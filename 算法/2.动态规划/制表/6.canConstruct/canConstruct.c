#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canConstruct(char *target, char **wordBank, int wordBankSize)
{
    bool table[strlen(target) + 1]; // 创建一个基于 target 的数组

    memset(table, false, sizeof(table)); // 初始化数组
    table[0] = true; // 由于 canConstruct('', [...]) 无论如何都为 true，因此表格的第 0 位为 true

    for (int i = 0; i <= strlen(target); i++)
    {
        if (table[i] == true) // 如果当前位置为 true，那么开始比较
        {
            for (int j = 0; j < wordBankSize; j++) // 遍历给定的数组
            {
                int wordLength = strlen(wordBank[j]); // 获取数组中的元素的长度
                if (strncmp(target + i, wordBank[j], wordLength) == 0) // 如果当前位置加上偏移量等于给定的数组中的元素，那么将当前位置加上偏移量的位置设置为 true
                {
                    table[i + wordLength] = true;
                }
                if (table[strlen(target)] == true) // 如果已经组合成了 target，那么返回 true
                {
                    return true;
                }
            }
        }
    }
    return table[strlen(target)]; // 返回 table[target]
}

int main(int argc, const char * argv[]) {
    char *s = "abcdef";
    char *words1[] = {"ab", "abc", "cd", "def", "abcd"};
    int wordsSize = sizeof(words1) / sizeof(words1[0]);
    bool result = canConstruct(s, words1, wordsSize);
    printf("%d\n", result); // 输出1

    s = "skateboard";
    char *words2[] = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    wordsSize = sizeof(words2) / sizeof(words2[0]);
    result = canConstruct(s, words2, wordsSize);
    printf("%d\n", result); // 输出0

    s = "eeeeeeeeeeeeeeeeeeeeeeeeeeef";
    char *words3[] = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    wordsSize = sizeof(words3) / sizeof(words3[0]);
    result = canConstruct(s, words3, wordsSize);
    printf("%d\n", result); // 输出0
    return 0;
}