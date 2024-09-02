#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
 {
    int  a = 3;
    float b =4;
 } // 复合语句

/* if (表达式) 只限定后面的语句
 {
 语句1;
 语句2;
 } 
 */
    //  int a = 190;
    //  if (a < 90)
        // printf("Game Over!\n");
    
    // printf("后续语句\n");

    char temp = 0;
    printf("请输入一个字符\n");
    scanf("%c",&temp);

    if (temp >='0' && temp <= '9')
    {
        printf("这是一个数字\n");
    }

    if (temp >= 'A' && temp <= 'Z' )
    {
        printf("这是一个大写字母\n");
    }

    if(temp >= 'a' && temp <= 'z')
    {
        printf("这是一个小写字母");
    }
    return 0;
}