#include <stdio.h>

#define SUM 100 + 200

constexpr int sum = 100 + 200;

int main(void) {
    int b = SUM * 2;
    printf("SUM * 2 = %d\n", b);

    int c = sum * 2;
    printf("sum * 2 = %d\n", c);

    return 0;
}