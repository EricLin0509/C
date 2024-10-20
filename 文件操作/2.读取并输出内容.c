// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdbool.h>

#define FILE_NAME_MAX 1024
#define LINE_MAX 2048

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
    

    // 读取文件中指定的行

    FILE *file;

    char filename[FILE_NAME_MAX];
    char buffer[LINE_MAX];

    int line;

    printf("FIle: ");
    scanf("%s",filename);
    
    printf("Read line: ");

    scanf("%d",&line);

    file = fopen(filename,"r");

    if (file == NULL)
    {
        printf("open file failed\n");
        return 1;
    }

    bool keep_reading = true; // 定义一个布尔变量，用于判断是否继续读取文件
    int current_line = 1; // 定义一个变量，用于记录当前读取的行数

    do
    {
        fgets(buffer, LINE_MAX, file);

        if (feof(file))
        {
            keep_reading = false;
            printf("File %d lines.\n",current_line-1);
            printf("Could not find line %d.\n",line);
        }
        else if (current_line == line)
        {
            keep_reading = false;
            printf("Line:\n%s",buffer);
        }
        current_line++;

    } while (keep_reading);
    
    fclose(file);  
    
    return 0;

}