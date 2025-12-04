# Volatile

## 简介

在C语言中，`volatile` 关键字用来表示一个变量可能被某些操作改变，而编译器不应对其进行优化 (如GCC的`-O2`、`-O3`等优化级别)


## 代码示例

假设现在有一个全局变量 `flag`

```c
bool flag = false;
```

如果有两个线程，一个线程先将 `flag` 置为 `true`，然后另一个线程判断 `flag` 是否为 `true`，如果是，则退出循环

```c
void *func(void *args) // 线程函数
{
    sleep(1);
    flag = true;
    return NULL;
}

int main(int argc, const char *argv[]) {
    pthread_t thread;
    pthread_create(&thread, NULL, func, NULL);

    printf("Waiting for flag to be set...\n");

    while(!flag) {} // 等待flag被设置
    printf("Flag is set!\n");

    pthread_join(thread, NULL);
    return 0;
}
```

此时不使用编译器优化，程序可以正常运行

```bash
gcc -o Thread Thread.c
./Thread
Waiting for flag to be set...
Flag is set!
```

但是，一旦使用`-O2`或`-O3`等优化级别，程序可能出现错误

```bash
gcc -O2 -o Thread Thread.c
./Thread
Waiting for flag to be set...
```

可以看到，程序卡在了 `while(!flag)` 这一行，原因是编译器优化了循环 (被优化成了 `while(true)`)

为了解决这个问题，我们需要告诉编译器，`flag` 是一个易变的变量，不要对其进行优化

```c
volatile bool flag = false; // 声明为易变的变量
```

此时，即使使用`-O2`或`-O3`等优化级别，程序也能正常运行

```bash
gcc -O2 -o Thread Thread.c
./Thread
Waiting for flag to be set...
Flag is set!
```

## 指针

`volatile` 关键字也可以用于指针，例如

- `volatile int *p` 表示**指针不是易变的，而指针指向的变量是易变的**
- `int *volatile p` 跟上面相反，表示**指针是易变的，而指针指向的变量不是易变的**

- `volatile int *volatile p` 表示**指针和指针指向的变量都是易变的**

## 作用

- 告诉编译器不要对易变的变量进行优化，从而避免出现不可预期的错误
- 避免多线程访问易变的变量时出现竞态条件 (race condition)