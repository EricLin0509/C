// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {

// 字符串拼接函数strcat()
/*
strcat(字符数组1,字符数组2)
把字符数组2中的字符连接到字符数组1中的字符后面
并且删去字符数组1末尾的结束标志'\0'
*/

char str1[20] = "hello"; // 要注意长度问题
char str2[] = "world";

strcat(str1,str2);
printf("str1= %s\n",str1); // 输出结果为 'helloworld'

/*
1. 内存足够大的字符数组
2. 标准的字符串

strcat("123", str2) ❌
*/


// strncat()
char str3[20] = "hello";
char str4[] = "world";

strncat(str3,str4,2);
printf("str3= %s\n",str3); // 输出结果为 'hellowo'

char str5[20] = "hello";
char str6[] = "world";

strncat(str5,str6+1,2);
printf("str3= %s\n",str5); // 输出结果为 'helloor'


// 练习
char s1[20] ="123";
char s2[] ="456";
/* 方法1
strcat(s2,s1);
printf("%s",s1);
*/
/* 方法2
strncpy(s1+strlen(s1),s2,strlen(s2));
printf("%s",s1);
*/
// 方法3
int nLength = (int)strlen(s1); // long 转 int
for (int i = 0; i <= strlen(s2); i++)
{
    s1[i+nLength] = s2[i];
}
printf("%s",s1);

return 0;
}