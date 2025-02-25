# 线程死锁

## 定义

线程死锁是指由于两个或者多个线程互相持有对方所需要的资源，导致这些线程处于等待状态，无法前往执行

## 产生原因

### 多次加锁

```c
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex);
        mail++;
        pthread_mutex_unlock(&mutex);
    }   
}
```

### 多个锁但不按顺序加锁

```c
pthread_mutex_t mutex;
pthread_mutex_t mutex2;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        if(i % 2 == 0)
        {
            pthread_mutex_lock(&mutex);
            pthread_mutex_lock(&mutex2);
        }
        else
        {
            pthread_mutex_lock(&mutex2);
            pthread_mutex_lock(&mutex);
        }
        mail++;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex2);
    }   
}
```

#### 图解

| | mutex | mutex2 |
| :---: | :---: | :---: |
| 线程1 | <mark>加锁</mark> | 等待 |
| 线程2 | 等待 | <mark>加锁</mark> |

可以看到线程1和线程2都在等待对方释放锁，导致两个线程都无法继续执行，从而产生死锁