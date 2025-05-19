#include <stdio.h>
#include <string.h>

int fib(int n)
{
    if (n == 0) return 0; // 边界条件
    if (n < 2) return 1; // 边界条件

    int arr[n + 1]; // 初始化数组
    memset(arr, 0, sizeof(arr)); // 将数组的所有元素设置为0

    arr[1] = 1; // 边界条件
    for (int i = 2; i <= n; i++) // 从第2项开始，将数组的第i项设置为数组的第i-1项和第i-2项的和
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n]; // 返回数组的第n项
}

int main(int argc, const char* argv[]) {
    printf("%d\n", fib(1)); // 1
    printf("%d\n", fib(40)); // 102334155
    return 0;
}