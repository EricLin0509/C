# 向线程传递参数

## 参数来源——void *args

先看`pthread_create`的函数原型

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
```
其中 `void *(*start_routine) (void *)` 这个函数指针指向的就是线程的入口函数，而 `void *arg` 就是这个入口函数的参数

只需要编写在入口函数中使用 `void *args` 就可以获取到线程的参数

```c
void *routine(void *args)
```

## 代码示例

每个线程打印不同的数字

### 创建线程

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine();
pthread_t thread[10];

for(int i = 0; i < 10; i++)
{
    if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

for(int i = 0; i < 10; i++)
{
    if(pthread_join(thread[i], NULL) != 0)
    {
        perror("pthread_join");
        return 2;
    }
}
```

### 传递参数

#### 入口函数部分

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int index = *((int *)args);
    printf("%d ", primes[index]);
}
```

#### main函数部分

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine();
pthread_t thread[10];

for(int i = 0; i < 10; i++)
{
    if(pthread_create(&thread[i], NULL, &routine, &i) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

for(int i = 0; i < 10; i++)
{
    if(pthread_join(thread[i], NULL) != 0)
    {
        perror("pthread_join");
        return 2;
    }
}
printf("\n");
```

#### 运行

```bash
gcc -o main main.c -pthread
./main
11 17 19 11 29 0 0 0 13 0
```

可以看到，有些线程输出的结果是错误的，这是因为在创建线程的时候，`i`的值已经被修改了，所以线程输出的结果是错误的

#### 图表示意图

假设只有两个线程

##### 理想情况

| 主线程 | 线程1 | 线程2 |
| :-----: | :---: | :---: |
| i = 0 | 已创建<br>i = 0<br>输出2 | - |
| i =1 | - | 已创建<br>i = 1<br>输出3 |

##### 实际情况
| 主线程 | 线程1 | 线程2 |
| :-----: | :---: | :---: |
| i = 0 | 已创建<br>但未执行<br>i = 1 | - |
| i =1 | 执行线程<br>i = 1<br>输出3 | 已创建<br>i = 1<br>输出3 |


### 解决方案

### 方案1——将i的值复制到堆上 (复杂)

#### main函数部分

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine();
pthread_t thread[10];

for(int i = 0; i < 10; i++)
{
    int *index =malloc(sizeof(int));
    *index = i;
    if(pthread_create(&thread[i], NULL, &routine, index) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

for(int i = 0; i < 10; i++)
{
    if(pthread_join(thread[i], NULL) != 0)
    {
        perror("pthread_join");
        return 2;
    }
}
printf("\n");
```

#### 入口函数部分

如果在 `main` 函数释放 `temp`，会导致传入 `args` 的值不正确 (因为可能已经释放)，所以只能在 `routine` 函数中释放 `args`

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int index = *((int *)args);
    printf("%d ", primes[index]);
    free(args);
}
```

[源代码](向线程传递参数.c)

### 方案2——将数组地址传递给入口函数 (简单)

#### main函数部分

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine();
pthread_t thread[10];

for(int i = 0; i < 10; i++)
{
    if(pthread_create(&thread[i], NULL, &routine, primes+i) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

for(int i = 0; i < 10; i++)
{
    if(pthread_join(thread[i], NULL) != 0)
    {
        perror("pthread_join");
        return 2;
    }
}
printf("\n");
```

#### 入口函数部分

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int arr = (int *)args;
    printf("%d ", *arr);
}
```

[源代码](向线程传递参数简单版.c)

##### 原因

之前使用 `&i` 会向每个线程传递 `i` 的地址，如果线程暂停，那么 `i` 的值就会被修改，也会导致`primes[i]` 发生偏移，使得读取结果错误

而使用 `primes+i` 会向每个线程传递不同的地址，即使线程暂停，也不会影响读取结果