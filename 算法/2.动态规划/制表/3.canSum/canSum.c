#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canSum(int target, int *nums, int numsSize)
{
    bool table[target + 1]; // 创建一个大小为target+1的布尔数组
    memset(table, false, sizeof(table)); // 将数组初始化为false
    table[0] = true; // 边界条件，canSum(0, [...]) 为 true

    for (int i = 0; i <= target; i++)
    {
        if (table[i] == false) continue; // 如果当前位置为false，跳过

        for (int j = 0; j < numsSize; j++) // 遍历数组中的每个元素，作为偏移量
        {
            if (i + nums[j] > target) continue; // 如果偏移量加上当前位置大于目标值，跳过
            table[i + nums[j]] = true; // 将偏移量加上当前位置的位置设置为true
        }
    }
    return table[target]; // 返回目标值的位置，即canSum(target, [...])的结果
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