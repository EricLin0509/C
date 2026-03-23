#include <stdio.h>
#include <string.h>

#define abs(x)((x) < 0 ? (x) * -1 : (x)) // 绝对值

int minMoves(char *s)
{
    int size = strlen(s);
    int x_count = 0;
    int x_index[size];

    for (int i = 0; i < size; i++)
    {
        if (s[i] == 'x' || s[i] == 'X') // 不区分大小写
            x_index[x_count++] = i;
    }

    int mid = x_index[x_count / 2]; // 中位数

    int moves = 0;
    int start_pos = mid - x_count / 2; // 计算连续x的起始位置
    for (int i = 0; i < x_count; i++)
    {
        int x_pos = x_index[i];
        moves += abs(x_pos - start_pos); // 计算移动次数
        start_pos++; // 移动到下一个位置
    }

    return moves;
}

int main(void) {
    char *s = "...x..x.";
    int moves = minMoves(s);
    printf("%d\n", moves);

    s = ".x..x..xx.";
    moves = minMoves(s);
    printf("%d\n", moves);

    s = "xx..xx....xxx";
    moves = minMoves(s);
    printf("%d\n", moves);

    return 0;
}