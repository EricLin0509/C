#include <stdio.h>

int open_bulb(int *status, int n)
{
    int steps = 0;

    for (int i = 0; i < n; i++)
    {
        if (status[i] == 0)
        {
            status[i] ^= 1;
            steps++;
            for (int j = i + 1; j < n; j++)
            {
                status[j] ^= 1;
            }
        }
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