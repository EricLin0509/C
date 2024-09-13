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

return 0;
}