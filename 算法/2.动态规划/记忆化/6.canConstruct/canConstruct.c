#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool iscounted[1024]; // 记录已经计算过的分支
bool memo[1024]; // 记录已经计算过的分支

bool canConstruct(char *s, char **words, int wordsSize)
{
    if (s[0] == '\0') return true; // s 为空，返回 true
    if (iscounted[strlen(s)]) return memo[strlen(s)]; // 如果已经计算过，返回结果

    for (int i = 0; i < wordsSize; i++) // 遍历 words，查找匹配的单词
    {
        if (strncmp(s, words[i], strlen(words[i])) == 0) // 找到匹配的单词
        {
            char *suffix = s + strlen(words[i]); // 移除已经匹配的单词
            if (canConstruct(suffix, words, wordsSize))
            {
                iscounted[strlen(s)] = true; // 记录已经计算过的分支
                memo[strlen(s)] = true; // 记录结果
                return true; // 递归
            }
        }
    }
    iscounted[strlen(s)] = true; // 记录已经计算过的分支
    memo[strlen(s)] = false; // 记录结果
    return false; // s 不为空且没有匹配的单词，返回 false
}

int main(int argc, const char * argv[]) {
    char *s = "abcdef";
    char *words1[] = {"ab", "abc", "cd", "def", "abcd"};
    int wordsSize = sizeof(words1) / sizeof(words1[0]);
    bool result = canConstruct(s, words1, wordsSize);
    printf("%d\n", result); // 输出1
    memset(iscounted, false, sizeof(iscounted));
    memset(memo, false, sizeof(memo));

    s = "skateboard";
    char *words2[] = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    wordsSize = sizeof(words2) / sizeof(words2[0]);
    result = canConstruct(s, words2, wordsSize);
    printf("%d\n", result); // 输出0
    memset(iscounted, false, sizeof(iscounted));
    memset(memo, false, sizeof(memo));

    s = "eeeeeeeeeeeeeeeeeeeeeeeeeeef";
    char *words3[] = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    wordsSize = sizeof(words3) / sizeof(words3[0]);
    result = canConstruct(s, words3, wordsSize);
    printf("%d\n", result); // 输出0
    memset(iscounted, false, sizeof(iscounted));
    memset(memo, false, sizeof(memo));
    return 0;
}