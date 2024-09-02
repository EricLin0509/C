#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/*
逗号运算符,     优先级最低
特殊运算符()    优先级最高
*/
    int a = 3;
    printf("a=%d\n",(a=3*5,a*4));

/*
sizeof()     以字节形式给出其操作数的存储大小
数据类型
常量
变量
sizeof不能用于函数、不完全类型和位字段
*/

    
    int myNum =5.78;
    int num1 = sizeof(double);
    int num2 = sizeof(4.78);
    int num3 = sizeof(myNum);

    printf("num1=%d\n",num1);
    printf("num2=%d\n",num2);
    printf("num3=%d\n",num3);
    return 0;
}