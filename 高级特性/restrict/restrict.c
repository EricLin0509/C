#include <stdio.h>

void update_ptr(size_t *ptr1, size_t *ptr2, size_t *val)
{
    *ptr1 += *val;
    *ptr2 += *val;
}

void update_ptr_restrict(size_t *restrict ptr1, size_t *restrict ptr2, size_t *restrict val)
{
    *ptr1 += *val;
    *ptr2 += *val;
}

int main(void) {
    size_t a = 10, b = 20, c = 30;
    update_ptr(&a, &b, &c);
    printf("a = %zu, b = %zu\n", a, b);

    update_ptr_restrict(&a, &b, &c);
    printf("a = %zu, b = %zu\n", a, b);

    return 0;
}