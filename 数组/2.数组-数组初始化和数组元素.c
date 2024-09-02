#include  <stdio.h> 
#define LENGTH 5 // 预编译指令
int main(int argc, const char * argv[] ) {

// 初始化数组
int array1[10] = {0,0,0,0,0,0,0,0,0,0}; // 推荐
float array2[5] = {1.0,2.0};

// 不能空掉一个或多个元素赋值
// char array3[20] = {'a', ,'b','5'};

// 使用循环方式赋值
double array4[10];
for (int i = 0; i < 10; i++)
{
    array4[i] = 0;
}

// 访问数组元素
array1[0] = 1;
array1[1] = 2;
array1[2] = 4;

int temp = array1[3];

// 特殊的数组
char str[20] = "hello"; // [h] [e] [l] [l] [o] [\n]

// 初始化的形式
int array6[10]; // 花括号只能在初始化时使用

// 错误写法
// int array6[10] = {1,2,3,4,5}; 
//str[20] = "world";
//printf("%s\n",str);

int a[6] = {2,4,6,8,10,12};

for (int i = 0; i < 6; i++)
{
    a[i] = (i+1)*2;
}

for (int i = 0; i < 6; i++)
{
    printf("a[%d] = %d\n",i,a[i]);
}


return 0;
}