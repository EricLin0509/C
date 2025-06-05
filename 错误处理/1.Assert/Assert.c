#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[]) {
    char *str = NULL;
    assert(str != NULL);
    printf("%s\n", str);
    return 0;
}