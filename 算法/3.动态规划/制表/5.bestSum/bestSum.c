#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *bestSum(int targetSum, int *nums, int numsSize)
{
    int *table[targetSum + 1]; // 创建一个基于 targetSum 的数组

    for (int i = 0; i <= targetSum; i++)
    {
        table[i] = NULL; // 初始化数组
    }

    table[0] = malloc(sizeof(int)); // 初始化 table[0]
    table[0][0] = 0;

    for (int i = 0; i <= targetSum; i++)
    {
        if (table[i] != NULL)
        {
            int temp_new_size = table[i][0] + 1; // 临时变量，用于存储新数组的长度
            for (int j = 0; j < numsSize; j++)
            {
                int sum = i + nums[j]; // 索引加上偏移量
                if (table[sum] == NULL || table[sum][0] > temp_new_size && sum <= targetSum) // 如果新数组的长度小于旧数组的长度或数组为空
                {
                    table[sum] = malloc(sizeof(int) * (temp_new_size + 1)); // 分配内存
                    table[sum][0] = temp_new_size; // 存储新数组的长度
                    memcpy(table[sum] + 1, table[i] + 1, sizeof(int) * table[i][0]); // 复制数组
                    table[sum][temp_new_size] = nums[j]; // 存储新元素
                    if (sum == targetSum) // 如果索引等于目标值
                    {
                        return table[sum]; // 返回数组
                    }
                }
            }
        }
    }
    return table[targetSum]; // 返回数组
}

int main(int argc, const char * argv[]) {
    int nums[] = {5, 3, 4, 7};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 7;
    int *result = bestSum(target, nums, numsSize);
    for (int i = 0; i < result[0]; i++)
    {
        printf("%d ", result[i+1]);
    }
    printf("\n");

    int nums1[] = {2, 3, 5};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int target1 = 8;
    int *result1 = bestSum(target1, nums1, numsSize1);
    for (int i = 0; i < result1[0]; i++)
    {
        printf("%d ", result1[i+1]);
    }
    printf("\n");

    int nums2[] = {25, 1, 5, 2};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int target2 = 100;
    int *result2 = bestSum(target2, nums2, numsSize2);
    for (int i = 0; i < result2[0]; i++)
    {
        printf("%d ", result2[i+1]);
    }
    printf("\n");

    return 0;
}