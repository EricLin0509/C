#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

    printf("pid: %d\n", getpid());

    if (pid != 0) {
        wait(NULL);
    }
}