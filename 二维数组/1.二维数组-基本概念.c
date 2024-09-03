// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

/*
int [3] 一维数组类型
*/

int array[3][3] = {{1,1,1},{2,2,2},{3,3,3}}; // 二维数组

/*
int a[3][4] 定义了一个3个元素的二维数组
数组中的妹一个元素是一个包含4个整形变量的一维数组 (先行后列)
*/

int array1[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
printf("%d\n",array1[2][0]);

int array2[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int array3[3][4] = {{1},{5},{9}};
printf("%d\n",array3[2][0]);

int array4[3][4] = {1,2};
printf("%d\n",array4[0][1]);

int arr[3][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};

for (int i = 0; i < 3; i++) // 外层控制哪一个子数组
{
    for (int j = 0; j < 5; j++) // 内层控制子数组中每个元素
    {
        printf("array[%d][%d] = %d" ,i, j, arr[i][j]);
    }
    
}
printf("\n");

return 0;
}