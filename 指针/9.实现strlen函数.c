// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
#include<string.h>


int mystrlen(char * str) {
/*
int 指的是返回 int 类型的值
char * str 指的是接收 char * 类型的值
*/
int counter = 0;
while (*str != '\0')
{
    counter++;
    str++;
}
return counter;

}

int mystrlen2(char * str) {
char * start = str;
while (*str != '\0')
{
    str++;
}
return str - start;

}

int main(int argc, const char * argv[]) {
int len = mystrlen("abc");
int len2 = mystrlen2("abc");
printf("%d\n",len);
printf("%d\n",len2);
return 0;

}