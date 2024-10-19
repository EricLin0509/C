// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

int main (int argc, const char * argv[]) {

    FILE *fh;

    fh = fopen("file.txt","r");

    if (fh != NULL) // 判断文件是否打开成功，如果文件不存在，返回 NULL
    {
        char c;
        while ((c = fgetc(fh))!= EOF) // fgetc 读取一个字符，直到文件结束
        {
            putchar(c);
        }
        
    }
    else
    {
        printf("open file failed\n");
        return 1;
    }

    fclose(fh);    
    
    return 0;

}