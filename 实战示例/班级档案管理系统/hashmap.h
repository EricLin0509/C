#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "student.h"

typedef uint64_t (hashfunction) (int, size_t);
typedef void cleanup(void *);

typedef struct entry
{
    Student *key;
    void *object;
    struct entry *next;
} entry;

typedef struct _hash_table
{
    uint32_t size; // 哈希表大小
    hashfunction *hash; // 哈希值
    cleanup *clean; // 清理函数
    entry **elements; // 入口
} hash_table;

hash_table *hash_table_create(uint32_t size, hashfunction *hf, cleanup *cf);
void hash_table_destory(hash_table *ht);
void hash_table_print(hash_table *ht);
bool hash_table_is_empty(hash_table *ht);
bool hash_table_insert(hash_table *ht, Student *key, void *obj);
void *hash_table_delete(hash_table *ht, Student *key);
void *hash_table_lookup(hash_table *ht, Student *key);
void *find_target(hash_table *ht, int target, size_t *index);

#endif