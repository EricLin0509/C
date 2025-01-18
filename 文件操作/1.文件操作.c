// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, const char * argv[]) {

    FILE *fh_output; // 文件句柄，是一个指针

    fh_output = fopen("output.txt","w"); // 打开文件，返回文件句柄
    // 如果文件不存在，会创建文件
    // w 表示写入，r 表示读取，a 表示追加

    // fputs("abc\n",fh_output);

    // fputs("123\n",fh_output);

    // fputs("A string\n",fh_output); // 写入字符串

    // fprintf(fh_output,"data: %d\n",100); // 写入数据，可以使用格式化字符串

    int input = 0;

    while(true)
    {
        printf("input numbers (-1 to quits): ");
        scanf("%d",&input);

        if(input == -1)
        {
            break;
        }
        else
        {
            fprintf(fh_output,"%d\n",input);
        } 
    }

    fclose(fh_output); // 关闭文件并保存

    int finput = 0;
    int lines = 0;
    int numbers[100];

    FILE *fh_input;
    fh_input = fopen("output.txt","r"); // 以只读方式打开文件
    while(fscanf(fh_input, "%d", &finput) != EOF)
    {
        numbers[lines] = finput;
        printf("file line %d = %d\n", lines+1, numbers[lines]);
        lines++;
    }

    fclose(fh_input);

    fh_input = fopen("in.txt","r"); // 以只读方式打开文件
   
    char buffer[256];
    fgets(buffer, 256, fh_input); // 以字符串的形式读取数据

    printf("buffer = %s\n",buffer);

    fclose(fh_input);

    return 0;

}