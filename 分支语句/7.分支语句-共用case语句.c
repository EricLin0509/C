#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

int score = 0;
printf("请输入一个分数\n");
scanf("%d",&score);

if (score<=100 && score>0)
{
    switch (score/10)
    {
    case 10:
    case 9:
        printf("A\n");
        break;

    case 8:
        printf("B\n");
        break;
    case 7:
        printf("C\n");
        break;
    case 6:
        printf("D\n");
        break;
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
    case 0:
        printf("E\n");
        break;
    }
}
else
{
    printf("输入不合法，请重试\n");
}
return 0;
}
