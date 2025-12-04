# _Generic

`_Generic` 是 C11 引入的新特性，它允许用户**在编译时手动进行函数重载** (Function Overloading with Manual Mangling)

> [!WARNING]
> `_Generic` 不是泛型，它只是一种函数重载的手段

## 宏定义

```c
#define _Generic(expression, type1: e1, type2: e2, ... /* , default: e */)
```

## 示例

假设现在我们有两个函数，`print_int()` 和 `print_double()`，它们都可以打印出一个数值，但是它们的实现方式不同

```c
void print_int(int num)
{
    printf("%d\n", num);
}

void print_double(double num)
{
    printf("%f\n", num);
}
```

如果我们想设计一个通用的宏 `PRINT()`，它可以打印出任意类型的数值，我们可以用 `_Generic` 关键字来实现：

```c
#define PRINT(num) _Generic(num, \
    int: print_int(num), \
    double: print_double(num))
```

也可以设置 `default` 分支，当没有匹配到类型时，会执行 `default` 分支的代码：

```c
#define PRINT(num) _Generic(num, \
    int: print_int(num), \
    double: print_double(num), \
    default: printf("Unknown type\n"))
```

这样，我们就可以使用 `PRINT()` 宏打印出任意类型的数值了：

```c
int main()
{
    PRINT(123);
    PRINT(3.14);
    PRINT(3.14F);
    return 0;
}
```

```zsh
123
3.140000
Unknown type
```