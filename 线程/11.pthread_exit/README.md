# pthread_exit

`pthread_exit` 可以直接获取当前线程的返回值，并且可以不用 `return`，直接退出线程

## 代码示例

### 在入口函数使用

```c
void *dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    pthread_exit((void *) result);
}
```

### 在`main`函数使用

#### 先尝试使用 `return 0`

```c
void *dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("result = %d\n", *result);
    pthread_exit((void *) result);
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

    return 0;

    if (pthread_join(thread, (void**) &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
    printf("result = %d\n", *result);
    free(result);
}
```

#### 运行

```c
gcc -o pthread_exit pthread_exit.c -pthread
./phtread_exit
```

可以看到，没有任何输出

#### 用`pthread_exit`替换`return 0`


```c
void *dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("result = %d\n", *result);
    pthread_exit((void *) result);
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

    pthread_exit(NULL);

    if (pthread_join(thread, (void**) &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
    printf("result = %d\n", *result);
    free(result);
}
```

[源代码](pthread_exit.c)

#### 再次运行

```bash
gcc -o pthread_exit pthread_exit.c -pthread
./phtread_exit
result = 2
```

可以看到，输出了`result = 2`，说明线程已经运行完毕

## 总结

`pthread_exit` 只会结束线程，不会结束进程，在`main`函数调用会让进程先等待所有线程结束，然后再结束进程