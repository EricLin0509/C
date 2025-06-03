#include <time.h>
#include "data.h"
#include "colour.h"
#include "flush.h"

#define MAX_LINE 4096

// 安全输入字符串
// 不要与flush_input()一起使用
// true: 输入的字符串超过了长度
// false: 输入的字符串没有超过长度
static bool secure_input(int length, char *str)
{
    bool result = false;
    char ch;
    int i = 0;
    int char_remain = 1;
    while(char_remain)
    {
        ch = getchar();

        if(i >= length - 1)
        {
            result = true;
        }

        if((ch == '\n') || (ch == EOF))
        {
            char_remain = 0;
        }
        else if (i < length - 1)
        {
            str[i] = ch;
            i++;
        }
    }
    str[i] = '\0';
    return result;
}

// 生成盐
static void rand_string(char *str)
{
    memcpy(str, "$6$", 3); // 算法选择
    char charset[] = "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(NULL));
    for (int i = 3; i < 10; i++)
    {
        size_t index = (double) rand() / RAND_MAX * (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[11] = '\0';
}

// 查找目标
static void check_student(hash_table *table, Student **student, size_t *index)
{
    int num;
check:
    // 从键盘输入学生信息
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's number: "));
    scanf("%d", &num);
    flush_input();

    // 检查学号是否已存在
    if ((*student = find_target(table, num, index)) == NULL)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Student not found! 😢\n"));
        goto check;
    }
}

// 学号输入
static void num_input(hash_table *table, Student *stu)
{
    int temp_num;
    size_t index;
num:
    temp_num = -1;
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's number: "));
    scanf("%d", &temp_num);
    flush_input();
    if(temp_num <= 0)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Invalid number! 😢\n"));
        goto num;
    }
    else if (find_target(table, temp_num, &index) != NULL)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Student already exists! 😢\n"));
        goto num;
    }
    stu->num = temp_num;
}

// 年龄输入
static void age_input(unsigned int *age)
{
    int temp_age;
age:
    temp_age = -1;
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's age: "));
    scanf("%d", &temp_age);
    flush_input();

    if (temp_age > 150 || temp_age < 1)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❓Are you serious? 😅\n"));
        goto age;
    }

    *age = temp_age;
}

// 性别输入
static void sex_input(char *sex)
{
    char temp_sex;
sex:
    temp_sex = '\0';
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's sex (M/F): "));
    scanf("%c", &temp_sex);
    flush_input();
    if (temp_sex == 'M' || temp_sex =='m')
    {
        *sex = 'M';
        return;
    }
    else if (temp_sex == 'F' || temp_sex == 'f')
    {
        *sex = 'F';
        return;
    }
    else
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Invalid sex! 😢\n"));
        goto sex;
    }
}

// 身份验证
static void authentication(char *password, char *salt)
{
    char temp_password[MAX_PASSWORD];
auth:
    printf(ANSI_COLOR_YELLOW_BOLD "%s" ANSI_COLOR_RESET, gettext("Input your password: "));
    secure_input(MAX_PASSWORD, temp_password);
    char *crypt_password = crypt(temp_password, salt);
    if (strcmp(crypt_password, password) != 0)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Incorrect password! 😢\n"));
        goto auth;
    }
    return;
}

bool is_invalid_password = false; // 全局变量，用于判断密码是否合法
// 密码输入
// is_modify: 判断是否是修改密码
static void password_input(char *password, char *salt, bool is_modify)
{
    struct crypt_data data[2] = {0}; // 加密数据
    char old_salt[SALT_SIZE]; // 旧盐
    char new_salt[SALT_SIZE]; // 新盐
    char temp_password[MAX_PASSWORD]; // 临时密码
    char confirm_password[MAX_PASSWORD]; // 确认密码
password:
    memcpy(old_salt, salt, SALT_SIZE);
    rand_string(new_salt);
    if (is_modify)
    {
        printf(ANSI_COLOR_YELLOW_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter your new password: "));
    }
    else
    {
        printf(ANSI_COLOR_YELLOW_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter your password: "));
    }
    is_invalid_password = secure_input(MAX_PASSWORD, temp_password);
    char *crypt_password = crypt_r(temp_password, new_salt, &data[0]); // 新密码加密
    char *old_crypt_password = crypt_r(temp_password, old_salt, &data[1]); // 旧密码加密
    if (is_invalid_password)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Password is too long! 😢\n"));
        goto password;
    }
    else if (is_modify && strcmp(old_crypt_password, password) == 0)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗New password cannot be the same as the old password! 😢\n"));
        goto password;
    }
    else if (temp_password[0] == '\0')
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Password cannot be empty! 😢\n"));
        goto password;
    }
    printf(ANSI_COLOR_ORANGE_BOLD "%s" ANSI_COLOR_RESET, gettext("Confirm your password: "));
    secure_input(MAX_PASSWORD, confirm_password);
    if (strcmp(temp_password, confirm_password) != 0)
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Password does not match! 😢\n"));
        goto password;
    }
    if (is_modify)
    {
        memset(password, 0, PASSWORD_LEN); // 清空密码
        memset(salt, 0, SALT_SIZE); // 清空盐
    }
    memcpy(password, crypt_password, strlen(crypt_password)); // 保存密码
    memcpy(salt, new_salt, SALT_SIZE); // 保存盐
}

