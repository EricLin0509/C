// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dynamic_string(char *string, int n)
{
    string[n] = '\0';
    return realloc(string , (n + 1) * sizeof(char));
}

int main (int argc, const char * argv[]) {

char array[25] = "It works on my machine";

printf("before array: %s\n", array);

array[8] = '\0'; // 将第 9 个字符设置为字符串结束符，截断字符串
// 由于此字符串存放在栈区，所以无法缩小其大小，只能截断它

printf("after array: %s\n", array);

char *string = malloc(25 * sizeof(char));

strcpy(string, "It works again");

printf("before string: %s\n", string);

string[8] = '\0';
string = realloc(string, (8 + 1) * sizeof(char)); // 重新分配内存，将字符串截断为 8 个字符
// 由于此字符串存放在堆区，所以可以动态调整其大小

string = dynamic_string(string, 7);

printf("after string: %s\n", string);

free(string);

return 0;

}