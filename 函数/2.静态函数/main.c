#include <stdio.h>

// 在C语言默认情况下，函数是全局的，可以在任何地方调用

void func(); // 函数声明

// void sfunc(); // 无法在main函数中调用，因为sfunc是静态函数

void report();

static void print()
{
    printf("Bonjour!\n");
}


int main(int argc, const char *argv[]) {

func();

// sfunc();

report(); // 调用静态函数

print(); // 虽然在main函数中调用了静态函数print，但调用的是 main.c 中的静态函数print，而不是 func.c 中的静态函数print

return 0;

}

// 输入 'gcc -o main main.c func.c' 编译