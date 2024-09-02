#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/* a++ <==> a = a + 1
 --a <==> a = a + 1
++a <==> a = a + 1

++a 先自加 再参与运算
a++ 先参与运算 后自加

--a 先自减 再参与运算
a-- 先参与运算 后自减

b = 7;
c = 1+ b++;
c = 8
b = 8

c = 3 + ++b;
c = 11
b = 8
自增自减运算符不能作用于常量或运算表达式
*/

int a = 7;
int b = 1 + a++;
printf("a=%d\nb=%d\n",a,b);

int c = 7;
int d = 3 + ++c;
printf("c=%d\nd=%d\n",c,d);

int i = 5;
int j;
j = i++;
printf("i=%d, j=%d\n",i,j);  // i=6, j=5
printf("i=%d, j=%d\n",i++,j++);  // i=6, j=5
printf("i=%d, j=%d\n",i,j);  // i=7, j=6

return 0;
}