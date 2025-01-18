// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

/*
1   123     90（整形常量）
3.14    6.789（小数）
1.23E+4 1.23-5
*/
//  1
// 'a' ; (字符，只占一个字节，只能放一个字符)
//"a"(a+\0   共占两个字节)

    printf("\"Hello World!\" \n");
    return 0;
}

 /*
\a 响铃
\b 退格
\f 换页
\n 换行
\r 回车
\t 水平制表
\v 垂直制表
\\ 反斜杠
\? 问号字符
\' 单引号
\" 双引号
\0 空字符(NULL)
*/