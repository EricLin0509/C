#include  <stdio.h> 
#include <string.h>
int main(int argc, const char *  argv[] ) {

char str[100];
memset(str, '\0', sizeof(str));

printf("请输入一个字符串\n");
puts(str);

int nLength = (int)strlen(str);
for (int i = nLength; i >= 0; i--)
{
    putchar(str[i]);
}
putchar('\n');


char firstName[10] = "";
char lastName[10] = "";
char name[30] = "";

// 由于 gets() 函数已经过时，所以直接使用 gets() 函数会报错
/*
printf("请输入性：");
gets(firstName);
printf("请输入名：");
gets(lastName);
*/

// 使用 fgets() 函数
// fgets(变量名,最大字符数,指针)

printf("请输入性：");
fgets(firstName,sizeof(firstName),stdin); // stdin 表示从键盘输入获取字符
firstName[strcspn(firstName, "\n")] = '\0'; // 将回车替换成空字符

printf("请输入名：");
fgets(lastName,sizeof(lastName),stdin);
lastName[strcspn(lastName, "\n")] = '\0';

// strcspn() 函数用于检索字符串中的数据
// strcspn(要被检索的字符串,用于进行匹配的字符串)

strcat(name,firstName);
strcat(name,lastName);

puts(name);

return 0;
}