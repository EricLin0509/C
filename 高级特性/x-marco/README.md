# X-Macro

X-Macro 是一种 C 预处理器宏技术，核心思想是将**数据定义**与**代码生成**分离——在一处集中维护数据列表，再通过反复重定义宏来生成不同的代码片段，从而在编译期自动生成重复性代码，避免手动维护带来的遗漏风险。

## 问题引入

假设我们有一个难度系统，每种难度对应一个返回速度值的函数：

```c
typedef int (*DifficultyFunc)(void);

int easy(void)   { return 1; }
int medium(void) { return 2; }
int hard(void)   { return 3; }

static const DifficultyFunc difficulty_funcs[] = {
    easy,
    medium,
    hard
};
```

当需要新增一个难度（如 `expert`）时，我们必须**同时**完成两件事：

1. 编写新函数 `expert`
2. 将 `expert` 添加到 `difficulty_funcs` 数组中

实际开发中很容易忘记第二步，导致数组与函数不同步。X-Macro 正是为了解决这类"列表与引用必须同步维护"的问题。

## 使用 X-Macro

### 第一步：集中定义数据列表

将所有难度条目集中到一个"列表宏"中，每条数据以统一的格式 `DIFFICULTY(name, value)` 描述：

```c
#define DIFFICULTIES \
    DIFFICULTY(EASY,   1) \
    DIFFICULTY(MEDIUM, 2) \
    DIFFICULTY(HARD,   3)
```

> `DIFFICULTY` 此时只是一个"占位符"，具体含义取决于后续的定义。

### 第二步：生成函数定义

对 `DIFFICULTY` 进行定义，使其展开为函数声明，然后展开列表宏：

```c
#define DIFFICULTY(name, value) \
    int difficulty_##name(void) \
    { \
        return value; \
    }

DIFFICULTIES

#undef DIFFICULTY
```

> 由于预处理器不会对宏参数进行拼接，`difficulty_name` 会被原样输出而非替换。因此必须使用 **`##` 记号拼接运算符（Token Pasting Operator）** 将 `difficulty_` 与参数 `name` 拼接为合法标识符，如 `difficulty_EASY`。

展开后等价于：

```c
int difficulty_EASY(void)   { return 1; }
int difficulty_MEDIUM(void) { return 2; }
int difficulty_HARD(void)   { return 3; }
```

### 第三步：生成函数指针数组

重新定义 `DIFFICULTY`，使其展开为函数名（加逗号），然后展开同一个列表宏：

```c
#define DIFFICULTY(name, value) difficulty_##name,

static const DifficultyFunc difficulty_funcs[] = {
    DIFFICULTIES
};

#undef DIFFICULTY
```

展开后等价于：

```c
static const DifficultyFunc difficulty_funcs[] = {
    difficulty_EASY, difficulty_MEDIUM, difficulty_HARD,
};
```

> 关键在于：函数定义和数组初始化**共享同一个数据源** `DIFFICULTIES`，因此永远保持同步。

## 补充：`##` 与 `#` 的区别

| 运算符 | 名称 | 作用 | 示例 | 展开结果 |
|--------|------|------|------|----------|
| `##` | 记号拼接运算符 (Token Pasting Operator) | 将两个记号拼接为一个新记号 | `difficulty_##EASY` | `difficulty_EASY` |
| `#` | 字符串化运算符 (Stringizing Operator) | 将宏参数转换为字符串字面量 | `#EASY` | `"EASY"` |

## 验证

可使用 `cpp`（C 预处理器）命令查看宏展开结果，确认代码生成是否正确：

```c
typedef int (*DifficultyFunc)(void);

int difficulty_EASY(void)   { return 1; }
int difficulty_MEDIUM(void) { return 2; }
int difficulty_HARD(void)   { return 3; }

static const DifficultyFunc difficulty_funcs[] = {
    difficulty_EASY, difficulty_MEDIUM, difficulty_HARD,
};
```

## 新增难度

使用 X-Macro 后，新增难度只需在 `DIFFICULTIES` 中添加一行：

```c
#define DIFFICULTIES \
    DIFFICULTY(EASY,   1) \
    DIFFICULTY(MEDIUM, 2) \
    DIFFICULTY(HARD,   3) \
    DIFFICULTY(EXPERT, 4)
```

重新编译后，函数定义和数组都会自动包含新条目，无需手动同步：

```c
int difficulty_EASY(void)   { return 1; }
int difficulty_MEDIUM(void) { return 2; }
int difficulty_HARD(void)   { return 3; }
int difficulty_EXPERT(void) { return 4; }

static const DifficultyFunc difficulty_funcs[] = {
    difficulty_EASY, difficulty_MEDIUM, difficulty_HARD, difficulty_EXPERT,
};
```