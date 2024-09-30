// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 

void func ()
{
    int nstic = 0; // 非静态局部变量
    static int stic = 0; // 静态局部变量
    nstic++;
    stic++;
    printf("non-static: %d \n",nstic);
    printf("static: %d \n",stic);
}

// 静态全局变量
static int gstic = 0;
// 静态全局变量的作用域仅限于当前文件，其他文件无法访问。


/*
当函数调用结束时，局部变量的内存空间会被释放，其中存储的内容也会被销毁。
静态变量的值在函数调用结束后不会被销毁，而是会保留在内存中，直到程序结束。
*/

// 外部变量
extern int entrn; // 外部变量，在其他文件中定义。
// 可以在多个文件中共享和使用，但是只能在定义的文件中进行修改

int main(int argc, const char * argv[] ) {

func();
func();
func();
/*
non-static: 1
static: 1
non-static: 1
static: 2
non-static: 1
static: 3
*/

return 0;
}