// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h>  
/*
stdio.h 系统库文件（可以理解为是一种仓库）
#include  导入头文件的预编译指令 
<> (直接搜索系统自带的库)
"" (先搜索用户自定义的库 再搜索系统库)
*/

/*
main() 主函数 作为程序唯一入口 它有且仅有一个（整个工程只能有一个）
*/
int main(int argc, const char * argv[] ) {
    //语句
    //  \n  表示换行    转义字符
    printf("Hello World!\n");
    return 0;
}
