# 可变参数列表

在 C 语言中，函数可以定义可变参数列表，即函数可以接受任意数量的参数

## 代码示例

### 函数定义

我们需要使用 `...` 作为函数的最后一个参数，表示这个参数是一个可变参数列表

```c
void sum_all(int total, ...);
```

### 引入头文件

我们需要引入 `stdarg.h` 头文件，其中包含了 `va_list`、`va_start`、`va_arg`、`va_end` 等函数

```c
#include <stdarg.h>
```

### 初始化可变参数列表

我们需要初始化一个 `va_list` 变量，用来存储可变参数列表

然后使用 `va_start` 函数初始化 `ap` 变量，这将 `ap` 指向第一个可变参数

```c
va_list ap;

va_start(ap, total);
```

### 读取可变参数列表

我们可以使用 `va_arg` 函数读取可变参数列表中的参数

**`va_arg` 会同时将 `ap` 指向下一个参数**

```c
int sum = 0;
for (int i = 0; i < total; i++)
{
    int arg = va_arg(ap, int);
    sum += arg;
}
printf("sum = %d\n", sum);
```

### 结束可变参数列表

最后，我们需要使用 `va_end` 函数结束 `ap` 变量的使用

```c
va_end(ap);
```

## 结果

当我们调用 `sum_all` 函数时，可以传入任意数量的 `int` 参数，并打印出所有参数的和

```c
sum_all(3, 1, 2, 3);
sum_all(5, 4, 5, 6, 7, 8);
```

输出

```
sum = 6
sum = 30
```