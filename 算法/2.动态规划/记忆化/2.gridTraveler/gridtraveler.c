#include <stdio.h>
#include <string.h>

size_t gridTraveler_memo(size_t m, size_t n, size_t (*memo)[n+1])
{
    if (m == 1 && n == 1) return 1;
    if (m == 0 || n == 0) return 0;
    if (memo[m][n] != 0) return memo[m][n];
    if(memo[n][m] != 0) return memo[n][m];
    memo[m][n] = gridTraveler_memo(m - 1, n, memo) + gridTraveler_memo(m, n - 1, memo);
    return memo[m][n];
}

size_t gridTraveler(size_t m, size_t n)
{
    size_t memo[m+1][n+1];
    size_t i = n+1;
    memset(memo, 0, sizeof(size_t) * (m+1) * (n+1));
    return gridTraveler_memo(m, n, memo);
}

size_t gridTraveler_loop(size_t m, size_t n)
{
    size_t table[m+1][n+1];
    memset(table, 0, sizeof(size_t) * (m+1) * (n+1));
    table[1][1] = 1;
    for (size_t i = 0; i <= m; i++)
    {
        for (size_t j = 0; j <= n; j++)
        {
            size_t current = table[i][j];
            if (j + 1 <= n) table[i][j+1] += current;
            if (i + 1 <= m) table[i+1][j] += current;
        }
    }
    return table[m][n];
}

int main(int argc, const char *argv[]) {
    printf("%zu\n", gridTraveler(4, 4)); // 6
    printf("%zu\n", gridTraveler_loop(4, 4)); // 6
    return 0;
}