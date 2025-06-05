# Assert

## 简介

在 C / C++ 中，我们通常使用 `assert` 来检查程序的运行状态

将一个表达式作为参数，有两种情况：
- 表达式为真，则程序继续运行
- 表达式为假，则程序终止
    - 输出错误信息
    - 调用 `abort` 终止程序

## 代码示例

需要导入 `assert.h` 头文件

```c
#include <assert.h>
```

```c
int main(int argc, const char *argv[]) {
    printf("Line 1 works!\n");
    assert(2 == 2);
    printf("Line 3 works!\n");
    return 0;
}
```

此时，由于 `2 == 2` 为真，程序继续运行

```
Line 1 works!
Line 3 works!
```

如果将 `2 == 2` 改为 `2 == 1`，则程序终止

```c
int main(int argc, const char *argv[]) {
    printf("Line 1 works!\n");
    assert(2 == 1);
    printf("Line 3 works!\n");
    return 0;
}
```

此时，由于 `2 == 1` 为假，程序终止

```
Line 1 works!
Assert: Assert.c:7: main: Assertion `1 == 2' failed.
```

错误信息包含以下信息：

- Assert —— 表示这是一个断言错误
- Assert.c:7 —— 表示错误发生在 `Assert.c` 文件的第 7 行
- main —— 表示错误发生在 `main` 函数中
- Assertion 1 == 2 failed. —— 表示断言失败，表达式 `1 == 2` 为假

### 实用示例 —— 检查指针是否为空

假设现在要输出一个字符串

```c
int main(int argc, const char *argv[]) {
    char *str = "Hello world!";
    printf("%s\n", str);
    return 0;
}
```

此时，由于 `str` 指向的是一个字符串，程序不会报错

但是，如果将 `str` 改为 `NULL`，则程序会报错

```c
int main(int argc, const char *argv[]) {
    char *str = NULL;
    printf("%s\n", str);
    return 0;
}
```

此时，由于 `str` 指向的是一个空指针，程序会报错

```
Segmentation fault (core dumped)
```

使用 `assert` 可以检查指针是否为空，如果为空，则程序终止

```c
int main(int argc, const char *argv[]) {
    char *str = NULL;
    assert(str != NULL);
    printf("%s\n", str);
    return 0;
}
```

```
Assert: Assert.c:7: main: Assertion `str!= NULL' failed.
```

### 关闭调试信息

在编译时，可以定义宏 `NDEBUG` 来关闭调试信息

```c
#define NDEBUG // 此行必须在 #include <assert.h> 之前

#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[]) {
    char *str = NULL;
    assert(str != NULL);
    printf("%s\n", str);
    return 0;
}
```

或者在编译时使用 `-DNDEBUG` 选项

```bash
gcc -DNDEBUG Assert.c
```

此时，由于 `NDEBUG` 定义了，程序不会输出任何错误信息