// 输出学生信息
static void print_student(Student *s)
{
    printf(ANSI_COLOR_BLUE "%s %d\n" ANSI_COLOR_RESET, 
           gettext("Student number:"), s->num);
    printf(ANSI_COLOR_GREEN "%s %s\n" ANSI_COLOR_RESET, 
           gettext("Student name:"), s->name);
    printf(ANSI_COLOR_ORANGE "%s %d\n" ANSI_COLOR_RESET,
           gettext("Student age:"), s->age);
    printf(ANSI_COLOR_YELLOW "%s %c\n" ANSI_COLOR_RESET,
           gettext("Student sex:"), s->sex);
    printf(ANSI_COLOR_RED "%s %s\n" ANSI_COLOR_RESET,
           gettext("Student note:"), s->note);
}

// 初始化数据
void init_data(FILE *fp, hash_table *table)
{
    fp = fopen("data.txt", "r");
    char buffer[MAX_LINE];
    while(!feof(fp) && fgets(buffer, MAX_LINE, fp)!= NULL)
    {
        buffer[strcspn(buffer, "\n")] = 0;
        Student *stu = calloc(1, sizeof(Student));
        sscanf(buffer, "%s %s %d %d %c %s %[^\n]", stu->password, stu->salt, &stu->num, &stu->age, &stu->sex, stu->note, stu->name);
        hash_table_insert(table, stu, stu);
    }
    fclose(fp);
}

// 插入数据
void insert_data(FILE *fp, hash_table *table)
{

    Student *student = calloc(1, sizeof(Student));
    
    // 从键盘输入学生学号
    num_input(table, student);

    // 从键盘输入学生信息
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's name: "));
    secure_input(MAX_LEN, student->name);
    
    age_input(&student->age);

    sex_input(&student->sex);

    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter the student's note: "));
    secure_input(MAX_LEN, student->note);

    password_input(student->password, student->salt, false);

    clear();
    if (hash_table_insert(table, student, student))
    {
        printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Here is the information you entered: 😊\n"));
        print_student(student);

        fp = fopen("data.txt", "a");
        fprintf(fp, "%s %s %d %d %c %s %s\n", student->password, student->salt, student->num, student->age, student->sex, student->note, student->name);
        fclose(fp);   
    }
    else
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("Insert failed! 😢\n"));
    }
}

// 重写data.txt
static void rewrite_data(FILE *fp, hash_table *table)
{
    fp = fopen("data.txt", "w");
    for (uint32_t i = 0; i < table->size; i++)
    {
        if (table->elements[i] != NULL)
        {
            entry *tmp = table->elements[i];
            while(tmp != NULL)
            {
                fprintf(fp, "%s %s %d %d %c %s %s\n", tmp->key->password, tmp->key->salt, tmp->key->num, tmp->key->age, tmp->key->sex, tmp->key->note, tmp->key->name);
                tmp = tmp->next;
            }
        }
    }
    fclose(fp);
}

// 删除数据
void delete_data(FILE *fp, hash_table *table)
{

    if (hash_table_is_empty(table))
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗No data inside, please add some data first! 😢\n"));
        return;
    }

    size_t index;

    Student *student = NULL;

    check_student(table, &student, &index);

    authentication(student->password, student->salt);

    clear();
    printf(ANSI_COLOR_YELLOW_BOLD "%s" ANSI_COLOR_RESET, gettext("Here is the information you want to delete: 😊\n"));
    print_student(student);

    printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Are you sure to delete this information? 🤔(Y/N): "));
    char confirm;
    scanf("%c", &confirm);
    flush_input();

    if (confirm != 'Y' && confirm != 'y')
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("Delete canceled! 😢\n"));
        return;
    }

    entry *tmp = table->elements[index];
    table->elements[index] = NULL;
    free(tmp);
    
    printf(ANSI_COLOR_GREEN_BOLD "%s" ANSI_COLOR_RESET, gettext("Deleted! 😊\n"));
    rewrite_data(fp, table);
}

// 查找目标
void search_data(hash_table *table)
{
    if (hash_table_is_empty(table))
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗No data inside, please add some data first! 😢\n"));
        return;
    }

    size_t index;

    Student *student = NULL;

    check_student(table, &student, &index);

    authentication(student->password, student->salt);

    clear();
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Here is the information you want to search: 😊\n"));
    print_student(student);
}

// 修改数据
void modify_data(FILE *fp, hash_table *table)
{

    if (hash_table_is_empty(table))
    {
        printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗No data inside, please add some data first! 😢\n"));
        return;
    }

    size_t index;

    Student *student = NULL;

    check_student(table, &student, &index);

    authentication(student->password, student->salt);

    clear();
    
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Here is the current information: 😊\n"));
    print_student(student);
    puts("\n");

    int choice; // 选择

choice:

    choice = -1; // 初始化

    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Choose the information you want to modify: \n"));
    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, gettext("1. Name\n"));
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, gettext("2. Age\n"));
    printf(ANSI_COLOR_ORANGE "%s" ANSI_COLOR_RESET, gettext("3. Sex\n"));
    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, gettext("4. Note\n"));
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, gettext("5. Password\n"));
    printf("%s", gettext("0. Cancel\n"));
    scanf("%d", &choice);
    flush_input();
    
    switch (choice)
    {
        case 1:
            printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Please enter the student's name: "));
            secure_input(MAX_LEN, student->name);
            break;
        case 2:
            age_input(&student->age);
            break;
        case 3:
            sex_input(&student->sex);
            break;
        case 4:
            printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Please enter the student's note: "));
            secure_input(MAX_LEN, student->note);
            break;
        case 5:
            password_input(student->password, student->salt, true);
            break;
        case 0:
            printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Modify canceled! 😢\n"));
            return;
        default:
            printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("❗Invalid choice! 😢\n"));
            goto choice;
    }
    clear();
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Here is the information you modified: 😊\n"));
    print_student(student);
    rewrite_data(fp, table);
}