// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h> // 系统库文件 存放一些「字符串」操作函数
int main(int argc, const char * argv[] ) {

    /*
    注意：'' 表示一个字符，"" 表示字符串
    */

    char str1[] = {'C','h','i','n','a'}; // 不是字符串 (没有 "\0")
    char str2[] = "China";
    char* str3 = "China";

    printf("%ld %ld\n",sizeof(str1),sizeof(str2));

    // 清空字符串 字符串初始化函数
    // memset(数组名,要清理内存使用的数据,清理的字节数)

    // 字符串清理函数
    /*
    1. 要操作的字符数组
    2. 要写入的初始化数据
    3. 要清理的字符个数
    */
    memset(str1,'a',10);

    for (int i = 0; i < 10; i++)
    {
        printf("%c",str1[i]);
    }

    printf("%s\n",str1);

    char str4[10] = "Beijing";
    sizeof(str4); // 求字符数组内存大小

    char temp = str2[0];
    int index = 0;
    while (temp != '\0')
    {
        temp = str4[++index];
    }
    printf("%d\n",index);

    // 求字符串长度
    /*
    1. 要计算的字符数组的名字 (数组内必须存放完整的字符串)
    */
    int length = strlen(str4);
    printf("%ld\n",length);

    return 0;
}