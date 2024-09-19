#include<stdio.h>

void function_pointer(char *str)
{

}

int Add(int x,int y)
{
    return x+y;
}

int main(int argc, const char * argv[]) {

int a = 10;
int *pa = &a;

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int (*parr)[10] = &arr; // 取出数组的地址
printf("%d\n\n",(*parr)[5]); // 输出6

// 函数指针 - 存放函数地址的指针
// &函数名 取得的就是函数的地址
// 函数名 == &函数名
printf("%zu\n",Add);
printf("%zu\n\n",&Add); // 两者相同

int (*pf)(int, int) = &Add; // pf 就是一个函数指针变量
/*
int 说明函数返回类型为 int
(*pf) 说明是个指针
(int, int) Add 这个函数对应的传参类型
*/
int (*pf2)(int, int) = Add; // Add == pf

void (*pt)(char *) = &function_pointer;

int result = (*pf)(3, 5); // 此处的 * 没意义
int result2 = pf(3, 5);
// int result3 = *pf(3, 5); // ❌ 此处相当于对返回值进行解引用
printf("result: %d\n",result);
printf("result2: %d\n",result2);

return 0;

}

