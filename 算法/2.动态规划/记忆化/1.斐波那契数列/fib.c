#include <stdio.h>
#include <string.h>

int fib_memo(int n, int *memo)
{
    if (n <= 2) return 1;
    if (memo[n] != 0) return memo[n]; 
    memo[n] = fib_memo(n-1, memo) + fib_memo(n-2, memo); // 记忆化
}

int fib(int n)
{
    int memo[n+1]; // 用于保存计算结果
    memset(memo, 0, sizeof(int) * (n+1));
    return fib_memo(n, memo);
}

int main(int argc, const char* argv[]) {
    printf("%d\n", fib(40));
    return 0;
}