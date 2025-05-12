#include <stdio.h>

int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (left > right) return -1; // 如果左边界大于右边界，说明找不到目标元素，返回 -1

    if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
    else if (arr[mid] > element) return binary_search(arr, element, left, mid - 1); // 如果中间点的值大于目标元素，在左半部分继续查找
    else return binary_search(arr, element, mid + 1, right); // 如果中间点的值小于目标元素，在右半部分继续查找
}

int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
        else if (arr[mid] > element) right = mid - 1; // 如果中间点的值大于目标元素，在左半部分继续查找
        else left = mid + 1; // 如果中间点的值小于目标元素，在右半部分继续查找
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13};

    printf("%d\n", binary_search(arr, 12, 0, 12));
    printf("%d\n", binary_search(arr, 14, 0, 12)); // 找不到目标元素，返回 -1

    printf("%d\n", binary_search_loop(arr, 12, 0, 12));
    printf("%d\n", binary_search_loop(arr, 14, 0, 12)); // 找不到目标元素，返回 -1
    return 0;
}