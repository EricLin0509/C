// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

    char chTemp = 0;

    chTemp = getchar();
    printf("%c \n",chTemp);
    printf("program stop!");

    /*
    注意：getchar() 函数只能接收一个字符
    且 getchar() 函数的返回值是 int 类型
    原因是 stdin 是一个文件指针， 当读取到文件末尾时，会返回 EOF
    char 类型在C语言中是特殊的整形， 当 char 类型的变量接收 EOF 时，会发生截断
    */

    return 0;
}