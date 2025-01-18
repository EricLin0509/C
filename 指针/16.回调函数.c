// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
#include<stdbool.h>

/*
把一段可执行的代码像参数传递那样传给其他代码，而这段代码会在某个时刻被调用执行，这就叫做回调
*/

bool Celsius(int temperature)
{
    if (temperature <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }   
}

bool Fahtenheit(int temperature)
{
    if (temperature <= 32)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void freezing(bool (*check)(int))
{
    int temperature = 0;
    printf("输入温度：");
    scanf("%d",&temperature);
    if (check(temperature))
    {
        printf("会结冰\n");
    }
    else
    {
        printf("不会结冰\n");
    }
    
}

int main(int argc, const char * argv[]) {

int option = 0;
printf("选择单位\n");
printf("1. 摄氏度 ℃\n");
printf("2. 华氏度 ℉\n");
printf("请选择：");
scanf("%d",&option);

switch (option)
{
case 1:
    freezing(Celsius);
    // freezing 函数调用 Celsius 函数
    break;

case 2:
    freezing(Fahtenheit);
    // freezing 函数调用 Fahtenheit 函数
    break;

default:
    printf("输入错误，请重试\n");
    break;
}

return 0;

}

