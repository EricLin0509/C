#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *memo[1024]; // 记忆化数组
int memo_size[1024]; // 记忆化数组的大小

int *howSum(int target, int *nums, int numsSize, int *returnSize)
{
    if (memo[target] != NULL)
    {
        *returnSize = memo_size[target]; // 如果已经计算过，直接返回结果
        return memo[target]; // 如果已经计算过，直接返回结果
    }

    if(target == 0) // 目标值为0，返回空数组
    {
        *returnSize = 0; // 返回空数组的大小
        return malloc(0); // 返回空数组
    }
    if(target < 0) // 目标值小于0，返回空指针
    {
        *returnSize = 0; // 返回空数组的大小
        return NULL; // 返回空指针
    }

    for (int i = 0; i < numsSize; i++)
    {
        int remainder = target - nums[i]; // 计算剩余的目标值
        int reminderSize = 0; // 结果数组的大小
        int *reminderResult = howSum(remainder, nums, numsSize, &reminderSize); // 递归调用canSum函数
        if (reminderResult != NULL) // 找到一个组合，返回结果数组
        {
            reminderResult[reminderSize++] = nums[i]; // 将此元素加入到结果数组中
            *returnSize = reminderSize; // 更新结果数组的大小
            if (memo[target]!= NULL && memo_size[target]!= 0) // 如果需要更新，释放内存
            {
                free(memo[target]); // 释放内存
            }
            memo[target] = malloc((reminderSize + 1) * sizeof(int)); // 分配内存
            memcpy(memo[target], reminderResult, reminderSize * sizeof(int)); // 复制结果数组到记忆化数组中
            memo_size[target] = reminderSize + 1; // 更新记忆化数组的大小
            return memo[target]; // 返回结果数组
        }
    }
    memo[target] = NULL; // 没有找到一个组合，返回空数组
    memo_size[target] = 0; // 没有找到一个组合，返回空数组
    return NULL; // 没有找到一个组合，返回空数组
}

int main(int argc, const char * argv[]) {
    int nums[] = {2, 3};
    int size = 0;
    int *result = howSum(7, nums, 2, &size); // [3, 2, 2]
    for (int i = 0; i < size; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    int nums2[] = {7,14};
    size = 0;
    result = howSum(300, nums2, 2, &size); // NULL
    for (int i = 0; i < size; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}