// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

# ifndef NUM2_H // 头文件保护符 (Header Guard)
# define NUM2_H
/*
头文件保护符 (Header Guard) 
用于防止头文件被包含多次
*/

# include "header1.h" // 如果 NUM1_H 已经被定义了。这个头文件将不会导入
int number2() {
    return 10;
}

# endif