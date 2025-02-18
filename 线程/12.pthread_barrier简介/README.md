# pthread_barrier简介

## 定义

pthread_barrier是一个同步工具，用于线程间的同步

## 使用方法

### 创建pthread_barrier

```c
pthread_barrier_t barrier;
```

### 初始化pthread_barrier

#### 先看一下pthread_barrier_init原型

```c
int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned count);
```

#### 参数

- `*barrier`: 用于存储`pthread_barrier`的信息
- `*attr`: 用于设置`pthread_barrier`的属性
- `count`: 用于设置`pthread_barrier`的初始化值


#### 示例

```c
pthread_barrier_t barrier;

int main() {
    pthread_t thread[2];
    pthread_barrier_init(&barrier, NULL, 2);
}
```

### 销毁pthread_barrier

```c
pthread_barrier_t barrier;

int main() {
    pthread_t thread[2];
    pthread_barrier_init(&barrier, NULL, 2);
    pthread_barrier_destroy(&barrier);
}
```

### 等待pthread_barrier

在入口函数部分

```c
void *thread_func(void *args)
{
    pthread_barrier_wait(&barrier);
}
```

## 代码示例

### 编写入口函数

```c
pthread_barrier_t barrier;

void *routine(void *args)
{
    printf("Waiting at the barrier....\n");
    pthread_barrier_wait(&barrier);
    printf("Passed barrier\n");
}
```

### main函数

```c
int main(int argc, const char *argv[]) {
    pthread_t thread[2];
    pthread_barrier_init(&barrier, NULL, 3);

    for(int i = 0; i < 2; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < 2; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            return 2;
        }
    }
    pthread_barrier_destroy(&barrier);
}
```

### 运行

```bash
gcc -o pthread_barrier pthread_barrier.c -pthread
./pthread_barrier
Waiting at the barrier....
Waiting at the barrier....
```

可以看到程序运行两次后就卡住了，因为`pthread_barrier`的初始化值为3，而我们创建了两个线程，所以需要等待3个线程到达`pthread_barrier`才能继续执行

### 创建9个线程

```c
int main(int argc, const char *argv[]) {
    pthread_t thread[9];
    pthread_barrier_init(&barrier, NULL, 3);

    for(int i = 0; i < 9; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < 9; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            return 2;
        }
    }
    pthread_barrier_destroy(&barrier);
}
```

### 再次运行

```bash
gcc -o pthread_barrier pthread_barrier.c -pthread
./pthread_barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Passed barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Passed barrier
Passed barrier
```

可以看到输出是每3个线程同时输出一次`Passed barrier`，而其他线程则会等待

### 创建10个线程

```c
int main(int argc, const char *argv[]) {
    pthread_t thread[10];
    pthread_barrier_init(&barrier, NULL, 3);

    for(int i = 0; i < 10; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            return 2;
        }
    }
    pthread_barrier_destroy(&barrier);
}
```

[源代码](pthread_barrier简介.c)

### 再次运行

```bash
gcc -o pthread_barrier pthread_barrier.c -pthread
./pthread_barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Passed barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Waiting at the barrier....
Waiting at the barrier....
Waiting at the barrier....
Passed barrier
Passed barrier
Passed barrier
Passed barrier
```

可以看到，程序运行9次后卡住了，因为`pthread_barrier`的初始化值为3，而我们创建了10个线程，所以第10个线程需要等待另外2个线程

## 总结

`pthread_barrier`会等待指定数量的线程到达`pthread_barrier`后，再继续执行