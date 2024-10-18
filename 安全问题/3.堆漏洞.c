// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {

    // 堆检查器漏洞
    char *password;
    char *snffier;
    password = malloc(10 * sizeof(char));
    printf("Enter your password: ");

    fgets(password, 10, stdin);

    snffier = password;

    free(password);

    printf("%zu\n",password);
   
    for (int i = 0; i < 10; i++)
    {
        printf("%c",*(snffier + i)); // 依然能读取到密码，造成安全漏洞
    }

    /*
    这种漏洞叫堆检查器漏洞
    原理是内存在释放前，没有安全清除里面的内容，在释放后，再次读取内存，就会读取到之前释放的内容
    */

   // 解决方法
   /*
   释放内存后，将指针指向NULL
   */

    password = NULL;  
    
    puts("\n");


    // 堆溢出漏洞
    char *str1;
    str1 = malloc(10 * sizeof(char));
    
    char *str2;
    str2 = malloc(10 * sizeof(char));

    printf("str1 = %zu\n",str1);
    printf("str2 = %zu\n",str2);

    unsigned int diff = str2 - str1;

    printf("diff = %d\n",diff);

    strcpy(str2,"Hello");

    printf("str2_before = %s\n",str2);

    memset(str1,'C',(unsigned int)(diff+10)); 

    printf("str2_after = %s\n",str2); // 数据被覆盖，造成堆溢出漏洞

    free(str1); // 同时无法释放 str1 的内存
    free(str2);

    // 解决方法
    /*
    使用 strnpcy() 函数而不是 memset() 函数
    */


    return 0;

}