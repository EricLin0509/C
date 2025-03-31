#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *longestCommonPrefix(char *pattern, int len)
{
    int *LPS = calloc(len, sizeof(int));
    int prev = 0;
    int i = 1;

    if (len == 1) return LPS;

    while (i < len)
    {
        if (pattern[i] == pattern[prev])
        {
            LPS[i] = prev + 1;
            prev++;
            i++;
        }
        else if (prev == 0)
        {
            LPS[i] = 0;
            i++;
        }
        else
        {
            prev = LPS[prev - 1];
        }
    }
    return LPS;
}

int KMP(char *str, char *pattern)
{
    int str_len = strlen(str);
    int pattern_len = strlen(pattern);
    int i = 0;
    int j = 0;
    int *LPS = longestCommonPrefix(pattern, pattern_len);

    while (i < str_len)
    {
        if (str[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                i++;
            }
            else
            {
                j = LPS[j - 1];
            }
        }

        if (j == pattern_len)
        {
            free(LPS);
            return i - j;
        }
    }
    free(LPS);
    return -1;
}

int main(int argc, const char *argv[]) {
    char str1[] = "abcdefg";
    char pattern1[] = "cde";
    int index = KMP(str1, pattern1);
    printf("%d\n", index);

    char str2[] = "AAAXAAAA";
    char pattern2[] = "AAAA";
    index = KMP(str2, pattern2);
    printf("%d\n", index);

    char str3[] = "abcdefg";
    char pattern3[] = "hij";
    index = KMP(str3, pattern3);
    printf("%d\n", index);
    return 0;
}