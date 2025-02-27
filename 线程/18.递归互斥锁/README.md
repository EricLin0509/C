# 递归互斥锁 (Recursive Mutex)

## 之前的问题

之前的例子中，我们使用了互斥锁，但是在使用互斥锁的过程中，我们可能会出现[死锁](../17.线程死锁/README.md)的情况

为了避免这种情况的发生，我们可以使用递归互斥锁

## 简介

递归互斥锁是一种特殊的互斥锁，它允许同一个线程多次获取互斥锁，而不会导致死锁的发生

## 用法

### 1. 定义互斥锁和互斥锁属性

```c
pthread_mutex_t mutex;
pthread_mutexattr_t recursive_mutex_attr;
```

### 2. 初始化互斥锁属性
```c
pthread_mutexattr_init(&recursive_mutex_attr);
```

### 3. 设置互斥锁属性为递归互斥锁

```c
pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
```

其中，`PTHREAD_MUTEX_RECURSIVE` 是一个宏，它用于设置互斥锁的类型为递归互斥锁

以下是其他的宏：
- `PTHREAD_MUTEX_NORMAL`：普通互斥锁，不允许递归
- `PTHREAD_MUTEX_ERRORCHECK`：错误检查互斥锁，允许递归，但在获取和释放互斥锁时会进行错误检查
- `PTHREAD_MUTEX_DEFAULT`：默认互斥锁，允许递归，但在获取和释放互斥锁时不会进行错误检查

### 4. 初始化互斥锁

```c
pthread_mutex_init(&mutex, &recursive_mutex_attr);
```

### 5. 使用互斥锁

```c
pthread_mutex_lock(&mutex);
// 代码块
pthread_mutex_unlock(&mutex);
```

### 6. 销毁互斥锁和互斥锁属性

```c
pthread_mutex_destroy(&mutex);
pthread_mutexattr_destroy(&recursive_mutex_attr);
```

## 代码示例

```c
pthread_mutex_t mutex;

void *routine()
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    printf("Hello world!\n");
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;

    pthread_mutexattr_t recursive_mutex_attr;
    pthread_mutexattr_init(&recursive_mutex_attr);
    pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex, &recursive_mutex_attr);
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
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&recursive_mutex_attr);
}
```

### 运行

```bash
gcc -o recursive_mutex recursive_mutex.c -pthread
./recursive_mutex
Hello world!
```

可以看到，只有一个线程输出了 `Hello world!`，这是因为只有一个线程获取了递归互斥锁，此线程加锁了两次，但只解锁了一次，导致其他线程无法获取递归互斥锁

### 解决方法——加锁次数与解锁次数相同

```c
pthread_mutex_t mutex;

void *routine()
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    printf("Hello world!\n");
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex); // 加锁次数与解锁次数相同
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;

    pthread_mutexattr_t recursive_mutex_attr;
    pthread_mutexattr_init(&recursive_mutex_attr);
    pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex, &recursive_mutex_attr);
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
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&recursive_mutex_attr);
}
```

### 运行
```bash
gcc -o recursive_mutex recursive_mutex.c -pthread
./recursive_mutex
Hello world!
Hello world!
```

## 原理

递归互斥锁有一个计数器，用于记录线程获取互斥锁的次数，当线程获取互斥锁时，计数器加一，当线程释放互斥锁时，计数器减一，当计数器为零时，互斥锁被释放

## 应用场景

- [多线程调用递归函数](多线程递归函数示例.c)
- 需要多次加锁的场景