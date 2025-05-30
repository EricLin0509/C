#include <stdio.h>
#include <stdbool.h>

bool memo[1024][2]; // 记忆化数组
bool canSum(int target, int *nums, int numsSize)
{
    if (memo[target][0]) return memo[target][1]; // 如果已经计算过，直接返回结果

    if (target == 0) return true; // 目标值为0，返回true
    if (target < 0) return false; // 目标值小于0，返回false

    for (int i = 0; i < numsSize; i++)
    {
        int remainder = target - nums[i]; // 计算剩余的目标值
        if (canSum(remainder, nums, numsSize)) // 递归调用canSum函数
        {
            memo[target][0] = true; // 此键值对已经计算过
            memo[target][1] = true; // 记录计算结果
            return true; // 找到一个组合，返回true
        }
    }

    memo[target][0] = true; // 此键值对已经计算过
    memo[target][1] = false; // 记录计算结果
    return false; // 没有找到任何组合，返回false
}

int main(int argc, const char * argv[]) {
    int nums1[] = {7, 14};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    bool result1 = canSum(300, nums1, numsSize1); // false
    printf("%d\n", result1);

    int nums2[] = {2, 3, 5};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    bool result2 = canSum(8, nums2, numsSize2); // true
    printf("%d\n", result2);
    return 0;
}