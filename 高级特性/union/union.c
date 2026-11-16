#include <stdio.h>

union MyUnion {
    char c;
    short a;
};

int main(void) {
    union MyUnion u;

    printf("sizeof(union MyUnion) = %zu\n", sizeof(union MyUnion));
    printf("u 的地址 = %p, u.c 的地址 = %p, u.a 的地址 = %p\n",
           (void *)&u, (void *)&u.c, (void *)&u.a);

    u.a = -1;
    printf("\nu.a = -1 之后\n");
    printf("u.a = %d (0x%x)\n", u.a, (unsigned)u.a);
    printf("u.c = %d (0x%x)\n", u.c, (unsigned char)u.c);

    u.c = 0;
    printf("\nu.c = 0 之后\n");
    printf("u.a = %d (0x%x)\n", u.a, (unsigned)u.a);
    printf("u.c = %d (0x%x)\n", u.c, (unsigned char)u.c);

    return 0;
}