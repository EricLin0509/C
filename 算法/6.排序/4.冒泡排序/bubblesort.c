#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int *arr, int len)
{
    bool flag = false; // 标记是否发生交换
    for (int i = 0; i < len - 1; i++) // 遍历整个数组
    {
        flag = false; // 重置标记
        for (int j = 0; j < len - 1 - i; j++) // 遍历未排序的数组
        {
            if (arr[j] > arr[j + 1]) // 如果前一个数大于后一个数
            {
                int temp = arr[j]; // 交换两个数
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true; // 发生交换
            }
        }
        if (!flag) break; // 如果没有发生交换，说明数组已经有序，可以提前结束排序
    }
}

int main(int argc, const char *argv[]) {
    int arr[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}