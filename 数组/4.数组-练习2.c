// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int array[10];

for (int i = 0; i < 10; i++)
{
    scanf("%d",&array[i]);
}

int number =1;

while (1)
{
    int flag = 0;

    for (int i = 0; i < 10; i++)
    {
        if (number%array[i] != 0) 
        {
            flag = 1;
        }
        
    }
    

    if (flag == 0)
    {
        printf("最小公倍数是%d\n",number);
        break;
    }
    number++;
}
return 0;
}