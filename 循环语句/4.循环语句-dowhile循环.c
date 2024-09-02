#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

/*
do-while侯的表达式一开始就为假，循环体还是要执行一次
do-while语句表达式后面必须加分号
不要忘记初始化循环变量
*/


int sum = 0;
int i = 0;
do
{
    i++; // 1
    sum += i;

} while (i < 100); //必须加分号

printf("sum=%d\n",sum);

return 0;
}