# 条件变量

## 定义

条件变量是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：一个线程等待"条件变量的条件成立"而挂起；另一个线程使"条件成立"（给出条件成立信号）

## 情景

假设现在有一辆汽车，现在有两个线程，一个线程是加油的线程，一个线程是等待加油的线程

- `fuel_filling`: 加油
- `car`: 车

### 定义两个函数

```c
pthread_mutex_t mutexFuel;
int fuel = 0;

void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    fuel -= 40;
    printf("请立即加油! 现在剩余：%d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}
```

这两个函数的作用分别是加油和等待加油

### 创建两个线程分别调用这两个函数

```c
pthread_mutex_t mutexFuel;
int fuel = 0;

int main(int argc, const char * argv[]) {
    pthread_t thread[2];
    pthread_mutex_init(&mutexFuel, NULL);
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
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
    return 0;
}
```

### 运行

```bash
gcc -o conditionVariable conditionVariable.c -pthread
./conditionVariable
请立即加油! 现在剩余：-40
加油中... -25
加油中... -10
加油中... 5
加油中... 20
加油中... 35
```

可以看到，油量出现了负值

### 尝试解决

```c
void *car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("没油了，等待中...\n");
        sleep(1);
    }
    fuel -= 40;
    printf("请立即加油! 现在剩余：%d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}
```

### 再次运行

```bash
gcc -o conditionVariable conditionVariable.c -pthread
./conditionVariable
没油了，等待中...
没油了，等待中...
没油了，等待中...
...
```

可以看到，程序一直在等待中，没有任何输出，因为 `mutex` 一直被占用着

## 解决方案——pthread_cond

`pthread_cond` 有三种类型
- `pthread_cond_wait`: 等待条件变量
- `pthread_cond_broadcast`: 广播条件变量
- `pthread_cond_signal`: 发送条件变量

### 定义条件变量

```c
pthread_cond_t condFuel;
```

### 初始化条件变量

```c
pthread_mutex_t mutexFuel;
int fuel = 0;

pthread_cond_t condFuel;

int main(int argc, const char * argv[]) {
    pthread_t thread[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL); // 初始化条件变量
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
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

### 使用条件变量

#### 等待条件变量

```c
pthread_mutex_t mutexFuel;
int fuel = 0;

pthread_cond_t condFuel;

void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("没油了，等待中...\n");
        pthread_cond_wait(&condFuel, &mutexFuel); // 等待条件变量
    }
    fuel -= 40;
    printf("请立即加油! 现在剩余：%d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}
```

**注意：当执行`pthread_cond_wait(&condFuel, &mutexFuel);` 时，会先解锁 `mutexFuel`，然后等待条件变量，当条件变量被发送时，会先加锁 `mutexFuel`，然后执行后面的代码**

#### 发送条件变量

```c
pthread_mutex_t mutexFuel;
int fuel = 0;

pthread_cond_t condFuel;

void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel); // 发送条件变量
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("没油了，等待中...\n");
        pthread_cond_wait(&condFuel, &mutexFuel); // 等待条件变量
        // 等价于：
        // pthread_mutex_unlock(&mutexFuel);
        // 等待条件变量
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("请立即加油! 现在剩余：%d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}
```

[源代码](条件变量.c)

### 运行

```bash
gcc -o conditionVariable conditionVariable.c -pthread
./conditionVariable
没油了，等待中...
加油中... 15
没油了，等待中...
加油中... 30
没油了，等待中...
加油中... 45
请立即加油! 现在剩余：5
加油中... 20
加油中... 35
```

可以看到，程序正常运行了

## 总结

条件变量相当于一个控制信号的标识符，可以发送信号，也可以等待信号，当信号被发送时，会唤醒等待的线程，然后执行后面的代码