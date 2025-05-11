# pthreads 简介

## 定义

pthreads 是 POSIX 线程标准的实现，是一套通用的多线程 API

## 特点

- 可移植性好
- 支持线程间同步和互斥
- 支持线程间通信
- 支持线程的优先级
- ...

## 引入函数库

```c
#include <pthread.h>
```

如果使用 vscode 编写，需要在 `tasks.json` 中的 `args` 中添加 `-pthread`

如果使用 gcc 编译，需要在编译命令中添加 `-pthread`


## 代码示例

### 定义线程标识符

线程标识符用于存储线程的信息

```c
pthread_t thread;
```

### 创建线程

#### 函数原型

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

#### 参数
- `thread`: 线程标识符
- `attr`: 线程属性
- `start_routine`: 线程函数，返回值为 `void*`，参数为 `void*`
- `arg`: 线程函数参数

#### 示例

```c
void *thread_func();
pthread_t thread;
pthread_create(&thread, NULL, &thread_func, NULL);
```

#### 创建多个线程

```c
void *thread_func();
pthread_t thread1, thread2;
pthread_create(&thread1, NULL, &thread_func, NULL);
pthread_create(&thread2, NULL, &thread_func, NULL);
```

### 等待子线程结束

使用 `pthread_join` 函数等待子线程结束

主线程需要等待子线程结束，否则子线程会成为僵尸线程

#### 函数原型
```c
int pthread_join(pthread_t thread, void **retval);
```

#### 参数
- `thread`: 线程标识符
- `retval`: 线程函数返回值

#### 示例

```c
void *thread_func();
pthread_t thread;
pthread_create(&thread, NULL, &thread_func, NULL);
pthread_join(thread, NULL);
```

### 错误检查

`pthread_create` 和 `pthread_join` 函数返回值为 `int`，如果返回值不为 `0`，则表示发生错误

#### 示例

```c
void *thread_func();
pthread_t thread;

if (pthread_create(&thread, NULL, &thread_func, NULL) != 0) {
    printf("Error creating thread\n");
    return 1;
}

if (pthread_join(thread, NULL)!= 0)
{
    printf("Error joining thread\n");
    return 2;
}
```

[源代码](pthreads简介.c)

