#include <stdio.h>

void print_int(int num)
{
    printf("%d\n", num);
}

void print_double(double num)
{
    printf("%f\n", num);
}

#define PRINT(num) _Generic(num, \
    int: print_int(num), \
    double: print_double(num), \
    default: printf("Unknown type\n"))

int main()
{
    PRINT(123);
    PRINT(3.14);
    PRINT(3.14F);
    return 0;
}