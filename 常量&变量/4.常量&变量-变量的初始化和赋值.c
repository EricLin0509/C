// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
       int nSum; // 定义一个整型的变量nSum
       short nNumber; //  定义一个short类型的的变量nNumber
       char chTemp; // 定义一个char类型的的变量chTemp
       float fAera; // 定义一个float类型的的变量fAera
       
        // 变量的初始化
        /*
        给定有意义的初始值
        清理内存中的垃圾值
        */
         int nNum = 0;
         float fNum = 5.78; 

        //变量的赋值
        nNum = 70;
        fNum = 5.67;

    int month = 7;
    int day = 20;

    printf("今天是%d月%d日   %%\n",month,day);
    double money = 78904.12345678;
    printf("money = %.5lf\n",money);

   /*
    %c 输出字符
    %d 输出整数
    %f 输出小数
    */

    char temp = 'a';
    printf("temp = %c\n",temp);

    float fTemp = 5.6789;
    printf("fTemp = %f\n",fTemp);



        printf("Hello World!  %f\n",fNum);
    return 0;
}