#ifndef FLUSH_H
#define FLUSH_H

// 清除屏幕
static void clear()
{
    // ANSI 转义序列
    printf("\e[1;1H\e[2J");
    printf("\e[?25h");
}

// 清空输入缓冲区
static void flush_input()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}

#endif