#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
int distributeCandies(int *ratings, int ratingsSize)
{
    int candies[ratingsSize];
    for (int i = 0; i < ratingsSize; i++) candies[i] = 1;

    for (int i = 1; i < ratingsSize; i++) // 从左到右遍历
    {
        if (ratings[i] > ratings[i-1]) // 如果当前孩子评分比左边高
            candies[i] = candies[i-1] + 1;
    }

    for (int i = ratingsSize - 2; i >= 0; i--) // 从右到左遍历
    {
        if (ratings[i] > ratings[i+1]) // 如果当前孩子评分比右边高
            candies[i] = max(candies[i], candies[i+1] + 1);
    }

    int sum = 0;
    for (int i = 0; i < ratingsSize; i++) sum += candies[i];
    return sum;
}

int main(void) {
    int kids[] = {1, 7, 4, 3, 1};

    int sum = distributeCandies(kids, 5);
    printf("The minimum number of candies is %d.\n", sum);

    return 0;
}