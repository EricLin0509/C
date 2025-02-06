# 创建多个线程

## 代码示例

### 创建数组

```c
void *rountine();
pthread_t thread[5];
```

### 遍历数组

```c
void *rountine();
pthread_t thread[5];

for(int i = 0; i < 5; i++) {    }
```

### 创建线程

```c
void *rountine();
pthread_t thread[5];

for(int i = 0; i < 5; i++)
{
    if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }
}
```

### 合并线程

```c
void *rountine();
pthread_t thread[5];

for(int i = 0; i < 5; i++)
{
    if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }

    if(pthread_join(thread[i], NULL) != 0)
    {
        return 2;
    }
}
```

### 这里遇到的问题

#### 添加调试信息

```c
void *rountine();
pthread_t thread[5];

for(int i = 0; i < 5; i++)
{
    if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }
    printf("线程%d启动\n", i);
    if(pthread_join(thread[i], NULL) != 0)
    {
        return 2;
    }
    printf("线程%d结束\n", i);
}
```

#### 运行结果

```bash
./mul_thread

线程0启动
线程0结束
线程1启动
线程1结束
线程2启动
线程2结束
线程3启动
线程3结束
线程4启动
线程4结束
```

这里可以看到，线程的启动和结束顺序并不是我们所期望的，这是因为线程的启动和结束是异步的，相当于只有一个线程在运行，其他线程都在等待

### 解决方法——使用第二个循环控制合并线程

```c
void *rountine();
pthread_t thread[5];

for(int i = 0; i < 5; i++)
{
    if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
    {
        perror("pthread_create failed");
        return 1;
    }
    printf("线程%d启动\n", i);
}

for(int i = 0; i < 5; i++)
{
    if(pthread_join(thread[i], NULL) != 0)
    {
        return 2;
    }
    printf("线程%d结束\n", i);
}
```

[源代码](创建多个线程.c#L22)