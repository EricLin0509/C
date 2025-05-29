#include <stdio.h>

void quick_sort(int *arr, int start, int end)
{
    if (start >= end) return; // 基准条件
    int pivot = arr[end]; // 选择基准元素

    int i = start - 1; // 指针 i
    int j = start; // 指针 j

    while (j < end) // 遍历数组
    {
        if (arr[j] < pivot) // 找到一个小于基准元素的元素
        {
            i++; // 指针 i 向后移动一位
            // 交换指针 i 和指针 j 所指向的元素
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        j++; // 指针 j 向后移动一位
    }
    
    // 交换指针 i 和基准元素
    i++;
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;

    // 计算下一个基准元素的位置
    int pivot_index = i;

    // 递归地对子数组进行排序
    quick_sort(arr, start, pivot_index - 1); // 左子数组
    quick_sort(arr, pivot_index + 1, end); // 右子数组
}

int main(int argc, const char *argv[]) {
    int arr[] = {8, 2, 5 ,3, 9, 4, 7, 6, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, len - 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}