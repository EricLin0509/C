#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/*
for (int i = 0; i < 5; 3)
{
    printf("Good morning\n");
}
*/

/*
int i = 0;
while (i < 5)
{
    i--;
    printf("good morning\n");
}
*/

int i = 1;

int pass = 0;
while (1)
{
    printf("请输入密码\n");
    scanf("%d",&pass);

    if (pass ==123456)
    {
        printf("输入正确\n");
        break;
    }
    else if (i == 3)
    {
        printf("输入达到最大次数，请明天再试\n");
        break;
    }
    
    else 
    {
        printf("输入错误，请重试\n");
        i++;
    }
    
    
}


return 0;
}