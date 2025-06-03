#include <unistd.h>
#include "data.h"
#include "flush.h"
#include "colour.h"

uint64_t hash(int num, size_t length)
{
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += num;
        hash_value = (hash_value * num) * num; // 随机化
    }
    
    return hash_value;
}

// 是否为ROOT用户
void is_root()
{
    if (geteuid() == 0)
    {
        printf(ANSI_COLOR_ORANGE_BOLD "%s" ANSI_COLOR_RESET, gettext("❗You are running as root, it may cause some problems❗\n"));
        printf(ANSI_COLOR_ORANGE_BOLD "%s" ANSI_COLOR_RESET, gettext("Are you sure to continue the proecess? (Y/N): 🤔"));
        char choice;
        scanf("%c", &choice);
        flush_input();
        if (choice !='Y' && choice!='y')
        {
            clear();
            printf(ANSI_COLOR_RED_BOLD "%s" ANSI_COLOR_RESET, gettext("Exiting...\n"));
            exit(1);
        }
    }
}

int main(int argc, const char * argv[]) {

    // 初始化

    setlocale(LC_ALL, ""); // 设置本地化环境，支持中文输出
    bindtextdomain("management", "locales"); // 设置消息目录
    textdomain("management"); // 设置消息域

    is_root();

    FILE *fp = NULL;
    const int tablesize = (1 << 20);
    hash_table *table = hash_table_create(tablesize, hash, NULL);
    init_data(fp, table);

    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, gettext("Welcome to student management system 😊\n"));
    usleep(500000);
start:
    clear();
    int choice = -1;
    printf(ANSI_COLOR_CYAN_BOLD "%s" ANSI_COLOR_RESET, gettext("Enter your choice: \n"));
    printf(ANSI_COLOR_LIGHTBLUE "%s" ANSI_COLOR_RESET, gettext("1. Check student information\n"));
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, gettext("2. Add student information\n"));
    printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, gettext("3. Modify student information\n"));
    printf(ANSI_COLOR_ORANGE "%s" ANSI_COLOR_RESET, gettext("4. Delete student information\n"));
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, gettext("0. Exit\n"));
    scanf("%d", &choice);
    flush_input();
    switch (choice)
    {
    case 1:
        // 查看学生信息
        clear();
        search_data(table);
        printf(ANSI_COLOR_MAGENTA_BOLD "%s" ANSI_COLOR_RESET, gettext("Press [enter] to continue\n"));
        flush_input();
        goto start;
        break;
    case 2:
        // 添加学生信息
        clear();
        insert_data(fp, table);
        printf(ANSI_COLOR_MAGENTA_BOLD "%s" ANSI_COLOR_RESET, gettext("Press [enter] to continue\n"));
        flush_input();
        goto start;
        break;
    case 3:
        // 修改学生信息
        clear();
        modify_data(fp, table);
        printf(ANSI_COLOR_MAGENTA_BOLD "%s" ANSI_COLOR_RESET, gettext("Press [enter] to continue\n"));
        flush_input();
        goto start;
        break;
    case 4:
        // 删除学生信息
        clear();
        delete_data(fp, table);
        printf(ANSI_COLOR_MAGENTA_BOLD "%s" ANSI_COLOR_RESET, gettext("Press [enter] to continue\n"));
        flush_input();
        goto start;
        break;
    case 0:
        // 退出
        clear();
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, gettext("Thank you for using student management system 😀\n"));
        hash_table_destory(table);
        return 0;
    default:
        goto start;
    }

    return 0;
}