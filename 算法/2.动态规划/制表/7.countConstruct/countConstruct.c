#include <stdio.h>
#include <string.h>

int countConstruct(char *target, char **wordBank, int wordBankSize)
{
    int table[strlen(target) + 1]; // 创建一个基于 target 的数组
    memset(table, 0, sizeof(table)); // 初始化数组

    table[0] = 1; // 由于 countConstruct("", [...]) 无论如何都可以拼接成空字符串，所以表格第 0 行初始值为 1

    for (int i = 0; i <= strlen(target); i++)
    {
        if (table[i] > 0) // 如果当前位置的值大于 0
        {
            for (int j = 0; j < wordBankSize; j++)
            {
                int wordLength = strlen(wordBank[j]);
                if (strncmp(target + i, wordBank[j], wordLength) == 0) // 如果当前位置的字符串与 wordBank 中的字符串匹配
                {
                    table[i + wordLength] += table[i]; // 将当前位置的值加到下一个位置的值上
                }
            }
        }
    }
    return table[strlen(target)]; // 返回表格的最后一个值
}

int main(int argc, const char * argv[]) {
    char *s = "purple";
    char *words1[] = {"purp", "p", "ur", "le", "purpl"};
    int wordsSize = sizeof(words1) / sizeof(words1[0]);
    int result = countConstruct(s, words1, wordsSize);
    printf("%d\n", result); // 输出2
    
    s = "skateboard";
    char *words2[] = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
    wordsSize = sizeof(words2) / sizeof(words2[0]);
    result = countConstruct(s, words2, wordsSize);
    printf("%d\n", result); // 输出0

    s = "enterapotentpot";
    char *words4[] = {"a", "p", "ent", "enter", "ot", "o", "t"};
    wordsSize = sizeof(words4) / sizeof(words4[0]);
    result = countConstruct(s, words4, wordsSize);
    printf("%d\n", result); // 输出4

    s = "eeeeeeeeeeeeeeeeeeeeeeeeeeef";
    char *words3[] = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    wordsSize = sizeof(words3) / sizeof(words3[0]);
    result = countConstruct(s, words3, wordsSize);
    printf("%d\n", result); // 输出0
    return 0;
}