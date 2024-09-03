// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int arr[2][3] = {{1,2,3},{4,5,6}};

for (int i = 1; i >= 0; i--)
{
    for (int j = 2; j >= 0; j--)
    {
        printf("%d ",arr[i][j]);
    }
    
}
printf("\n");

int arr1[2][3] = {1,2,4,3,6,5};
int array[6];

int index = 0;
for (int i = 0; i < 2; i++)
{
    for (int j = 0; j < 3; j++)
    {
        array[index++] = arr1[i][j];
    } 
}

for (int i = 0; i < 6; i++)
{
    printf("%d ",array[i]);
}
printf("\n");

for (int i = 1; i < 5; i++)
{
    int flag = 0;

    for (int j = 0; j < 6-i; j++)
    {
        if (array[j] > array[j+1])
        {
            int temp = array[j]; 
            array[j] = array[j+1];
            array[j+1] = temp;
            flag =1;
        }
        
    }
    if (flag == 0)
    {
        break;
    }
    
}

for (int i = 0; i < 6; i++)
{
    printf("%d ",array[i]);
}
printf("\n");

return 0;
}