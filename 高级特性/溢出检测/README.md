# 溢出检测

在 C 语言中，整数溢出是一种未定义行为

所以我们在进行整数运算时，需要检查是否会导致整数溢出

## 传统的检测方法

假设我们现在有两个整数 `a` 和 `b`，我们想计算它们的和 `a + b`

```c
int a = INT_MAX - 10;
int b = 10000;
```

如果要检测 `a + b` 是否会导致整数溢出，我们可以用以下方法

这里需要处理两种情况：
- 正数溢出：`a + b` 结果大于 `INT_MAX`
- 负数溢出：`a + b` 结果小于 `INT_MIN`

```c
if (b > 0 && a > INT_MAX - b) // 正数溢出
    printf("Overflow occurred!\n");
if (b < 0 && a < INT_MIN - b) // 负数溢出
    printf("Underflow occurred!\n");

int sum = a + b;
```

## 新的检测方法

在新的 C23 标准中，引入了新的 [`stdckdint`](https://en.cppreference.com/c/header/stdckdint) 库，可以检测整数溢出

这提供三个宏

- `ckd_add(R, A, B)`
- `ckd_sub(R, A, B)`
- `ckd_mul(R, A, B)`

它们分别运算 `A + B`、`A - B`、`A * B` 并把运算结果存入 `R`

如果溢出，则返回 `true`，否则返回 `false`

> Tips: 这些宏是通用的，可以用于任意整数类型, 包括 `char`、`short`、`int`、`long`、`size_t`

```c
int c = 0;
if (ckd_add(&c, a, b)) // 正负数溢出都检测
    printf("Overflow or underflow occurred!\n");
else
    printf("Result: %d\n", c);
```