#include <stdio.h>

constexpr int len = 10;
static int arr[len];

int main(void) {
    for (int i = 0; i < len; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; i < len; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}