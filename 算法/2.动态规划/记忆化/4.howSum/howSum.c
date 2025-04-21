#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main(int argc, const char * argv[]) {
    int nums[] = {2, 3};
    int *result = howSum(7, nums, 2, &resultSize); // [3, 2, 2]
    for (int i = 0; i < resultSize; i++)
    {
        printf("%d ", result[i]);
    }
    resultSize = 0;
    printf("\n");

    int nums2[] = {7, 14};
    result = howSum(300, nums2, 2, &resultSize); // NULL
    for (int i = 0; i < resultSize; i++)
    {
        printf("%d ", result[i]);
    }
    resultSize = 0;
    return 0;
}