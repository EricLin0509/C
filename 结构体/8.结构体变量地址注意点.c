#include <stdio.h>
#include <string.h>

typedef struct students
{
    int num;
    char name[20];
    float score;
}STUDENT;

int main(int argc, const char * argv[]) {

STUDENT boy;

// 结构体变量的地址编号和结构他第一个成员的地址编号是一样的，但指针类型不同
printf("&boy=%zu\n",&boy);
printf("&boy+1=%zu\n",&boy+1); // 跳过整个结构体的大小
printf("&(boy.num)=%zu\n",&(boy.num));
printf("&(boy.num)+1=%zu\n",&(boy.num)+1); // 跳过一个结构体成员的大小

return 0;

}