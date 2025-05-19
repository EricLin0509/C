#include <stdio.h>
#include <string.h>

void reverseString(char *left, char *right)
{
    if (left >= right) return;
    // 交换
    char tmp = *left;
    *left = *right;
    *right = tmp;
    // 向目标前进，递归调用
    reverseString(left + 1, right - 1);
}

int main(int argc, const char * argv[]) {
    char str[] = "I love Rust";
    int sSize = strlen(str);
    reverseString(str, str + sSize - 1);
    printf("%s\n", str);
    return 0;
}