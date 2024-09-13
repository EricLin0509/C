#include<stdio.h>
#include<string.h>

void rec(char *arr) {

int len =strlen(arr);

char *p1 = arr; //字符串的首地址
char *p2 = &arr[len - 1]; // 字符串最后一个有效字符的地址

while (p1 < p2)
{
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    p1++;
    p2--;
}


}

int main(int argc, const char * argv[]) {

char arr[] = "Hello world";
rec(arr);
printf("%s\n",arr);

return 0;

}