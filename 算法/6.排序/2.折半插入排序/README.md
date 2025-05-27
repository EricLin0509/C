# 折半插入排序

## 简介

折半插入排序相比于直接插入排序，减少了比较次数，但是移动次数不变

## 算法步骤

1. 从第一个元素开始，该元素可以认为已经被排序
2. 取出下一个元素，在已经**排序的元素序列二分查找**，直到第一个比它大的数
3. 将新元素插入到该位置后
4. 重复上述两步，直到所有元素都被插入到正确的位置

此算法的时间复杂度依旧为 O(n<sup>2</sup>)，但在数据量较大时，比直接插入排序更快

## 实现

```c
void binary_insertion_sort(int *arr, int len);
```

- `arr`：待排序的数组
- `len`：数组的长度

### 设置临时变量

```c
void binary_insertion_sort(int *arr, int len)
{
    int temp; // 临时变量
}
```

### 遍历数组

```c
void binary_insertion_sort(int *arr, int len)
{
    int temp; // 临时变量

    for (int i = 1; i < len; i++)
    {
        temp = arr[i]; // 取出下一个元素
    }
}
```

### 在已经排序的元素序列中二分查找

```c
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
    }
}
```

### 将新元素插入到该位置后

```c
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
```