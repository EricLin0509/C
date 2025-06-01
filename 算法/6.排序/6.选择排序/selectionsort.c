#include <stdio.h>

void selection_sort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++) // 遍历数组
    {
        int min = i; // 记录最小值的索引

        for (int j = i + 1; j < len; j++) // 遍历未排序的元素
        {
            if (arr[j] < arr[min]) min = j;
        }

        // 交换元素
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main(int argc, const char *argv[]) {
    int arr[] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    int len = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}