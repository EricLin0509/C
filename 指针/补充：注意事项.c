// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

int main() {

// char s[] = "abcd"; 和 char *s = "abcd"; 的区别
char s1[] = "abcdef"; // 此字符串存放在堆区，可以修改
s1[0] = 'X';
printf("s1: %s\n",s1); // s1 在此处的作用是常量指针

char *s2 = "abcdef"; // 此字符串存放的位置是只读的，不可修改
// 然后 s2 这个指针变量指向此字符串
// s2[0] = 'X'; // 会发生错误 segmentation fault
s2++;
printf("s2: %s\n",s2);

s2 = "new string"; // s2 这个指针变量指向一个新的字符串
// 同样此字符串存放的位置是只读的，不可修改
printf("s2: %s\n",s2);

printf("sizeof(s1): %d\n",sizeof(s1)); // 字符串的大小
printf("sizeof(s2): %d\n",sizeof(s2)); // 一个 'char *' 类型的大小


// 指针声明
int* p1,p2,p3; // 这里只有p1是指针变量，p2 和 p3 都是整形变量
printf("sizeof(int): %d\n",sizeof(int));
printf("sizeof(int*): %d\n",sizeof(int*));

printf("sizeof(p1): %d\n",sizeof(p1));
printf("sizeof(p2): %d\n",sizeof(p2));

int *p4,*p5,*p6; // 推荐写法


// array[] 和  &array[] 的区别
int array[5];

array[2] = 5;
printf("array: %zu\n",array); // array 指向的是数组的第一个元素的内存
printf("array+1: %zu\n",array+1); // 增加4个字节 (增加1个 int 类型)

printf("&array: %zu\n",&array); // &array 指向的是整一个数组
printf("&array+1: %zu\n\n",&array+1); // 增加20个字节 (增加5个 int 类型)(这个数组大小)

// 二维数组
int matrix[3][5] = {{0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14}};

printf("matrix[1]: %zu\n",matrix[1]); // matrix[1] 指向第二个子数组里的第一个元素的内存
printf("matrix[1]+1: %zu\n\n",matrix[1]+1); // 增加4个字节 (增加1个 int 类型)
printf("*(matrix[1]+1): %zu\n\n",*(matrix[1]+1)); // 输出6

printf("&matrix[1]: %zu\n",&matrix[1]); // &matrix[1] 指向整个第二个子数组
printf("&matrix[1]+1: %zu\n",&matrix[1]+1); // 增加20个字节 (增加5个 int 类型)(里面子数组大小)
printf("*(&matrix[1]+1): %zu\n\n",*(&matrix[1]+1)); // *(&matrix[1]+1) 指向第三个子数组里的第一个元素的内存

int *pointer = (int *)(&matrix[1] +1);

printf("pointer: %zu\n",pointer);
printf("*pointer: %zu\n",*pointer); // 输出10
printf("*(*(&matrix[1]+1)): %zu\n\n",*(*(&matrix[1]+1)));

return 0;
}