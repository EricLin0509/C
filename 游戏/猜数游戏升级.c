#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, const char * argv[]) {
printf("请输入一个0~100之间的数，你有10次机会\n");
int answer;


srand((unsigned)time(NULL));
int question = rand()%100; // 生成随机数

int counter = 0; // 记录尝试次数

while (1) // 用于死循环
{
    counter++;
    scanf("%d",&answer);
    if (answer == question)
    {
        printf("回答正确！\n");
        printf("一共尝试了%d次\n",counter);
        break;
    }

    else if (answer < question)
    {
        printf("小了，剩余%d次机会\n",10-counter);
    }
    else if (answer > question)
    {
        printf("大了，剩余%d次机会\n",10-counter);
    }

    if (counter == 10)
    {
        printf("挑战失败\n");
        break;
    }
    

}
  
    return 0;
}