#ifndef STUDENT_H
#define STUDENT_H

#define MAX_LEN 256
#define TABLE_SIZE 100
#define MAX_PASSWORD 21
#define PASSWORD_LEN 107
#define SALT_SIZE 12

typedef struct Studtent
{
    char password[PASSWORD_LEN];
    char salt[SALT_SIZE];
    unsigned int num;
    unsigned int age;
    char sex;
    char name[256];
    char note[256];
} Student;

#endif