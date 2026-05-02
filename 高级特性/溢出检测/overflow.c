#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdckdint.h>

int main(void) {
    int a = INT_MAX - 10;
    int b = 1;
    int c = 0;

    if (ckd_add(&c, a, b))
        printf("Overflow or underflow occurred!\n");
    else
        printf("Result: %d\n", c);

    b = 100000;

    if (ckd_add(&c, a, b))
        printf("Overflow or underflow occurred!\n");
    else
        printf("Result: %d\n", c);

    a = INT_MIN;
    b = -1;

    if (ckd_add(&c, a, b))
        printf("Overflow or underflow occurred!\n");
    else
        printf("Result: %d\n", c);

    return 0;
}