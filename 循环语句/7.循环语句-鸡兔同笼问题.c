// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int number = 0;
scanf("%d",&number);
for (int i = 0; i <= 100; i++)
{
    if (i%number != 0)
    {
        continue;
    }
    printf("%d\n",number);
}


int chicken = 0;
int rabbit = 0;

for (chicken = 0; chicken < 88; chicken++)
{
   rabbit = 88 - chicken;
   if (rabbit*4 + chicken*2 == 244)
   {
        printf("rabbit=%d chicken=%d\n",rabbit,chicken);
        break;
   }
   
}


return 0;
}