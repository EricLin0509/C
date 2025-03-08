# 竟态条件

## 定义

当两个或多个线程对同一个数据进行操作时，就会发生竟态条件

## 代码示例

### 设计简单的多线程

```c
int mail = 0;

void *routine()
{
    mail++;
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;   
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL) != 0)
    {
        return 2;
    }
    printf("mail: %d\n", mail);
}
```

运行

```bash
gcc -o race race.c -pthread
./race
mail: 2
```

### 使用循环增加mail的值

```c
int mail = 0;

void *routine()
{
    for (int i = 0; i < 100; i++)
    {
        mail++;
    }
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;   
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL) != 0)
    {
        return 2;
    }
    printf("mail: %d\n", mail);
}
```

运行

```bash
gcc -o race race.c -pthread
./race
mail: 200
```

### 将循环次数增加到1000000

```c
int mail = 0;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        mail++;
    }
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;   
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL) != 0)
    {
        return 2;
    }
    printf("mail: %d\n", mail);
}
```

[源代码](竞态条件.c)

运行

```bash
gcc -o race race.c -pthread
./race
mail: 1052041
```

这里的结果并不是2000000，而是**随机数**，这是因为线程1和线程2在执行mail++时，可能会出现竟态条件，导致mail的值不正确

## 原因

### 首先了解怎么增加变量的值

1. 从内存中读取变量的值
2. 增加变量的值
3. 将变量的值写回内存

如果是单线程，那么这三个步骤是顺序执行的，不会出现竟态条件

但是如果是多线程，那么这三个步骤可能会被打断，导致变量的值不正确

### 图表示意图

#### 正常情况

假设初始值为25

|        | thread1 | thread2 |
| :---: | :---: | :---: |
| 读取 | 25 | 26 |
| 增加 | 25 | 26 |
| 写回 | 26 | 27 |

结果：27

#### 假设线程2被打断

假设初始值为25，且已经循环了4次

|        | thread1 | thread2 |
| :---: | :---: | :---: |
| 读取 | 29 | 25 |
| 增加 | 29 | 30 |
| 写回 | 30 | 26 |

结果：26

这里可以看到，`thread2`被打断了，导致获取的值不正确

## 解决方法——互斥锁

互斥锁的意思是，当一个线程在执行时，其他线程不能执行，直到该线程执行完毕

### 大致原理

```c
int mail = 0;
int lock = 0;

void *routine()
{
    if (lock == 1)
    {
        // 等待lock变为0
    }
    lock = 1;
    mail++;
    lock = 0;
}
```

## Mutex

Mutex是一种同步原语，用于保护共享资源，防止多个线程同时访问共享资源，防止出现竟态条件

### 原理

Mutex采用的互斥 (Mutual Exclusion) 的原理

互斥是线程同步的一个属性，它表示**在任意给定时间点，临界区中不能同时存在两个线程**

### 代码示例

#### 初始化mutex

```c
int mail = 0;
pthread_mutex_t mutex;

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁
    ...
    pthread_mutex_destroy(&mutex); // 销毁互斥锁
}
```

#### 使用mutex

```c
int mail = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        mail++;
        pthread_mutex_unlock(&mutex); // 解锁
    }   
}
```

[源代码](mutex.c)

#### 运行

```bash
gcc -o mutex mutex.c -pthread
./mutex
mail: 2000000
```

### 原理

`pthread_mutex` 相当于将一部分代码保护起来，防止其他线程同时执行。当执行`pthread_mutex_lock`时，其他线程就无法执行，直到执行`pthread_mutex_unlock`，其他线程才能执行，**但这样会使运算时间变长**

p.s. 一般情况下，竞态条件不会在单核CPU上出现