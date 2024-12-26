#include <stdio.h>

int main(int argc, char * argv[], char * envp[]) { // 根据C语言标准，main函数的返回值类型必须是int


    // argc (argument count) 是一个整数，用于表示命令行参数的数量
    // argv (argument vector) 是一个指针数组，用于存储命令行参数的字符串
    printf("argc: %d\n\n", argc); // 打印 argc 的值
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n\n", i, argv[i]); // 打印 argv 数组中的每个元素
    }
    
    
    // envp (environment pointer) 是一个指针数组，用于存储环境变量的字符串
    for (int i = 0; envp[i] != NULL; i++) // envp 以 NULL 结尾
    {
        printf("envp[%d]: %s\n", i, envp[i]); // 打印 envp 数组中的每个元素
    }
    // 注意：envp 没有长度，所以需要判断是否为空


    return 0; // 返回一个整数作为程序的退出状态 (状态码)，告诉操作系统程序是否成功执行
    // 状态码可以在 errno.h 头文件中找到
}