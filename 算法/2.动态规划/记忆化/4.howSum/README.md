# howSum

## 问题描述

给定一个数组和一个目标数，求数组中是否存在一个子数组，使得子数组的和等于目标数

条件:
- 数组中的元素都是正整数
- 数组中的元素可以重复使用
- 如果有多个子数组，返回任意一个
- 如果没有子数组，返回空数组

示例:
- 输入: 7, [5, 3, 4, 7] —— 输出: [3, 4]
- 输入: 7, [2, 4] —— 输出: []
- 输入: 8, [2, 3, 5] —— 输出: [2, 2, 2, 2]

## 解题思路

使用递归的方式解决，每次递归时，将目标值减去数组中的一个元素，然后将此元素加入到结果数组中，然后递归调用canSum函数，直到目标值为0或者小于0，等于0时返回结果数组，小于0时返回空数组

![howSum](imgs/howSum.png)
![howSum](imgs/howSum_result.png)

这里以 howSum(7, [5, 3, 4, 7]) 为例

```c
int result[1024]; // 结果数组
int resultSize = 0; // 结果数组的大小
int *howSum(int target, int *nums, int numsSize, int *returnSize)
{
    if (target == 0) return result; // 目标值为0，返回结果数组
    if (target < 0) return NULL; // 目标值小于0，返回空数组
    for (int i = 0; i < numsSize; i++)
    {
        int remainder = target - nums[i]; // 计算剩余的目标值
        int *remainderResult = howSum(remainder, nums, numsSize, returnSize); // 递归调用canSum函数
        if (remainderResult != NULL) // 找到一个组合，返回结果数组
        {
            result[resultSize++] = nums[i]; // 将此元素加入到结果数组中
            return result; // 返回结果数组
        }
    }
    return NULL; // 没有找到一个组合，返回空数组
}
```

但是这种解法的时间复杂度为O(n<sup>m</sup>)，空间复杂度为O(m)

## 过程图分析

这里以 howSum(8, [2, 3, 5]) 为例
![step1](imgs/step1.png)

我们可以看到，所有 `3` 的分支都是相同的
![step2](imgs/step2.png)

那么我们可以使用记忆化的方式来优化这个问题

## 使用动态规划实现

`memo[1024][2]` 表示键值对，键为地址，值为结果数组的地址

`memo[1024][0]` 表示是否已经计算过，`memo[1024][1]` 表示结果数组


```c
int result[1024]; // 结果数组
int resultSize = 0; // 结果数组的大小
int *memo[1024][2]; // 记忆化数组
int *howSum(int target, int *nums, int numsSize, int *returnSize)
{
    if (memo[target][0] != NULL) return memo[target][1]; // 已经计算过，返回结果数组
    if (target == 0) return result; // 目标值为0，返回结果数组
    if (target < 0) return NULL; // 目标值小于0，返回空数组
    for (int i = 0; i < numsSize; i++)
    {
        int remainder = target - nums[i]; // 计算剩余的目标值
        int *remainderResult = howSum(remainder, nums, numsSize, returnSize); // 递归调用canSum函数
        if (remainderResult!= NULL) // 找到一个组合，返回结果数组
        {
            result[resultSize++] = nums[i]; // 将此元素加入到结果数组中
            memo[target][0] = result; //  表示已经计算过
            memo[target][1] = malloc(sizeof(int) * resultSize);
            memcpy(memo[target][1], result, sizeof(int) * resultSize); // 将结果数组加入到记忆化数组中
            return result; // 返回结果数组
        }
    }
    memo[target][0] = result; //  表示已经计算过
    memo[target][1] = NULL; // 将空数组加入到记忆化数组中
    return NULL; // 没有找到一个组合，返回空数组
}
```

此时的时间复杂度为O(n*m<sup>2</sup>)，空间复杂度为O(m<sup>2</sup>)