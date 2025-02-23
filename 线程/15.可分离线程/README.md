# 可分离线程

## 可分离线程的函数——pthread_detach

```c
int pthread_detach (pthread_t __th) __THROW;
```

## 用处

`pthread_detach`函数可以让线程在终止时自动释放资源，而不需要使用`pthread_join`函数来等待线程的终止

## 代码示例

### 使用pthread_detach

```c
#define THREAD_NUM 2

void *routine(void *arg)
{
    sleep(1);
    printf("Finished\n");
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
        pthread_detach(thread[i]);
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }

    return 0;
}
```

### 运行

```bash
gcc -o detach detach.c -pthread
./detach
pthread_join: Success
```

可以看到，程序在`pthread_join`处报错，原因是线程已经被分离了，不能再被`join`

### 去除pthread_join

```c
#define THREAD_NUM 2

void *routine(void *arg)
{
    sleep(1);
    printf("Finished\n");
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
        pthread_detach(thread[i]);
    }

    pthread_exit(NULL); // 等待其他线程结束，防止主线程提前结束

    return 0;
}
```

### 再次运行

```bash
gcc -o detach detach.c -pthread
./detach
Finished
Finished
```

可以看到，程序没有报错，线程已经被分离了

## 单独设置可分离线程

在`pthread_create`函数中，第二个参数可以设置线程的属性，其中就包括可分离线程

```c
const pthread_attr_t *attr
```

### 设置线程属性

```c
pthread_attr_t DetachAttr;
```

### 初始化线程属性

```c
pthread_attr_t DetachAttr;

pthread_attr_init(&DetachAttr);
```

### 设置线程属性为可分离线程

```c
pthread_attr_t DetachAttr;

pthread_attr_init(&DetachAttr);
pthread_attr_setdetachstate(&DetachAttr, PTHREAD_CREATE_DETACHED);
```

### 使用可分离线程

```c
int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    pthread_attr_t DetachAttr;

    pthread_attr_init(&DetachAttr);
    pthread_attr_setdetachstate(&DetachAttr, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], &DetachAttr, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    pthread_exit(NULL); // 等待其他线程结束，防止主线程提前结束

    return 0;
}
```

### 销毁线程属性

```c
pthread_attr_t DetachAttr;

pthread_attr_init(&DetachAttr);
pthread_attr_setdetachstate(&DetachAttr, PTHREAD_CREATE_DETACHED);
```

### 使用可分离线程

```c
int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    pthread_attr_t DetachAttr;

    pthread_attr_init(&DetachAttr);
    pthread_attr_setdetachstate(&DetachAttr, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], &DetachAttr, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    pthread_attr_destroy(&DetachAttr);

    pthread_exit(NULL); // 等待其他线程结束，防止主线程提前结束

    return 0;
}
```

[源代码](可分离线程.c)

### 运行

```bash
gcc -o detach detach.c -pthread
./detach
Finished
Finished
```
