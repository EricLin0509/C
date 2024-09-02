#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

/*
int number = 0;
scanf("%d",&number);

int n = 0;
int i = 1;
while (i<number)
{
    i++;
    if (number%i == 0)
    {
        n++;
        break;
    }
}
if (n > 0)
{
    printf("不是质数\n");
}
else
{
    printf("是质数\n");
}
*/

/*
char temp = '0';
scanf ("%c",&temp);
if ((temp>='a'&&temp<='z') || (temp>='A'&&temp<='Z'))
{
    printf("是英文字符\n");
}
else
{
    printf("不是英文字符\n");
}
*/

char first = '0';
char second ='0';

scanf("%c",&first);

switch (first)
{
case 'M':
case 'm':
    printf("Monday\n");
    break;
case 'T':
case 't':
printf("请输入第二个字符\n");
scanf("\n%c",&second);
if (second == 'u' || second == 'U')
{
    printf("Tuesday\n"); 
    break;  
}
else if (second == 'h' || second == 'H')
{
    printf("Thursday\n");
    break;   
}
else
{
    printf("输入错误，请重试\n");
    break;
}
case 'W':
case 'w':
    printf("Wednesday\n");
    break;
case 'F':
case 'f':
    printf("Friday\n");
    break;
case 'S':
case 's':
printf("请输入第二个字符\n");
scanf("\n%c",&second);
if (second == 'a' || second == 'A')
{
    printf("Saturday\n");   
}
else if (second == 'u' || second == 'U')
{
    printf("Sunday\n"); 
    break;  
}
else
{
    printf("输入错误，请重试\n");
    break;
}
default:
    printf("输入错误，请重试\n");
    break;
}


return 0;
}
