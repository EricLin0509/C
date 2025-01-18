// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

int mouth = 6;
int day = 6;
scanf ("%d",&mouth);
scanf ("%d",&day);

//判断日期是否正确
if (mouth < 1 || mouth >12)
{
    printf("ERROR!\n");
    return 1;
}
if (day < 1 || day > 31)
{
    printf("ERROR!\n");
    return 1;
}
if ((mouth == 4 && day > 30) || (mouth == 6 && day > 30) || (mouth == 9 && day > 30) || (mouth == 11 && day > 30))
{
    printf("ERROR!\n");
}
if (mouth == 2 && day > 29)
{
    printf("ERROR!\n");
    return 1;
}

//判断星座
if ((mouth == 3 && day >= 21) || (mouth == 5 && day < 21))
{
    printf("金牛\n");
}
if ((mouth == 8 && day >= 23) || (mouth == 9 && day < 22))
{
    printf("处女\n");
}
return 0;
}