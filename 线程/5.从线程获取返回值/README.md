# 从线程获取返回值

## 线程的返回值来源——pthread_join

先看`pthread_join`的函数原型

```c
int pthread_join (pthread_t __th, void **__thread_return);
```

可以看到，`pthread_join`的第二个参数是一个二级指针，用来接收线程的返回值

## 代码示例

```c
void *dice()
{
    int value = (rand() % 6) + 1;
    return (void*) &value;
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    int *result;
    pthread_t thread;
    if (pthread_create(&thread, NULL, &dice, NULL) != 0) 
    {
        perror("pthread_create");
        return 1;
    }
    if (pthread_join(thread, (void**) &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
    printf("result = %d\n", *result);
}
```

### 运行

```bash
./pthread_join
segmentation fault (core dumped)
```

### 为什么会报错？

因为函数 `dice` 存储在栈上，当函数返回时，栈上的内存会被释放，所以 `result` 指向的内存已经被释放，所以会报错

### 解决方法

将结果存储在堆上，这样就不会被释放

```c
void *dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    return (void*) result;
}
```

最后别忘了在 `main` 函数中释放内存
```c
free(result);
```

[源代码](从线程获取返回值.c)