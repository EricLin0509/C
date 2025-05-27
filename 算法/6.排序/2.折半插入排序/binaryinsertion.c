#include <stdio.h>

void binary_insertion_sort(int *arr, int len)
{
    int temp; // 临时变量

    for (int i = 1; i < len; i++)
    {
        temp = arr[i]; // 取出下一个元素

        int left = 0; // 左指针
        int right = i - 1; // 右指针
        int mid; // 中间指针
        while (left <= right)
        {
            mid = left + (right - left) / 2; // 计算中间指针
            if (arr[mid] > temp) right = mid - 1; // 如果中间元素大于临时变量，右指针左移
            else left = mid + 1; // 如果中间元素小于等于临时变量，左指针右移
        }
        
        for (int j = i - 1; j >= left; j--)
        {
            arr[j + 1] = arr[j]; // 将元素后移
        }
        arr[left] = temp; // 将临时变量插入到该位置后
    }
}

int main(int argc, const char *argv[]) {
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int len = sizeof(arr) / sizeof(arr[0]);
    binary_insertion_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}