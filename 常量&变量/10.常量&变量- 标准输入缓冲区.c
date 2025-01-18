// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 

int main(int argc, const char * argv[] ) {

    // 标准输入缓冲区是一个字符数组， 当输入一个字符时， 会将该字符存储到标准输入缓冲区中

    int num = 0;
    char ch = 0;

    printf("请输入第一个整数：");
    scanf("%d",&num);

    printf("请输入第一个字符：");
    scanf("%c",&ch);

    printf("num = %d\n",num);
    printf("char = %c\n",ch);

    /*
    当用户输入 (stdin) 一个整数并按下回车键时，会发现程序没有要求用户输入第二个字符， 而是直接输出了第二个字符
    因为，当用户输入一个整数并按下回车键时， 整数会被存储到标准输入缓冲区中，而回车键也会被存储到标准输入缓冲区中
    因此， 当程序执行到第二个scanf函数时，会从标准输入缓冲区中读取一个字符
    第二个scanf函数读取到的是一个换行符 ('\n')
    */


    // 解决方法

    // 方法一： 使用 getchar() 函数接住换行符
    printf("请输入第二个整数：");
    scanf("%d",&num);

    getchar();

    printf("请输入第二个字符：");
    scanf("%c",&ch);
    
    printf("num = %d\n",num);
    printf("char = %c\n",ch);
    // 缺点：当用户输入的字符是空格时，第二个scanf函数会读取到空格


    // 方法二： 使用 fflush() 函数清空标准输入缓冲区
    printf("请输入第三个整数：");
    scanf("%d",&num);

    fflush(stdin); // 清空标准输入缓冲区

    printf("请输入第三个字符：");
    scanf("%c",&ch);
    
    printf("num = %d\n",num);
    printf("char = %c\n",ch);
    // 缺点： 该函数只适用于Windows系统


    // 方法三： 使用 getchar() 函数循环读取标准输入缓冲区中的字符
    printf("请输入第四个整数：");
    scanf("%d",&num);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // 在读取到换行符之前，循环接收标准输入缓冲区中的字符
    // 'c != EOF' 表示读取到了文件结尾或者读取错误时退出， 防止死循环

    printf("请输入第四个字符：");
    scanf("%c",&ch);

    printf("num = %d\n",num);
    printf("char = %c\n",ch);

    return 0;
}