# include <stdio.h>
# include <string.h>

int main(int argc, char *argv[]) {

// 容易遗忘的 '\0'
// 字符串都以 '\0' 结尾
int length = strlen(argv[1])+1; // 由于 strlen() 不包含 '\0' ,所以要加1
char password[length];
memcpy(password,argv[1],length);

if (strcmp(password, "super secret") == 0)
{
    printf("Correct password\n");
}
else
{
    printf("Incorrect password, try again\n");
}

}