#include <stdio.h>
#include <string.h>

size_t gridTraveler(size_t m, size_t n)
{
    size_t grid[m + 1][n + 1]; // 创建一个 m+1 x n+1 的二维数组
    memset(grid, 0, sizeof(grid)); // 将数组初始化为 0
    grid[1][1] = 1; // 初始条件，左上角只有一种走法
    for (size_t i = 1; i <= m; i++) // 遍历行
    {
        for (size_t j = 1; j <= n; j++) // 遍历列
        {
            size_t current = grid[i][j]; // 当前格子的值
            if (j + 1 <= n) // 如果没有碰到右侧边界
            {
                grid[i][j + 1] += current; // 右侧格子的值加上当前格子的值
            }
            if (i + 1 <= m) // 如果没有碰到下侧边界
            {
                grid[i + 1][j] += current; // 下侧格子的值加上当前格子的值
            }
        }
    }
    return grid[m][n]; // 返回右下角的值
}

int main(int argc, const char *argv[]) {
    printf("%zu\n", gridTraveler(3, 3)); // 输出 6
    printf("%zu\n", gridTraveler(18, 18)); // 输出 2333606220
    return 0;
}