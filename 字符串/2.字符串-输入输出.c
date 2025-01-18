// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

    char c[] = "It's a computer";
    int j = 0;

    for (int i = 0; i < strlen("computer"); i++)
    {
        j =i+7; // 这里7指的是前面 "It's a "共7个字符
        printf("%c",c[j]);
    }
    printf("\n");

    // 格式化输入输出 scanf    prinf    %s
    char str[100] = "Good morning";
 
    scanf("%s",str); // 输入 "Hello", str 里的数据变成 "Hello\0orning\0"
    printf("%s\n",str);
        
    scanf("%3s",str); // 输入 "Hello", 则输出 "Hel"
    printf("%s\n",str);

    // 字符串和数组不需要取址符&

    /*
    字符输入输出函数
    char temp = getchar()
    purchar(字符)

    字符串输入输出函数
    gets(字符数组名) // 这里的字符数组名不能是常量
    puts(字符数组名 or 字符串常量)
    */

   char str1[100] = ""; // {} or "", 不能用 {""}, "" 不是数组标准的初始化方式且只能初始化时使用
   /*
   str1 = "";  ❌
   */

    char str2[100] = "ABC";
    printf("%s\n",str2); // 输出ABC

    char str3[100] = "ABC";
    str3[1] = '\0';
    printf("%s\n",str3); // 输出A

    /*
    char str4[4] = "ABC";
    str4[3] = 'D';
    printf("%s\n",str4); // 错误, 没有\0
    */

    return 0;
}