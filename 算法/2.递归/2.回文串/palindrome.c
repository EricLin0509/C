#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char *left, char *right)
{
    if (left >= right) return true; // 基准条件

    if (*left == *right)
    {
        return isPalindrome(left + 1, right - 1);
    }

    return false; // 额外的基准条件，用于不是回文串的情况
}

int main(int argc, const char *argv[]) {
    char str[] = "abba";
    char *left = str;
    char *right = str + strlen(str) - 1;
    printf("%s\n", isPalindrome(left, right) ? "Palindrome" : "Not Palindrome"); // Palindrome

    char str2[] = "hello";
    char *left2 = str2;
    char *right2 = str2 + strlen(str2) - 1;
    printf("%s\n", isPalindrome(left2, right2) ? "Palindrome" : "Not Palindrome"); // Not Palindrome
}