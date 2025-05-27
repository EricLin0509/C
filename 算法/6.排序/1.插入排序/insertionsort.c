#include <stdio.h>

void insertion_sort(int *arr, int len)
{
    int temp; // 临时变量，用于存储未排序序列的第一个元素

    for (int i = 1; i < len; i++)
    {
        temp = arr[i]; // 取出未排序序列的第一个元素
        int j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j]; // 将已排序序列中大于新元素的元素向后移动一位
            j--;
        }
        arr[j + 1] = temp; // 将新元素插入到已排序序列中的正确位置
    }
}

int main(int argc, const char * argv[]) {
    int arr[] = {4, 2, 5, 1, 3, 6, 7, 8, 9, 0};
    int len = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}