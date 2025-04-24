#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int *memo[1024]; // 记忆化数组
int memo_size[1024]; // 记忆化数组的大小

int* bestSum(int target, int* nums, int numsSize, int* returnSize)
{
    int minSize = INT_MAX; // 最小的结果数组大小
    int *minResult = NULL; // 最小的结果数组
    
    if (memo[target] != NULL) // 如果已经计算过，直接返回
    {
        *returnSize = memo_size[target]; // 返回结果数组的大小
        return memo[target]; // 返回结果数组
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

    for(int i = 0; i < numsSize; i++)
    {
        int remainder = target - nums[i];
        int remainderSize = 0; // 余数的结果数组大小
        int *remainderResult = bestSum(remainder, nums, numsSize, &remainderSize); // 递归调用bestSum函数
        if(remainderResult != NULL)
        {
            int *combination = malloc((remainderSize + 1) * sizeof(int)); // 结果数组的排列组合
            memcpy(combination, remainderResult, remainderSize * sizeof(int)); // 复制结果数组
            combination[remainderSize] = nums[i]; // 将当前数字加入结果数组
            if(remainderSize + 1 < minSize)
            {
                minSize = remainderSize + 1;
                minResult = combination;
            }
        }
    }
    memo[target] = minResult; // 将结果数组存入记忆化数组
    memo_size[target] = minSize; // 将结果数组的大小存入记忆化数组
    *returnSize = minSize; // 返回结果数组的大小
    return minResult; // 返回结果数组
}

int main(int argc, const char * argv[]) {
    int nums[] = {5, 3, 4, 7};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 7;
    int size = 0;
    int *result = bestSum(target, nums, numsSize, &size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", result[i]);
    }

    printf("\n");

    for (int i = 0; i < 1024; i++)
    {
        if (memo[i] != NULL)
        {
            free(memo[i]);
            memo[i] = NULL;
        }
    }

    int nums2[] = {3, 13, 23};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int target2 = 100;
    size = 0;
    int *result2 = bestSum(target2, nums2, numsSize2, &size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", result2[i]);
    }
    printf("\n");
    return 0;
}