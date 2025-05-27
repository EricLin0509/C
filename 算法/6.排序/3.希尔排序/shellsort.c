#include <stdio.h>

void shell_sort(int *arr, int len)
{
    int gap = len / 2; // 计算增量序列
    while (gap > 0)
    {
        for (int i = gap; i < len; i++)
        {
            int j = i; // 记录当前元素的下标   
            while (j >= gap && arr[j] < arr[j - gap]) // 对每组进行插入排序
            {
                // 交换元素
                int temp = arr[j];
                arr[j] = arr[j - gap];
                arr[j - gap] = temp;
                j -= gap; // 继续向前遍历
            }
        }
        gap /= 2; // 缩小增量序列
    }
}

int main(int argc, const char *argv[]) {
    int arr[] = {1, 5, 3, 7, 9, 2, 4, 6, 8, 0, 10};
    int len = sizeof(arr) / sizeof(arr[0]);
    shell_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}