// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
#include<string.h>

char * mystrchr(const char * arr1, char ch) { // 返回 'char *' 类型的值
char * p = arr1;

while(*p != '\0')
{
    if (*p == ch)
    {
        return p;
    }
    p++;
}
return NULL;
}
int main(int argc, const char * argv[]) {

char arr1[] = "Hello world";
char ch = 'w ';
char * p = mystrchr(arr1, ch);
printf("%s\n",p);

return 0;

}