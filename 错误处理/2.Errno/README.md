# Errno

## 简介

在C语言中，errno是一个全局变量，用于存储最近一次系统调用的错误码。当一个系统调用失败时，errno会被设置为一个非零值，这个值可以通过errno宏来获取

## 代码示例

```c
int main(int argc, const char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
}
```

假设传入的argv[1]是一个不存在的文件，那么open函数会返回-1，errno会被设置为ENOENT

### 使用errno

```c
int main(int argc, const char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) printf("errno: %d\n", errno);
}
```

```
./example /tmp/123
errno: 2
```

### 查看errno对应的错误信息

使用 `strerror` 函数可以查看errno对应的错误信息

```c
int main(int argc, const char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) printf("errno: %d, strerror: %s\n", errno, strerror(errno));
}
```

```
./example /tmp/123
errno: 2, strerror: No such file or directory
```