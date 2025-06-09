#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) printf("errno: %d, strerror: %s\n", errno, strerror(errno));
}