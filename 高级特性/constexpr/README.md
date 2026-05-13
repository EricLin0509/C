# constexpr

`constexpr` 是 C23 引入的新特性

可以用来定义常量表达式。常量表达式是指在编译期间可以计算出结果的表达式

## 示例

假设我们现在有一个静态常量

```c
static const int a = 10;
```

如果我们想用这个值初始化一个数组，会发生报错

```c
int arr[a]; // error: non-constant expression cannot be used in a constant expression
```

## 使用宏定义

虽说使用宏定义可以解决这个问题

```c
#define A 10
int arr[A]; // ok
```

但是宏定义只是**文字替换**，它并没有类型

如果发生了整数溢出，编译器也不会发出警告，这会导致难以排查的问题

## constexpr

但是如果我们把 `a` 定义为 `constexpr`，就可以正常初始化数组

相比宏定义，`constexpr` 有类型，可以避免一些隐患

```c
constexpr int b = 10;
int arr[b]; // ok
```

这是因为 `const` 是在运行时初始化，而 `constexpr` 是在编译时初始化 (开启编译器优化甚至会做文字替换)