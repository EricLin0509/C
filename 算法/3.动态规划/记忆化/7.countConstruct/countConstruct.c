#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool iscounted[1024]; // 记录已经计算过的分支
int memo[1024]; // 记录已经计算过的分支的结果

int countConstruct(char *s, char **words, int wordsSize)
{
    if (iscounted[strlen(s)]) return memo[strlen(s)]; // 如果已经计算过，直接返回结果
    if (s[0] == '\0') return 1; // 空字符串可以拼接成空字符串
    
    int total = 0; // 记录能够拼接成字符串的个数

    for (int i = 0; i < wordsSize; i++)
    {
        if (strncmp(s, words[i], strlen(words[i])) == 0)
        {
            // 去掉前缀
            char *suffix = s + strlen(words[i]);
            int count = countConstruct(suffix, words, wordsSize); // 递归
            total += count; // 累加
        }
    }
    iscounted[strlen(s)] = true; // 标记已经计算过
    memo[strlen(s)] = total; // 记录结果
    return total;
}

int main(int argc, const char * argv[]) {
    char *s = "purple";
    char *words1[] = {"purp", "p", "ur", "le", "purpl"};
    int wordsSize = sizeof(words1) / sizeof(words1[0]);
    int result = countConstruct(s, words1, wordsSize);
    printf("%d\n", result); // 输出2
    memset(iscounted, false, sizeof(iscounted)); // 重置标记
    memset(memo, 0, sizeof(memo)); // 重置记录
    
    s = "skateboard";
    char *words2[] = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    wordsSize = sizeof(words2) / sizeof(words2[0]);
    result = countConstruct(s, words2, wordsSize);
    printf("%d\n", result); // 输出0
    memset(iscounted, false, sizeof(iscounted)); // 重置标记
    memset(memo, 0, sizeof(memo)); // 重置记录

    s = "eeeeeeeeeeeeeeeeeeeeeeeeeeef";
    char *words3[] = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    wordsSize = sizeof(words3) / sizeof(words3[0]);
    result = countConstruct(s, words3, wordsSize);
    printf("%d\n", result); // 输出0
    memset(iscounted, false, sizeof(iscounted)); // 重置标记
    memset(memo, 0, sizeof(memo)); // 重置记录
    return 0;
}