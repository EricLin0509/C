// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

int main (int argc, const char * argv[]) {

    FILE *data;
    int c;
    data = fopen("file.txt","r");

    if (data == NULL)
    {
        printf("open file failed\n");
        return 1;
    }

    while (1)
    {
        c = fgetc(data);
        printf("%c",c);

        if (feof(data)) // 判断文件是否结束，如果文件结束，返回 true
        {
            break;
        }
    }

    rewind(data); // 将文件指针重置到文件开头，同时清除文件结束标志，以便再次读取文件

        while (1)
    {
        c = fgetc(data);
        printf("%c",c);

        if (feof(data))
        {
            break;
        }
    }
    
    fclose(data);
    
    return 0;

}