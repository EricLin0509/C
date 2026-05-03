#include <stdio.h>
#include <stdarg.h>

void sum_all(int total, ...)
{
    va_list ap;
    va_start(ap, total);

    int sum = 0;
    for (int i = 0; i < total; i++)
    {
        int arg = va_arg(ap, int);
        sum += arg;
    }
    printf("sum = %d\n", sum);

    va_end(ap);
}

int main(int argc, const char *argv[])
{
    sum_all(3, 1, 2, 3);
    sum_all(5, 4, 5, 6, 7, 8);
    return 0;
}