#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t mutex;
pthread_cond_t cond;

void sum(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}

void sub(int a, int b)
{
    printf("%d - %d = %d\n", a, b, a - b);
}

// 任务
typedef struct Task
{
    void (*func)(int, int); // 函数指针
    int arg1, arg2;
} Task;

// 任务队列
Task taskQueue[1024];
int taskCount = 0; // 任务数量

// 执行任务的函数
void executeTask(Task *task)
{
    task->func(task->arg1, task->arg2);
}

void *startThread(void *arg)
{
    while (1)
    {
        Task task;

        pthread_mutex_lock(&mutex);
        while (taskCount == 0)
        {
            pthread_cond_wait(&cond, &mutex); // 等待任务
        }

        task = taskQueue[0]; // 获取任务
        for (int i = 0; i < taskCount - 1; i++) // 任务队列前移一位
        {
            taskQueue[i] = taskQueue[i + 1];
        }
        taskCount--;

        pthread_mutex_unlock(&mutex);

        executeTask(&task); // 要在锁外执行任务，否则只是一个线程在执行任务

    }
}

void submitTask(Task task)
{
    pthread_mutex_lock(&mutex);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond); // 通知线程池中的线程有任务了
}

int main(int argc, const char *argv[]) {
    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&thread[i], NULL, &startThread, NULL) != 0)
        {
            perror("pthread_create");
        }
    }

    // 提交任务
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

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(thread[i], NULL)!= 0)
        {
            perror("pthread_join");
        }
    }
    pthread_mutex_destroy(&mutex);
}
