//printf("格式控制字符串",参数列表...);

#include  <stdio.h>  
int main(int argc, const char * argv[] ) {

    int month = 7;
    int day = 20;
    
    printf("今天是%d月%d日%% \n",month,day);

    return 0;
}

    /*
    %d 十进制有符号函数
    %u 十进制五符号函数
    %f  浮点数（单精度）float
    %lf 浮点数（双精度）double
    %.5lf 显示时保留小数点1后5位
    %s 字符串
    %c 单个字符
    %p 指针的值
    %e 指数形式的浮点数
    %x 以十六进制表示的整数
    %0 以八进制表示的整数
    %%输出%
    */