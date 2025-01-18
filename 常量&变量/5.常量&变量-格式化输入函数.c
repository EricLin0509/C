// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

    int num1 = 0;
    char num2 = 0;

    scanf("%d",&num1);
    scanf("\n%c",&num2);
//& 取址符
    printf("num1 = %d",num1);
    printf("num2 = %c\n",num2);

    return 0;
}