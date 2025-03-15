# 含函数指针的线程池

## 为什么线程池需要函数指针？

线程池需要函数指针的原因是，线程池中的线程需要执行不同的任务，而这些任务的具体实现方式是不同的。**为了能够让线程池中的线程能够执行不同的任务，线程池需要使用函数指针来执行不同的函数**

## 无参函数示例

### 设计任务

```c
// 任务
typedef struct Task
{
    void (*func)(); // 函数指针
} Task;

// 执行任务的函数
void executeTask(Task *task)
{
    task->func();
}
```

### 设计函数

```c
void sum()
{
    int a = rand() % 100;
    int b = rand() % 100;
    printf("%d + %d = %d\n", a, b, a + b);
}
```

### 测试

```c
// main

srand(time(NULL));
for (int i = 0; i < 100; i++)
{
    Task task = {&sum};
    submitTask(task);
}
```

```bash
gcc -o threadpool threadpool.c -pthread
./threadpool
...
66 + 4 = 70
21 + 31 = 52
77 + 4 = 81
87 + 87 = 174
91 + 63 = 154
8 + 14 = 22
91 + 9 = 100
56 + 43 = 99
24 + 26 = 50

```

可以看到，线程池成功执行了任务

## 含参函数示例

### 设计任务
```c
// 任务
typedef struct Task
{
    void (*func)(int, int); // 函数指针
    int arg1, arg2; // 参数
} Task;

// 执行任务的函数
void executeTask(Task *task)
{
    task->func(task->arg1, task->arg2);
}
```

### 设计函数
```c
void sum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}
```

### 测试
```c
// main

srand(time(NULL));
for (int i = 0; i < 100; i++)
{
    Task task = {&sum, rand() % 100, rand() % 100};
    submitTask(task);
}
```

```bash
gcc -o threadpool threadpool.c -pthread
./threadpool
...
2 + 10 = 12
34 + 19 = 53
51 + 75 = 126
2 + 90 = 92
31 + 95 = 126
89 + 73 = 162
10 + 1 = 11
16 + 84 = 100
97 + 38 = 135
70 + 24 = 94

```

可以看到，线程池成功执行了任务

## 运行不同函数

### 设计函数

```c
void sum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}

void sub(int a, int b)
{
    printf("%d - %d = %d\n", a, b, a - b);
}
```

### 测试

```c
// main

srand(time(NULL));
for (int i = 0; i < 100; i++)
{
    Task task = {
        .func = i % 2 == 0 ? &sum : &sub,
        .arg1 = rand() % 100,
        .arg2 = rand() % 100,
    };
    submitTask(task);
}
```

```bash
gcc -o threadpool threadpool.c -pthread
./threadpool
...
82 + 20 = 102
73 - 0 = 73
45 + 90 = 135
73 - 34 = 39
34 + 96 = 130
84 - 47 = 37
14 + 24 = 38
4 - 41 = -37
```

可以看到，线程池成功执行了两种不同的任务

## 获取返回值

### 存储返回值

由于我们无法直接从函数中获取返回值，所以一个相应数据类型的指针来存储函数的返回值

```c
int result[100];
```

### 设计任务
```c
// 任务
typedef struct Task
{
    int (*func)(int, int, int *); // 函数指针
    // 'int *' 是一个指向 int 类型的指针，它用来存储函数的返回值
    int arg1, arg2; // 参数
    int *res; // 返回值
}

// 执行任务的函数
void executeTask(Task *task)
{
    task->func(task->arg1, task->arg2, task->res);
}
```

### 设计函数

```c
void sum(int a, int b, int *result)
{
    *result = a + b; // 将结果存储到 result 中
}
```

### 测试

```c
// main

srand(time(NULL));
for (int i = 0; i < 100; i++)
{
    Task task = {
       .func = &sum,
       .arg1 = rand() % 100,
       .arg2 = rand() % 100,
       .res = result + i,
    };
}

for (int i = 0; i < 100; i++) // 打印结果
{
    printf("%d\n", result[i]);
}
```

```bash
gcc -o threadpool threadpool.c -pthread
./threadpool
...
155
137
35
70
78
133
180
```

可以看到，成功获取了返回值