# 线程与进程的区别

## 代码

### 进程

```c
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid != 0) {
        wait(NULL);
    }
```

### 线程

```c
    void *threadFunc();
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &threadFunc, NULL) != 0)
    {
        return 1;
    }

    if (pthread_create(&thread2, NULL, &threadFunc, NULL) != 0)
    {
        return 1;
    }
    
    if (pthread_join(thread, NULL) != 0)
    {
        return 2;
    }
```

## 检测两者的 pid

### 进程

```c
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    printf("pid = %d\n", pid); // 两个进程的 pid

    if (pid != 0) {
        wait(NULL);
    }
```
[源代码](进程.c)

#### 运行

```bash
gcc -o process process.c

./process

pid = 26932
pid = 26938
```

可以看到两个进程的 pid 不同

### 线程

```c
    void *threadFunc()
    {
        printf("thread pid = %d\n", getpid());
    }
```
[源代码](线程.c)

#### 运行

```bash
gcc -o thread thread.c -pthread

./thread

thread pid = 26932
thread pid = 26932
```
可以看到两个线程的 pid 相同

### 总结

这说明一个进程可以有多个线程，但是线程是共享进程的资源的

`fork` 相当于将此进程所有东西都复制一份到新的进程

## 另外的检测方法

### 进程

```c
    int x = 2;
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    
    if (pid!= 0) {
        x++;
    }
    sleep(2);
    printf("x = %d\n", x);
```

#### 运行

```bash
gcc -o process process.c

./process

x = 2
x = 3
```
可以看到父进程和子进程的 x 是不同的

### 线程

```c
int x = 2;
    
void *threadFunc1()
{
    x++;
    sleep(2);
    printf("thread1 x = %d\n", x);
}

void *threadFunc2()
{
    printf("thread2 x = %d\n", x);
}

int main() {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &threadFunc1, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&thread2, NULL, &threadFunc2, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL)!= 0)
    {
        return 2;
    }
}
```

#### 运行
```bash
gcc -o thread thread.c -pthread

./thread

thread1 x = 3
thread2 x = 3
```

可以看到两个线程的 x 是相同的

## 两者内存的区别

**进程的内存是独立的，线程的内存是共享的**

## 总结

| 方面 | 进程 | 线程 |
| :---: | :---: | :---: |
| 代码 | 独立 | 共享 |
| 数据 | 独立 | 共享 |
| 堆栈 | 独立 | 共享 |




