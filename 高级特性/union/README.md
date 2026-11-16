# union (联合体)

本文基于 x86_64 架构 (小端序)

## 简介

`union` (联合体) 是一种和 `struct` 长得很像的自定义类型，区别在于：

- `struct` 的成员**各自占据独立的内存**，大小是各成员之和 (含对齐填充)
- `union` 的成员**共享同一块内存**，大小是最大成员的大小 (含对齐)

因为所有成员起始地址相同，**同一时刻只有一个成员的值是"有意义"的** —— 写一个成员就会覆盖其他成员的重叠部分。

## 语法

```c
union <联合体名> {
    <类型1> <成员1>;
    <类型2> <成员2>;
    ...
};  /* 注意这里的分号，漏写是常见编译错误 */
```

假设现在有个联合体：

```c
union MyUnion {
    char c;
    short a;
};
```

### 类型名与标签：为什么 `MyUnion u;` 编译不过

`union MyUnion { ... };` 里的 `MyUnion` 只是 **union tag (标签)**，不是类型名。C 语言的标签位于独立的命名空间，所以引用类型时必须写全 `union` 关键字：

```c
union MyUnion u;   /* 正确 */
MyUnion u;         /* 错误: error: unknown type name 'MyUnion' */
```

> 这正是 C 与 C++ 的差异：C++ 允许直接用标签当类型名，C 不允许。

如果想省掉 `union` 关键字，用 `typedef` 起个别名即可（这是 C 里最惯用的写法）：

```c
typedef union MyUnion {
    char c;
    short a;
} MyUnion;

MyUnion u;   /* 现在合法了，MyUnion 是真正的类型名 */
```

## 内存占用大小

`union` 的大小 = **最大成员的大小**，并向上对齐到最大成员的对齐要求。

```c
union Data {
    char c;
    double d;
    char a[32];
};
```

`Data` 中最大成员是长度为 32 的字符数组，`double` 要求 8 字节对齐，而 32 是 8 的整数倍，所以 `sizeof(union Data) == 32`。

对齐可能让结果比"最大成员"更大一点，例如：

```c
union A { char a[10]; int b; };   /* 最大成员 10 字节，int 要求 4 对齐 → sizeof == 12 */
union B { char c; double d; };    /* 最大成员 8 字节 → sizeof == 8 */
union C { char c; short a; };     /* 最大成员 2 字节 → sizeof == 2 */
```

## 内存布局

`union MyUnion` 的两个成员都从偏移 0 开始，共占 2 字节：

```
偏移:    0       1
       ┌───────┬───────┐
u.c    │ c     │       │   ← 只占 1 字节
       ├───────┴───────┤
u.a    │ a             │   ← 占 2 字节
       └───────────────┘
```

- `c`: `char` 类型成员，占 1 字节
- `a`: `short` 类型成员，占 2 字节
- 两者的**起始地址完全相同**，所以 `c` 与 `a` 的低字节重叠

## 示例

见 [union.c](union.c)，核心逻辑如下：

```c
union MyUnion u;

u.a = -1;
printf("u.a = %d (0x%x)\n", u.a, (unsigned)u.a);
printf("u.c = %d (0x%x)\n", u.c, (unsigned char)u.c);

u.c = 0;
printf("u.a = %d (0x%x)\n", u.a, (unsigned)u.a);
printf("u.c = %d (0x%x)\n", u.c, (unsigned char)u.c);
```

编译并运行：

```bash
gcc -std=c11 -Wall -Wextra -o union union.c
./union
```

实际输出（地址每次运行都不同，此处仅作示例）：

```
sizeof(union MyUnion) = 2
u 的地址 = 0x7fff79c2fe96, u.c 的地址 = 0x7fff79c2fe96, u.a 的地址 = 0x7fff79c2fe96

u.a = -1 之后
u.a = -1 (0xffffffff)
u.c = -1 (0xff)

u.c = 0 之后
u.a = -256 (0xffffff00)
u.c = 0 (0x0)
```

从输出可以得到三个结论：

