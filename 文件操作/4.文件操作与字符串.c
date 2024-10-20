// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>

char *read_file(char *filename)
{
    FILE *file;

    file = fopen(filename , "r");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END); // 获取文件大小，SEEK_END 表示文件末尾
    int length = ftell(file); // 获取文件大小
    fseek(file, 0, SEEK_SET); // 重置文件指针到文件开头

    char *string = malloc(length + 1); // 分配内存空间，多分配一个字节用于存储字符串结束符 '\0'

    char c;
    int i = 0;
    while ((c = fgetc(file))!= EOF) // 读取文件内容
    // fgetc 读取一个字符，EOF 表示文件结束符
    {
        string[i] = c;
        i++;
    }
    string[length] = '\0'; // 字符串结束符

    fclose(file); // 关闭文件

    return string;
}

int main (int argc, const char * argv[]) {

    char filename[1024];
    printf("File: ");
    scanf("%s", filename);

    char *file_contents = read_file(filename);

    if (file_contents == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    printf("File contents: \n\n%s", file_contents);

    free(file_contents);

    return 0;

}