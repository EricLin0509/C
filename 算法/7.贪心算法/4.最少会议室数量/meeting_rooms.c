#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *a, const void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    if (x[0] != y[0]) return x[0] - y[0]; // 如果时间不同，则按照时间排序
    return x[1] - y[1]; // 如果时间相同，则按照类型排序，结束时间在前面
}

int minMeetingRooms(int (*intervals)[2], int n)
{
    int curr = 0;
    int res = 0;
    int list[n * 2][2];

    /* 开始时间 */
    for (int i = 0; i < n; i++)
    {
        list[i][0] = intervals[i][0];
        list[i][1] = 1; // 需要额外一个会议室
    }

    /* 结束时间 */
    for (int i = 0; i < n; i++)
    {
        list[i + n][0] = intervals[i][1];
        list[i + n][1] = -1; // 可以减少一个会议室
    }
    
    qsort(list, n * 2, sizeof(list[0]), cmp);

    for (int i = 0; i < n * 2; i++)
    {
        curr += list[i][1];
        if (curr > res)
            res = curr;
    }

    return res;
}

int main(void) {
    int intervals[][2] = {{0, 30}, {5, 10}, {15, 20}};
    int n = sizeof(intervals) / sizeof(intervals[0]);
    int res = minMeetingRooms(intervals, n);
    printf("%d\n", res);
    return 0;
}