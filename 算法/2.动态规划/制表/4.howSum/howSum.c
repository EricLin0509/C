#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *howSum(int target, int *nums, int numsSize)
{
    int *table[target + 1]; // 创建一个基于 target 的数组
    
    for (int i = 0; i <= target; i++)
    {
        table[i] = NULL;
    }

    // 初始化 table[0] 为一个空数组，第一个元素记录数组大小
    table[0] = malloc(sizeof(int)); 
    table[0][0] = 0;

    for (int i = 0; i <= target; i++)
    {
        if (table[i] != NULL) // 如果 table[i] 不为 NULL，说明找到了一个组合
        {
            int size = table[i][0]; // 获取 table[i] 的大小
            int newSize = size + 1; // 增加一个元素

            for (int j = 0; j < numsSize; j++)
            {
                int sum = i + nums[j];
                if (sum <= target) // 如果 sum 小于等于 target
                {
                    table[sum] = malloc((newSize + 1) * sizeof(int)); // 分配新的内存，多一个位置存大小
                    table[sum][0] = newSize; // 更新 table[sum] 的大小
                    memcpy(table[sum] + 1, table[i] + 1, size * sizeof(int)); // 复制 table[i] 的内容到 table[sum]
                    table[sum][size + 1] = nums[j]; // 将 nums[j] 加入到 table[sum] 的末尾

                    if (sum == target) // 如果 sum 等于 target，说明找到了一个组合
                    {
                        return table[sum]; // 返回 table[sum]
                    }
                }
            }
        }
    }
    return table[target]; // 返回 table[target]
}

int main(int argc, const char * argv[]) {
    int nums[] = {2, 3};
    int size = 0;
    int *result = howSum(7, nums, 2); // [2, 2, 3]
    if (result == NULL)
    {
        printf("NULL!\n");
    }
    else
    {
        for (int i = 0; i < result[0]; i++)
        {
            printf("%d ", result[i+1]);
        }
    }
    printf("\n");

    int nums1[] = {2, 3, 5};
    size = 0;
    result = howSum(8, nums1, 3); // [3, 5]
    if (result == NULL)
    {
        printf("NULL!\n");
    }
    else
    {
        for (int i = 0; i < result[0]; i++)
        {
            printf("%d ", result[i+1]);
        }
    }
    printf("\n");
    
    int nums2[] = {7,14};
    size = 0;
    result = howSum(300, nums2, 2); // NULL
    if (result == NULL)
    {
        printf("NULL!\n");
    }
    else
    {
        for (int i = 1; i < result[0]; i++)
        {
            printf("%d ", result[i+1]);
        }
    }
    printf("\n");

    return 0;
}