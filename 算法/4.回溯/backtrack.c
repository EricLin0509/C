#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int total = 1 << numsSize; // 子集总数 2^n
    int **res = malloc(sizeof(int *) * total);
    *returnColumnSizes = malloc(sizeof(int) * total);
    *returnSize = 1; // 初始为空集
    res[0] = malloc(0); // 空集
    (*returnColumnSizes)[0] = 0;

    // 动态规划核心逻辑
    for (int i = 0; i < numsSize; i++)
    {
        int currentSize = *returnSize;
        // 将当前元素添加到所有现有子集中生成新子集
        for (int j = 0; j < currentSize; j++)
        {
            int newSize = (*returnColumnSizes)[j] + 1;
            res[*returnSize] = malloc(sizeof(int) * newSize);
            memcpy(res[*returnSize], res[j], sizeof(int) * (*returnColumnSizes)[j]);
            res[*returnSize][newSize - 1] = nums[i]; // 添加新元素
            (*returnColumnSizes)[*returnSize] = newSize;
            (*returnSize)++;
        }
    }
    return res;
}


int main(int argc, const char * argv[]) {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int *returnColumnSizes;
    int **result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1)
            {
                printf(",");
            }
        }
        printf("]\n");
    }
    return 0;
}