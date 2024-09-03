// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

char psw1 [20];
char psw2 [20];

scanf("%s",psw1);
scanf("%s",psw2);

if (strcmp(psw1, psw2)==0)
{
    printf("两次输入一致\n");
}
else
{
    printf("两次输入不一致\n");
}
return 0;
}