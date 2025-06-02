#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *arr, int left1, int right1, int left2, int right2)
{
    int len1 = right1 - left1 + 1; // 左子数组长度
    int len2 = right2 - left2 + 1; // 右子数组长度

    int *left_arr = malloc(len1 * sizeof(int)); // 分配内存
    int *right_arr = malloc(len2 * sizeof(int)); // 分配内存

    memcpy(left_arr, arr + left1, len1 * sizeof(int)); // 复制左子数组
    memcpy(right_arr, arr + left2, len2 * sizeof(int)); // 复制右子数组

    int i = 0, j = 0, k = left1; // 初始化指针

    while (i < len1 && j < len2) // 遍历两个子数组
    {
        if (left_arr[i] <= right_arr[j]) // 比较两个子数组的元素
        {
            arr[k++] = left_arr[i++]; // 将较小的元素复制到合并数组
        }
        else
        {
            arr[k++] = right_arr[j++]; // 将较小的元素复制到合并数组
        }
    }
    
    while (i < len1) // 复制剩余的元素
    {
        arr[k++] = left_arr[i++]; // 将剩余的元素复制到合并数组
    }
    while (j < len2) // 复制剩余的元素
    {
        arr[k++] = right_arr[j++]; // 将剩余的元素复制到合并数组
    }

    // 释放内存
    free(left_arr);
    free(right_arr);
}

void merge_sort(int *arr, int left, int right)
{
    int len = right - left + 1; // 计算数组长度
    if (len <= 1) return; // 基准条件

    int mid = (left + right) / 2; // 计算中间位置

    // 递归调用
    merge_sort(arr, left, mid); // 左子数组
    merge_sort(arr, mid + 1, right); // 右子数组

    // 合并数组
    merge(arr, left, mid, mid + 1, right); // 合并数组
}

int main(int argc, const char *argv[]) {
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int len = sizeof(arr) / sizeof(arr[0]);
    merge_sort(arr, 0, len - 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0; 
}