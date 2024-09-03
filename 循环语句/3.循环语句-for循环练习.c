// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/*
int sum = 0;

for (int i = 0; i <=100; i++)
{
    if (i%3==0)
        {
            sum += i;
        }
}

printf("sum=%d\n",sum);
*/

for (int  i = 1; i <=9; i++)
{
    for (int k = i; k <=9; k++)
    {
        printf("%d ",k);
    }
    printf("\n");
}


return 0;
}