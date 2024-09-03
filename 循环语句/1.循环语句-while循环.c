// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int i = 1;
int num = 0;

while (i <= 100)
{
    num = num + i;
    i++;
}

printf("num=%d\n",num);

return 0;
}