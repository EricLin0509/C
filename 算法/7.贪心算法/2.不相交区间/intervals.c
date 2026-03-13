#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

static int cmp(const void *a, const void *b) // qsort 的比较函数
{
    Interval *interval_a = (Interval *)a;
    Interval *interval_b = (Interval *)b;
    if (interval_a->end == interval_b->end)
        return interval_a->start - interval_b->start; // 右端点相同则按照左端点排序

    return interval_a->end - interval_b->end; // 右端点不同则按照右端点排序
}

int maxNonOverlapping(Interval *intervals, int n)
{
    qsort(intervals, n, sizeof(Interval), cmp); // 按照右端点排序

    int count = 1; // 至少有一个区间
    int end = intervals[0].end; // 记录当前选择的区间的右端点

    for (int i = 0; i < n; i++)
    {
        if (intervals[i].start > end) // 选择的区间和当前选择的区间无交集
        {
            count++; // 计数加一
            end = intervals[i].end; // 更新当前选择的区间的右端点
        }
    }

    return count; // 返回不相交的区间数量
}

int main(void) {
    Interval intervals[] = {{1, 4}, {2, 3}, {4, 6}, {8, 9}};

    int n = sizeof(intervals) / sizeof(Interval);

    printf("%d\n", maxNonOverlapping(intervals, n)); // 输出 3 ({2, 3}, {4, 6}, {8, 9})

    return 0;
}