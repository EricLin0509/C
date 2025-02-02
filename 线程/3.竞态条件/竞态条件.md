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