1. `sizeof(union MyUnion) == 2`，等于最大成员 `short` 的大小
2. `u`、`u.c`、`u.a` 的地址完全相同，证实成员共享同一块内存
3. `u.c = 0` 只覆盖了 `u.a` 的**最低 1 个字节**，`0xFFFFFFFF` 变成 `0xFFFFFF00`，即十进制 `-1` 变成 `-256`

### 覆盖的是"最低字节"还是"最高字节"？

这取决于端序，本文基于 x86_64 的小端序：

| 端序 | 低地址存放 | `u.c = 0` 后 `u.a` | 十进制结果 |
|------|-----------|--------------------|-----------|
| 小端序 (x86_64) | 数值的最低位字节 | `0xFFFFFF00` | `-256` |
| 大端序 (如 SPARC) | 数值的最高位字节 | `0x00FFFFFF` | `16777215` |

所以这个示例的输出**依赖平台**，不是跨平台可移植的结论。想验证端序可参考 [端序](../端序/README.md)

## 与 struct 的对比

```c
struct S { char c; short a; };   /* sizeof == 4: 1 字节 c + 1 字节填充 + 2 字节 a */
union  U { char c; short a; };   /* sizeof == 2: 两个成员重叠在同一块内存 */
```

| 对比项 | `struct` | `union` |
| :---: | :------: | :-----: |
| 成员内存 | 各自独立、可能顺序排列 | 全部共享同一块内存 |
| 大小 | 各成员之和 + 对齐填充 | 最大成员大小 + 对齐填充 |
| 同时有效成员 | 全部 | 仅最后写入的那一个 |
| 典型用途 | 组合数据 | 互斥数据、类型双关 |

## 典型应用场景

1. **节省内存**：同一时刻只会用到其中一种字段的数据，例如"学生 / 教师"共用一个人员结构

```c
typedef enum {
    TYPE_STUDENT,
    TYPE_TEACHER,
} PersonType;

struct Person {
    PersonType type;          /* TYPE_STUDENT = 学生, TYPE_TEACHER = 教师 */
    union {
        int  grade;     /* 学生: 年级 */
        char title[16]; /* 教师: 职称 */
    } info;             /* 取两者中较大的大小 */
};
```

- `type` 是**标签字段 (tag)**，用来标记当前 `info` 中哪个成员是有效的
    - 取值为 `TYPE_STUDENT` 时，表示这条记录是学生，应读取 `info.grade`
    - 取值为 `TYPE_TEACHER` 时，表示这条记录是教师，应读取 `info.title`

2. **类型双关 (type punning)**：直接查看同一块内存的另一种解释，例如查看 `float` 的位模式

```c
union FloatBits {
    float f;
    unsigned int bits;
};

union FloatBits fb = { .f = 1.0f };
printf("%08x\n", fb.bits);   /* 3f800000 */
```

3. **协议 / 寄存器解析**：同一寄存器既可整体按 32 位访问，也可按位域拆解

4. **匿名 union** (C11)：省去中间成员名，直接访问

```c
struct Node {
    int type;
    union {
        int   i;
        float f;
    };      /* 匿名 union，可直接用 n.i / n.f */
};
```

## 注意事项

- **读取"非最后写入"的成员属于实现定义行为**：C 标准 (C11 §6.5.2.3 脚注) 只保证"读回的字节值"可见，具体结果依赖实现。GCC / Clang 明确支持这种用法，教学演示没问题，正式代码建议加注释标明当前活跃成员，或用 `struct` + tag 字段
- **不要用指针强转做类型双关**：`*(unsigned int *)&f` 违反 strict aliasing 规则（GCC 的 `-fstrict-aliasing` 可能优化出错）。请用 `union` 或 `memcpy`
- **不能对成员取地址后跨成员使用**：`&u.c` 与 `&u.a` 虽然数值相同，但指向的是不同有效类型
- **初始化只作用于一个成员**：

```c
union MyUnion u = { .a = 1 };   /* 只初始化 a，其余字节为 0 */
```

- **union 不记录"当前哪个成员有效"**：它只共享内存，不携带类型信息。需要区分当前活跃成员时，必须自己维护一个 tag 字段，例如上面 `struct Person` 中的 `type`
