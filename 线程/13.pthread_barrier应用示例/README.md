# pthread_barrier应用示例

## 代码示例

### 定义线程数量和摇色子次数

```c
#define THREAD_NUM 10

int diveValue[10];
int status[10] = {0};
```

### 摇色子函数

```c
#define THREAD_NUM 10

int diveValue[10];
int status[10] = {0};

void *roll_dice(void *args)
{
    int index = *(int *)args;
    diceValues[index]  = rand() % 6 + 1;
    if (status[index] == 1)
    {
        printf("(%d rolled %d) I won\n", index, diceValues[index]);
    }
    else
    {
        printf("(%d rolled %d) I lost\n", index, diceValues[index]);
    }
}
```

### main函数

#### 创建线程

```c
#define THREAD_NUM 10

int diveValue[10];
int status[10] = {0};

int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&threads[i], NULL, &roll_dice, NULL) != 0)
        {
            perror("pthread_create error");
        }
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join error");
        }
    }
}
```

#### 添加获胜条件

```c
#define THREAD_NUM 10

int diveValue[10];
int status[10] = {0};

int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&threads[i], NULL, &roll_dice, NULL) != 0)
        {
            perror("pthread_create error");
        }
    }

    int max = 0;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] > max)
        {
            max = diceValues[i];
        }
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] == max)
        {
            status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join error");
        }
    }
}
```

#### 传递参数

```c
#define THREAD_NUM 10

int diveValue[10];
int status[10] = {0};

void *roll_dice(void *args)
{
    int index = *(int *)args;
    diceValues[index]  = rand() % 6 + 1;
    if (status[index] == 1)
    {
        printf("(%d rolled %d) I won\n", index, diceValues[index]);
    }
    else
    {
        printf("(%d rolled %d) I lost\n", index, diceValues[index]);
    }
    free(args);
}

int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&threads[i], NULL, &roll_dice, a) != 0)
        {
            perror("pthread_create error");
        }
    }

    int max = 0;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] > max)
        {
            max = diceValues[i];
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join error");
        }
    }
}
```

### 运行

```bash
gcc -o pthread_barrier pthread_barrier.c -pthread
./pthread_barrier
(1 rolled 2) I lost
(6 rolled 2) I lost
(3 rolled 6) I lost
(5 rolled 2) I lost
(4 rolled 5) I lost
(0 rolled 5) I lost
(9 rolled 1) I lost
(7 rolled 4) I lost
(8 rolled 2) I lost
(2 rolled 4) I lost
```

可以看到，即使有符合条件的线程，也会判定为输

### 原因

因为多线程没有办法保证运行在某处代码后面

### 解决方案——pthread_barrier

由于我们不能使用 `pthread_mutex` ,因为这些线程需要同时运行，所以我们需要使用 `pthread_barrier`

```c
#define THREAD_NUM 10

int diceValues[10];
int status[10] = {0};

pthread_barrier_t barrierRollDice; // 用于保证所有线程都摇完色子
pthread_barrier_t barrierCaculate; // 用于保证所有线程都计算完胜负

void *roll_dice(void *args)
{
    int index = *(int *)args;
    diceValues[index]  = rand() % 6 + 1;
    pthread_barrier_wait(&barrierRollDice); // 保证所有线程都摇完色子
    pthread_barrier_wait(&barrierCaculate); // 保证所有线程都计算完胜负
    if (status[index] == 1)
    {
        printf("(%d rolled %d) I won\n", index, diceValues[index]);
    }
    else
    {
        printf("(%d rolled %d) I lost\n", index, diceValues[index]);
    }
    free(args);
}

int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    pthread_barrier_init(&barrierRollDice, NULL, THREAD_NUM+1);
    pthread_barrier_init(&barrierCaculate, NULL, THREAD_NUM+1);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&threads[i], NULL, &roll_dice, a) != 0)
        {
            perror("pthread_create error");
        }
    }

    pthread_barrier_wait(&barrierRollDice); // 保证所有线程都摇完色子

    int max = 0;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] > max)
        {
            max = diceValues[i];
        }
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] == max)
        {
            status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }

    pthread_barrier_wait(&barrierCaculate); // 保证所有线程都计算完胜负

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join error");
        }
    }
    pthread_barrier_destroy(&barrierRollDice);
    pthread_barrier_destroy(&barrierCaculate);
}
```

**注意：由于还有一个主线程，所以线程总量为`THREAD_NUM+1`**

[源代码](pthread_barrier应用示例.c)

### 重新运行

```bash
gcc -o pthread_barrier pthread_barrier.c -pthread
./pthread_barrier
(9 rolled 2) I lost
(7 rolled 1) I lost
(8 rolled 4) I lost
(6 rolled 5) I lost
(3 rolled 2) I lost
(5 rolled 2) I lost
(0 rolled 2) I lost
(4 rolled 6) I won
(1 rolled 4) I lost
(2 rolled 5) I lost
```