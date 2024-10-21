// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MORE_LINES 128
#define MORE_CHARS 128

int main (int argc, const char * argv[]) {

    FILE *file = fopen("bigdata.txt", "r");

    if (file == NULL)
    {
        printf("open file failed\n");
        return 1;
    }

    char **lines; // 定义一个指针数组，用于存储文件中的每一行
    lines = malloc(MORE_LINES * sizeof(char *)); // 为 lines 分配内存空间

    size_t total_lines = 0;
    size_t total_chars = 0;
    char c;

    do
    {
        c = fgetc(file);

        if (ferror(file)) // ferror() 用于判断文件是否出错
        {
            printf("Error reading from file.\n");
            return 1;
        }
        
        if (feof(file))
        {
            if (total_chars != 0) // 如果 total_chars 不为 0，则说明最后一行没有结束符，需要手动添加结束符
            {
                lines[total_lines] = realloc(lines[total_lines], total_chars + 1); // 为 lines[total_lines] 重新分配内存空间
                lines[total_lines][total_chars] = '\0';
                total_lines++; // 读取新的一行
            }

            break;
        }

        if (total_chars == 0)
        {
            lines[total_lines] = malloc(MORE_CHARS * sizeof(char)); // 为 lines[total_lines] 分配内存空间
        }
        lines[total_lines][total_chars] = c;

        total_chars++;

        if (c == '\n')
        {
            lines[total_lines] = realloc(lines[total_lines], total_chars + 1); // 为 lines[total_lines] 重新分配内存空间
            lines[total_lines][total_chars] = '\0';

            total_lines++; // 读取新的一行
            total_chars = 0; // 重置 total_chars，准备读取下一行

            if (total_lines % MORE_LINES == 0)
            {
                size_t new_size = (total_lines + MORE_LINES);
                lines = realloc(lines, new_size * sizeof(char *)); // 为 lines 重新分配内存空间
            }
        }
        else if (total_chars % MORE_CHARS == 0)
        {
            size_t new_size = (total_chars + MORE_CHARS);
            lines[total_lines] = realloc(lines[total_lines], new_size); // 为 lines[total_lines] 重新分配内存空间
        }
        
        
    } while (true);
    
    lines = realloc(lines, total_lines * sizeof(char *)); // 为 lines 重新分配内存空间，以适应实际的行数

    for (size_t i = 0; i < total_lines; i++)
    {
        printf("%s", lines[i]);
    }

    for (size_t i = 0; i < total_lines; i++)
    {
        free(lines[i]);
    }

    free(lines);

    fclose(file);

    return 0;
}