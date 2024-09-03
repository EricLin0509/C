// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 

int main(int argc, const char * argv[] ) {

int array[10];

for (int i = 0; i < 10; i++)
{
    scanf("%d",&array[i]);
}

for (int  i = 1; i <= 9; i++)
{
    int flag = 0;
    for (int j = 0; j < 10-i; j++)
    {
        if (array[j] > array[j+1])
        {
            int temp = array[j]; 
            array[j] = array[j+1];
            array[j+1] = temp;
            flag = 1;
        }
        
    }
    if (flag == 0)
    {
        break;
    }
}

int array1[10];
int array2[10];

int index1 = 0;
int index2 = 0;
for (int i = 0; i < 10; i++)
{
    if (array[i]%2 != 0)
    {
        array1[index1++] = array[i];
    }
    else
    {
        array2[index2++] = array[i];
    }
}

int newarray[10];

for (int i = 0; i < index1; i++)
{
    newarray[i] = array1[i];
}
for (int i = 0; i < index2; i++)
{
    newarray[index1+i] = array2[i];
}

for (int i = 0; i < 10; i++)
{
    printf("%d ",newarray[i]);
}
putchar('\n');

return 0;
}