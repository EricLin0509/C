# 二分查找

## 定义

二分查找是一种高效的查找算法，用于在**有序数组**中查找特定元素的位置

## 原理

假设现在有一个有序数组，样式如下：

```
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
```

要查找的元素是 12

如果使用顺序查找，需要从第一个元素开始逐个比较，直到找到目标元素或遍历完整个数组

但是二分查找从中间元素开始，即 7 开始比较，因为 7 小于 12，**那可以确定的是 7 前面的元素都小于 12**，可以直接跳过这些元素，只需要在 7 后面的元素中查找

然后**不断缩小查找范围**，直到找到目标元素或确定目标元素不存在

## 递归实现

### 函数原型

```c
int binary_search(int *arr, int element, int left, int right);
```

- `arr` —— 有序数组
- `element` —— 要查找的元素
- `left` —— 左边界
- `right` —— 右边界

### 设置中间点

`(right - left) / 2` 是为了计算中间点的索引

```c
int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;
}
```

### 如果中间点的值等于目标元素

如果中间点的值等于目标元素，直接返回中间点的索引

```c
int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
}
```

### 如果中间点的值大于目标元素

如果中间点的值大于目标元素，说明目标元素在中间点的左边，需要在左半部分继续查找

那**左边界不改变，右边界改为中间点的前一个元素**，然后递归调用函数

```c
int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
    else if (arr[mid] > element) return binary_search(arr, element, left, mid - 1); // 如果中间点的值大于目标元素，在左半部分继续查找
}
```

### 如果中间点的值小于目标元素

如果中间点的值小于目标元素，说明目标元素在中间点的右边，需要在右半部分继续查找

那**右边界不改变，左边界改为中间点的后一个元素**，然后递归调用函数

```c
int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
    else if (arr[mid] > element) return binary_search(arr, element, left, mid - 1); // 如果中间点的值大于目标元素，在左半部分继续查找
    else return binary_search(arr, element, mid + 1, right); // 如果中间点的值小于目标元素，在右半部分继续查找
}
```

### 找不到目标元素的情况

如果找不到目标元素，即**左边界大于右边界**，则返回 -1

```c
int binary_search(int *arr, int element, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (left > right) return -1; // 如果左边界大于右边界，说明找不到目标元素，返回 -1

    if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
    else if (arr[mid] > element) return binary_search(arr, element, left, mid - 1); // 如果中间点的值大于目标元素，在左半部分继续查找
    else return binary_search(arr, element, mid + 1, right); // 如果中间点的值小于目标元素，在右半部分继续查找
}
```

## 循环实现

### 函数原型

```c
int binary_search_loop(int *arr, int element, int left, int right);
```

- `arr` —— 有序数组
- `element` —— 要查找的元素
- `left` —— 左边界
- `right` —— 右边界

### 循环条件

如果左边界小于等于右边界，说明还有元素需要查找，继续循环

```c
int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right) {   }
}
```

### 设置中间点

**中间点每次循环都需要重新计算，因为左边界和右边界可能会改变**

```c
int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
    }
}
```

### 如果中间点的值等于目标元素

如果中间点的值等于目标元素，直接返回中间点的索引

```c
int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
    }
}
```

### 如果中间点的值大于目标元素

如果中间点的值大于目标元素，说明目标元素在中间点的左边，需要在左半部分继续查找

那**左边界不改变，右边界改为中间点的前一个元素**，然后继续循环

```c
int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
        else if (arr[mid] > element) right = mid - 1; // 如果中间点的值大于目标元素，在左半部分继续查找
    }
}
```

### 如果中间点的值小于目标元素

如果中间点的值小于目标元素，说明目标元素在中间点的右边，需要在右半部分继续查找

那**右边界不改变，左边界改为中间点的后一个元素**，然后继续循环

```c
int binary_search_loop(int *arr, int element, int left, int right)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == element) return mid; // 如果中间点的值等于目标元素，返回中间点的索引
        else if (arr[mid] > element) right = mid - 1; // 如果中间点的值大于目标元素，在左半部分继续查找
        else left = mid + 1; // 如果中间点的值小于目标元素，在右半部分继续查找
    }
}
```

### 找不到目标元素的情况

如果找不到目标元素，即**循环结束 (left > right)**，则返回 -1

```c
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
```