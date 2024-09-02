#include<stdio.h>
int main(int argc, const char * argv[]) {
    
    printf("请输入一个个位数\n");
    char answer = 0;
    scanf("%d",&answer);
    if (answer == 5)
    {
        printf("回答正确\n");
    }
    else
    {
        printf("回答错误\n");
    }
    return 0;
}