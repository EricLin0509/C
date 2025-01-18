// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int row;
    int col;
    char *text;
}Point;


int main(int argc, const char * argv[]) {

Point p1;

p1.row = 4;
p1.col = 5;

printf("%d %d\n", p1.row, p1.col);

Point *p2;

p2 = malloc(sizeof(Point)); // 使用 malloc 分配一个结构体空间

(*p2).col = 5; // 先解引用，再访问结构体成员
p2 -> row = 2; // 使用箭头运算符访问结构体成员

printf("%d %d\n", (*p2).row, (*p2).col);

free(p2);

int length =3;
Point *array;

array = malloc(sizeof(Point) * length); // 使用 malloc 分配三个结构体数组空间

array[0].col = 1;
array[0].row = 1;
array[0].text = malloc(sizeof(char) * 10);

strcpy(array[0].text, "point 1");

array[1].col = 2;
array[1].row = 2;
array[1].text = malloc(sizeof(char) * 10);

strcpy(array[1].text, "point 2");

array[2].col = 3;
(*(array + 2)).col =3; // 等价于 array[2].col = 3;
array[2].row = 3;
array[2].text = malloc(sizeof(char) * 10);

strcpy(array[2].text, "point 3");

for (int i = 0; i < length; i++)
{
    printf("(%d, %d)\n", array[i].row, array[i].col);
    printf("%s\n", array[i].text);
}

puts("\n");

length = 4;

array = realloc(array, sizeof(Point) * length); // 使用 realloc 重新分配四个结构体数组空间

array[3].col = 4;
array[3].row = 4;
array[3].text = malloc(sizeof(char) * 10);

strcpy(array[3].text, "point 4");

for (int i = 0; i < length; i++)
{
    printf("(%d, %d)\n", array[i].row, array[i].col);
    printf("%s\n", array[i].text);
}

for (int i = 0; i < length; i++)
{
    free(array[i].text); //先释放 text 结构体成员的内存
}

free(array); // 再释放结构体数组的内存

return 0;

}