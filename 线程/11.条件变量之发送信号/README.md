# 条件变量之发送信号 (signal vs broadcast)

## 先看之前采用`signal`的代码

[传送门](../10.条件变量/条件变量.c)

### 假设现在有4辆车

```c
int main(int argc, const char * argv[]) {
    pthread_t thread[5];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL); // 初始化条件变量
    for (int i = 0; i < 5; i++)
    {
        if (i == 4)
        {
            if (pthread_create(&thread[i], NULL, &fuel_filling, NULL) != 0)
            {
                perror("pthread_create");
                return 1;
            }
            
        }
        else
        {
            if (pthread_create(&thread[i], NULL, &car, NULL) != 0)
            {
                perror("pthread_create");
                return 1;
            }
            
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel); // 销毁条件变量
    return 0;
}
```

[源代码](signal.c)

#### 运行

```bash
gcc -o signal signal.c -pthread
./signal
没油了，等待中...
没油了，等待中...
加油中... 15
没油了，等待中...
没油了，等待中...
没油了，等待中...
加油中... 30
没油了，等待中...
加油中... 45
请立即加油! 现在剩余：5
加油中... 20
没油了，等待中...
加油中... 35
没油了，等待中...
```

可以看到，程序一直在等待中，因为其中一辆车加油，其他车一直在等待中，因为只有一辆车加油，其他车都在等待中

### 修改代码

```c
void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 60; // 修改为60
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel); // 发送条件变量
        sleep(1);
    }
}
```

#### 运行

```bash
gcc -o signal signal.c -pthread
./signal
没油了，等待中...
没油了，等待中...
没油了，等待中...
加油中... 60
请立即加油! 现在剩余：20
没油了，等待中...
加油中... 80
请立即加油! 现在剩余：40
加油中... 100
请立即加油! 现在剩余：60
加油中... 120
请立即加油! 现在剩余：80
加油中... 140
```

可以看到，加油总量为300，扣除油量为160

### 原因

- **`pthread_cond_signal` 只会唤醒一个线程**
- 其他的线程都在等待中

#### 执行步骤

car1：lock -> cond_wait -> unlock
car2：lock -> cond_wait -> unlock
`fuel_filling`：lock -> cond_wait -> unlock
car3：lock (cond_wait)
car4：lock (cond_wait)

## 解决

### 使用`pthread_cond_broadcast` 广播条件变量

使用`pthread_cond_broadcast` 广播条件变量

```c
void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 60; // 修改为60
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_broadcast(&condFuel); // 广播条件变量
        sleep(1);
    }
}
```

[源代码](broadcast.c)


### 运行

```bash
gcc -o broadcast broadcast.c -pthread
./broadcast
没油了，等待中...
没油了，等待中...
加油中... 60
请立即加油! 现在剩余：20
没油了，等待中...
没油了，等待中...
没油了，等待中...
加油中... 80
请立即加油! 现在剩余：40
请立即加油! 现在剩余：0
没油了，等待中...
加油中... 60
请立即加油! 现在剩余：20
加油中... 80
加油中... 140
```

可以看到，所有的线程都被唤醒了，并且所有线程都是异步执行的

## 总结

| 函数 | signal | broadcast |
| ---- | ---- | ---- |
| 功能 | 唤醒一个线程 | 唤醒所有线程 |
| 用法 | `pthread_cond_signal(&condFuel);` | `pthread_cond_broadcast(&condFuel);` |