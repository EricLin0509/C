#include <stdio.h>
#include <stdlib.h>

static void quick_swap(int *a, int *b)
{
    /* 使用异或交换两个变量的值 */ 
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void max_permutation(int *A, int n, int B)
{
    for (int i = 0; i < B; i++) // 进行B次交换
    {
        int max_index = i;
        for (int j = i + 1; j < n; j++) // 找出最大的数字的索引
        {
            if (A[max_index] < A[j])
                max_index = j;
        }
        quick_swap(A + i, A + max_index); // 交换最大的数字到最前面
    }
}

int main(void) {
    int A[] = {3, 2, 4, 1, 5};
    int B = 3;
    int n = sizeof(A) / sizeof(A[0]);
    max_permutation(A, n, B);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}