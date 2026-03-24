#include <stdio.h>
#include <stdlib.h>

#define abs(x) ((x) > 0 ? (x) : (-(x)))

static int cmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int minTime(int* mice, int* holes, int n)
{
    /* 对数组进行排序 */ 
    qsort(mice, n, sizeof(int), cmp);
    qsort(holes, n, sizeof(int), cmp);

    int max_distance = 0;

    for (int i = 0; i < n; i++)
    {
        int distance = abs(mice[i] - holes[i]);
        if (distance > max_distance)
            max_distance = distance;
    }

    return max_distance;
}

int main(void) {
    int mice[] = {3, 2, -4};
    int holes[] = {0, -2, 4};

    int time = minTime(mice, holes, 3);
    printf("The minimum time is %d\n", time);

    return 0;
}