// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int array[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};

int sum = 0;
int counter = 0;
int linesum = 0;
int linecounter = 0;

for (int i = 0; i < 3; i++)
{
    linesum = 0;
    linecounter = 0;
    for (int j = 0; j < 4; j++)
    {
        sum += array[i][j];
        counter++;
        linesum += array[i][j];
        linecounter++;
    }
    printf("第%d行 linesum=%d lineave=%.2lf\n",i+1,linesum,linesum/(float)linecounter);
}

for (int i = 0; i < 4; i++)
{
    linesum = 0;
    linecounter = 0;
    for (int j = 0; j < 3; j++)
    {
        array[j][i];
        linesum += array[j][i];
        linecounter++;
    }
    printf("第%d列 listsum=%d listave=%.2lf\n",i+1,linesum,linesum/(float)linecounter);
}


printf("sum=%d ave=%.2lf\n",sum,sum/(float)counter);

return 0;
}