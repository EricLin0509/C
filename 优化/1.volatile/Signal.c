#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

volatile bool sig = false;

void handler(int signum)
{
    if (signum == SIGINT) // 终止信号
    {
        sig = true;
    }
}

int main(int argc, const char * argv[]) {
    printf("Press Ctrl+C to exit.\n");
    signal(SIGINT, handler); // 设置信号处理函数
    while (!sig) {} // 等待信号
    printf("Exiting...\n");
    return 0;
}