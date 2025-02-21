# 什么是pthread_t

## pthread_t的定义

```c
typedef unsigned long int pthread_t;
```
pthread_t是一个无符号长整型

### 打印pthread_t

```c
pthread_t thread[2];

for(int i = 0; i < 2; i++)
{
    if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }
    printf("thread[%d] = %lu\n", i, thread[i]);
}
```

#### 运行

```bash
gcc -o pthread_t pthread_t.c -pthread
./pthread_t
thread[0] = 123162750322368
thread[1] = 123162741929664
```

这些数字是线程的ID，用于标记线程

### 使用pthread_self()获取线程ID
```c
void *routine(void *arg)
{
    pthread_t th = pthread_self();
    printf("thread ID = %lu\n", th);
}
```

## 不透明数据类型

在 pthread API 文档中，**pthread_t 被定义为一个不透明数据类型**，这意味着它的具体实现细节是不可见的 (有可能是int，也有可能是long，或者是其他数据类型)。这意味着你不能直接操作或比较 pthread_t 的值，而只能使用提供的函数来操作和比较它们


### sys_gettid (Linux独占)

```c
#include <unistd.h>
#include <sys/syscall.h>

void *routine(void *arg)
{
    pthread_t th = pthread_self();
    printf("thread ID = %lu\n", th);
    printf("thread syscall ID = %d\n", (pid_t)syscall(SYS_gettid));
}
```

[源代码](什么是pthread_t.c)

- `pid_t`: 是一个有符号整型，通常用于表示进程 ID
- `syscall`: 是一个系统调用函数，用于执行系统调用
- `SYS_gettid`: 是一个系统调用号，用于获取线程 ID

#### 运行

```bash
gcc -o pthread_t pthread_t.c -pthread
./pthread_t
thread ID = 139571158324928
thread syscall ID = 18777
thread ID = 139571166717632
thread syscall ID = 18776
```

### 区别

`pthread_t` 里的ID是由pthread API管理，而 `syscall(SYS_gettid)` 里的ID是由操作系统管理