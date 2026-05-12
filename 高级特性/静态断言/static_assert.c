#include <stdio.h>
#include <assert.h>

#define FOO 0

static_assert(FOO == 10, "FOO should be 10");

#if FOO != 10
#error "FOO should be 10"
#endif

int main(void) {
    return 0;
}