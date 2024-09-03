// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h>  
int main(int argc, const char * argv[] ) {
/*
argc (argument count): 表示命令行参数的数量，包括程序名本身
argc 的值至少为 1

argv (argument vector): 是一个指向字符串的指针，其中每个字符串是一个命令行参数
数组的第一个元素 argv[0] 通常是程序的名称，接下来的元素是传递给程序的命令行参数
*/

if (argc == 2)
{
    printf("There is one additional argument and the argument is %s\n",argv[1]);
}
else if (argc > 2)
{
    printf("There are more than one additional argument\n");
}
else
{
    printf("There is no additional argument\n");
}

/* 编译完成后在命令行输入以下命令会输出不同结果
输入：./a.out argument1
输出：There is one additional argument and the argument is argument1

输入：./a.out argument1 argument2
输出：There are more than one additional argument

输入：./a.out
输出：There is no additional argument
*/

return 0;
}