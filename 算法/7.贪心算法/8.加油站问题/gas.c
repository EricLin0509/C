#include <stdio.h>

int gasStation(int* A, int* B, int n)
{
    int total = 0; // 总剩余油量
    int curr = 0; // 当前段的净油量
    int candidate = 0; // 候选位置

    for (int i = 0; i < n; i++)
    {
        int diff = A[i] - B[i]; // 差值
        total += diff; // 总剩余油量增加
        curr += diff; // 当前段的净油量增加

        if (curr < 0)
        {
            candidate = i + 1; // 候选位置更新
            curr = 0; // 当前段的净油量重置
        }
    }

    return total >= 0 ? candidate : -1; // 如果总剩余油量大于等于0，则返回候选位置，否则返回-1
}

int main(void) {
    int A[] = {3, 5, 2, 1, 7};
    int B[] = {4, 2, 1, 9, 1};

    int start = gasStation(A, B, 5);

    printf("start position: %d\n", start);

    return 0;
}