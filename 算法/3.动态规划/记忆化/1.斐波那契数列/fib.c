#include <stdio.h>
#include <string.h>

size_t fib_memo(size_t n, size_t *memo)
{
    if (n <= 2) return 1;
    if (memo[n] != 0) return memo[n]; 
    memo[n] = fib_memo(n-1, memo) + fib_memo(n-2, memo); // 记忆化
    return memo[n];
}

size_t fib(size_t n)
{
    size_t memo[n+1]; // 用于保存计算结果
    memset(memo, 0, sizeof(size_t) * (n+1));
    return fib_memo(n, memo);
}

size_t fib_loop(size_t n)
{
    size_t memo[n]; // 用于保存计算结果
    memset(memo, 0, sizeof(size_t) * (n+1));
    if (n <= 2) return 1;
    memo[0] = 1;
    memo[1] = 1;
    for (size_t i = 2; i < n; i++)
    {
        memo[i] = memo[i-1] + memo[i-2];
    }
    return memo[n-1];
}

int main(int argc, const char* argv[]) {
    printf("%d\n", fib(40));
    printf("%d\n", fib_loop(40));
    return 0;
}