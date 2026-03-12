#include <stdio.h>

int open_bulb(int *status, int n)
{
    int steps = 0;
    for (int i = 0; i < n; i++)
    {
        if (steps & 1 == 1) // 奇数步数，反转状态
            status[i] ^= 1;
        else // 偶数步数，保持状态
            status[i] &= 1;

        if (status[i] & 1 == 1) continue; // 灯泡已经打开，跳过
        else steps++; // 灯泡未打开，打开灯泡
    }

    return steps;
}

int main(void) {
    int status[] = {0, 1, 0, 1, 1, 0, 1, 1};
    int steps = open_bulb(status, 8);

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", status[i]);
    }
    printf("\n");
    printf("Steps: %d\n", steps);

    return 0;
}