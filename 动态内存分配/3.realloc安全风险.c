#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 注意：此方法可能会失效，因为可能会被其他程序覆盖或者被操作系统的内存管理机制覆盖

int main(int argc, const char * argv[]) {

char *password1;
char *password2;
char *sniffer;

password1 = malloc(7 * sizeof(char));
password2 = malloc(7 * sizeof(char));
strcpy(password1, "123456");
strcpy(password2, "xyz789");

printf("password1_addr: %zu\n", password1);
printf("password2_addr: %zu\n", password2);

for (int i = 0; i < 100; i++)
{
    printf("%c",password1[i]); // 可以读取到 password2 的数据
}
printf("\n\n");


sniffer = password1; // 将 password1 原来的地址赋值给 sniffer
printf("sniffer_addr: %zu\n\n", sniffer);

password1 = realloc(password1, 100 * sizeof(char));
printf("password1: %s\n\n", password1);

printf("password1_addr: %zu\n", password1); // password1 的地址发生改变
printf("password2_addr: %zu\n", password2);

for (int i = 0; i < 100; i++)
{
    printf("%c", sniffer[i]); // 可以读取到原来 password1 的数据，导致密码泄露
}
printf("\n\n");

free(password1);
free(password2);

return 0;
}