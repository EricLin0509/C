// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <unistd.h>
int main(int argc, const char * argv[] ) {

int hour = 23;
int min = 59;
int sec = 59;
while (1)
{
if ((hour <= 23 && hour >= 0) || (min <= 59 && min >= 0) || (sec <=  59 && sec >= 0))
{
        if (sec == 59)
        {
            min += 1;
            sec = 0;
            if (min == 60)
            {
              hour += 1;
              min = 0;
              if (hour == 24)
              {
                hour = 0;
              }
            }
        }
    else
    {
        sec += 1;
    }
    
}
printf("%.2d:%.2d:%.2d\n",hour,min,sec);
sleep(1);
}
return 0;
}