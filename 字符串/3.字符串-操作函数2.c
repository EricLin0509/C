// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

    //  字符串长度函数 strlen()，返回值不包含'\0'
    char str[10] = "1234";
    int nLen1 = strlen(str); // 结果是4
    int nLen2 = sizeof(str); // 结果是10

    printf("%d\n",nLen1);
    printf("%d\n",nLen2);



    // 字符串比较原理
    /*
    ABCDEFE <  ABCDEFG
    ABCDEF <  ABCDEFG
    */
    
    /*
    1. 可以是字符串常量，也可以是字符数组 (以\0结束的字符序列)
    2. 字符串常量或字符数组
    result = 0      相等
    result > 0      str1 > str2
    result < 0      str1 < str2
    */

    strcmp("123","123");

    char str1[] = "123";
    char str2[] = "123";
    int result = strcmp(str1,str2);

    if (result > 0)
    {
        printf("str1 > str2\n");
    }
    else if (result < 0)
    {
        printf("str1 > str2\n");
    }
    else
    {
        printf("str1 = str2\n");
    }
    


    /*
    字符串赋值函数
    strcpy()
    1. 字符数组 (内存大小足够大)
    2. 常量字符串、字符数组
    */

    char str3[20];
    char str4[] = "China";

    strcpy(str3,str4);
    printf("%s\n",str3);

    strcpy(str3,"sha");
    printf("%s\n",str3); // 输出结果为'sha'
    printf("%c\n",str3[4]); // 后面的内存并没有清除

    char str5[20];
    char str6[] = "China hello";

    str6[3] ='\0';

    strcpy(str5,str6);
    printf("%s\n",str5); // 输出结果为'Chi'


    // strncpy()
    char str7[30] = "beijing";
    char str8[20] = "love";

    strncpy(str7,str8,2);
    printf("str7 = %s\n",str7); // 输出结果是'loijing'

    char str9[30] = "beijing";
    char str10[20] = "love";

    strncpy(str9+1,str10+1,2); // +n是指从第n个索引开始替换
    printf("str7 = %s\n",str9); // 输出结果是'bovjing'

    return 0;
}