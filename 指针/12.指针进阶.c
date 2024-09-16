#include<stdio.h>

int main(int argc, const char * argv[]) {

// 本质上是把 "hello world" 这个字符串的首字符的地址存储在 ps 中
char *ps = "hello world";
char arr[] = "hello world";

printf("%c\n",*ps);
printf("%s\n",ps);
printf("%s\n",arr);

char str1[] = "hello bit"; // 创建了一个字符串
char str2[] = "hello bit"; // 创建了一个字符串
char *str3 = "hello bit";
char *str4 = "hello bit";
// str3 和 str4 都指向同一个内存空间

if (str1 == str2)
{
    printf("same\n");
}
else
{
    printf("not same\n");
}
// 输出 "not same"

if (str3 == str4)
{
    printf("same\n");
}
else
{
    printf("not same\n");
}
// 输出 "same"
return 0;
}