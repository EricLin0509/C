# 静态断言

在 C23 标准中，引入了静态断言 (`static_assert`) 的概念

静态断言是指在编译时进行的检查，用来确保程序中的条件一定为真

## 代码

在之前的 C 语言标准中，如果想检查一个常量是否设置正确，我们只能使用 `assert` 关键字来进行条件检查

```c
#define FOO 0
assert(FOO == 10);
```

这种只能在程序运行时进行检查的做法，对于编译时检查来说是不够的

```bash
static_assert: static_assert.c:7: main: Assertion `FOO == 10' failed.
[1]    76542 IOT instruction (core dumped)  ./static_assert
```

那么解决办法就是使用 `static_assert` 关键字

```c
#define FOO 0
static_assert(FOO == 10, "FOO should be 10"); // 可以在全局作用域或者局部作用域使用
```

这时，如果 `FOO` 的值不是 10，编译器会报错并显示指定的错误信息

```bash
static_assert.c:6:1: error: 静态断言错误："FOO should be 10"
    6 | static_assert(FOO == 10, "FOO should be 10");
      | ^~~~~~~~~~~~~
```

**注意**：`static_assert` 关键字只能用于宏定义或者 `constexpr` 变量

## 附加内容

如果使用条件编译，可以使用 `#error` 关键字来触发编译错误

```c
#define FOO 0
#if FOO != 10
#error "FOO should be 10"
#endif
```

```bash
static_assert.c:6:2: error: #error "FOO should be 10"
    6 | #error "FOO should be 10"
      |  ^~~~~
```