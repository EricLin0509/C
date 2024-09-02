#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

for (int i = 0; i < 50; i++)
{
    if (i%3 != 0)
    {
        continue;  //如果条件不成立，则下面printf语句不执行
    }
    printf("%d\n",i);
}

int times = 0;
int passdata = 123456;

while (1)
{
    if (!times)
    {
        printf("请输入密码\n");
    }
    else
    {
        printf("输再次输入密码\n");
    }
    times++;

    int temp = 0;
    scanf("%d",&temp);

    if  (temp == passdata)
    {
        printf("输入正确\n");
        break;
    }

    else 
    {
    //限定输入次数
        if (times == 3)
        {
            printf("输入达到最大次数，请明天再试\n");
            break;
        }
        printf("输入错误，请重试\n");
    }


    
}


return 0;
}