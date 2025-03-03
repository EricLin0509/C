# 信号量实用示例

这里以登录排队为例，说明信号量的使用


## 示例

### 条件

假设有10个用户，最多允许5个用户同时登录

```c
#define USER 10
#define MAX_USER 5
```

### 入口函数

```c
#define USER 10
#define MAX_USER 5

sem_t semaphore; // 设置信号量

void *routine(void *arg)
{
    printf("(%d) 登录中...\n", *(int *)arg);
    sem_wait(&semaphore); // 信号量减1
    printf("(%d) 登录成功！\n", *(int *)arg);
    sleep(rand() % 5 + 1);
    printf("(%d) 退出登录！\n", *(int *)arg);
    free(arg);
    sem_post(&semaphore); // 信号量加1
}
```

### 主函数

```c
#define USER 10
#define MAX_USER 5

sem_t semaphore; // 设置信号量

int main(int argc, const char *argv[]) {
    pthread_t thread[USER];

    sem_init(&semaphore, 0, MAX_USER); // 初始化信号量

    for (int i = 0; i < USER; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < USER; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore); // 销毁信号量
}
```

[源代码](信号量实用示例.c)

### 运行

```bash
gcc semaphore.c -o semaphore -pthread
./semaphore
(1) 登录中...
(1) 登录成功！
(4) 登录中...
(4) 登录成功！
(8) 登录中...
(8) 登录成功！
(5) 登录中...
(5) 登录成功！
(0) 登录中...
(0) 登录成功！
(3) 登录中...
(6) 登录中...
(9) 登录中...
(2) 登录中...
(7) 登录中...
(5) 退出登录！
(3) 登录成功！
(4) 退出登录！
(6) 登录成功！
(3) 退出登录！
(9) 登录成功！
(8) 退出登录！
(2) 登录成功！
(1) 退出登录！
(7) 登录成功！
(0) 退出登录！
(6) 退出登录！
(9) 退出登录！
(7) 退出登录！
(2) 退出登录！
```

可以看到，**刚开始的时候有5个用户同时登录**，5个位置都被占用后，剩下的用户**要等到其中一个用户退出登录后，下一个用户才可以登录**，最后10个用户都退出登录

## 将上限调整为15

```c
#define USER 10
#define MAX_USER 15

sem_t semaphore;

void *routine(void *arg)
{
    printf("(%d) 登录中...\n", *(int *)arg);
    sem_wait(&semaphore);
    printf("(%d) 登录成功！\n", *(int *)arg);
    sleep(rand() % 5 + 1);
    printf("(%d) 退出登录！\n", *(int *)arg);
    free(arg);
    sem_post(&semaphore);
}


int main(int argc, const char *argv[]) {
    pthread_t thread[USER];

    sem_init(&semaphore, 0, MAX_USER);

    for (int i = 0; i < USER; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < USER; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore);
}
```

### 运行
```bash
gcc semaphore.c -o semaphore -pthread
./semaphore
(1) 登录中...
(1) 登录成功！
(0) 登录中...
(0) 登录成功！
(2) 登录中...
(2) 登录成功！
(6) 登录中...
(6) 登录成功！
(7) 登录中...
(7) 登录成功！
(3) 登录中...
(3) 登录成功！
(4) 登录中...
(4) 登录成功！
(5) 登录中...
(5) 登录成功！
(9) 登录中...
(9) 登录成功！
(8) 登录中...
(8) 登录成功！
(6) 退出登录！
(3) 退出登录！
(0) 退出登录！
(4) 退出登录！
(8) 退出登录！
(2) 退出登录！
(5) 退出登录！
(1) 退出登录！
(7) 退出登录！
(9) 退出登录！
```

可以看到，当上限调整到大于或等于用户数量时，**所有用户都可以同时登录和登出**，并且**程序运行速度更快**

## 总结

- 信号量一般用于限制资源的访问数量
    - 例如，服务器性能有限，只能同时处理一定数量的请求，可以使用信号量限制同时处理的请求数量
- 信号量越多，程序运行速度越快