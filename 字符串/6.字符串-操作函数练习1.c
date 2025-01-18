// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

char str[20] = ""; // '\0'
scanf("%s",str);

printf("number = %ld\n",strlen(str));

char str1[100] = "";
char str2[100] = "";
scanf("%s",str1);
scanf("%s",str2);

strcpy(str1,str2);
printf("%s\n",str1);

strcat(str2,str1);
printf("%s\n",str2);

char address[100] = "";
char findChar = '\0';

memset(address,'\0',sizeof(address));

scanf("%s",address);
scanf("\n%c",&findChar);

int number = 0;
for (int i = 0; i < strlen(address); i++)
{
    if (findChar == address[i])
    {
        number++;
    }   
}
if (number == 0)
{
    printf("Sorry not found\n");
}
else
{
    printf("%d\n",number);
}


return 0;
}