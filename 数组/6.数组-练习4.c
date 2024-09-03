// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int array[5] = {1,2,3,4,5};
int number= 0;

for (int i = 4; i >= 0; i--)
{
    number = number*10 + array[i];
}

printf("number = %d\n",number);


int array1[5];
int array2[5];

for (int i = 0; i < 5; i++)
{
    scanf("%d",&array1[i]);
}
for (int i = 0; i < 5; i++)
{
    array2[i] = array1[i];
}
for (int i = 0; i < 5; i++)
{
    printf("%d ",array2[i]);
}
putchar('\n');

int array3[5] = {1,2,3,4,5};

for (int i = 0; i < 5/2; i++)
{
    int temp = array3[i];
    array3[i] = array3[4-i];
    array3[4-i] = temp;
}
for (int i = 0; i < 5; i++)
{
    printf("%d ",array3[i]);
}


return 0;
}