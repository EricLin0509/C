#include "hashmap.h"

static size_t hash_table_index(hash_table *ht, Student *key)
{
    size_t result = (ht->hash(key->num, sizeof(Student)) % ht->size);
    return result;
}

hash_table *hash_table_create(uint32_t size, hashfunction *hf, cleanup *cf)
{
    hash_table *ht = calloc(1, sizeof(*ht));
    ht->size = size;
    ht->hash = hf;
    if (cf)
    {
        ht->clean = cf;
    }
    else
    {
        ht->clean = free;
    }
    ht->elements = calloc(sizeof(entry*), ht->size);
    return ht;
}

void hash_table_destory(hash_table *ht)
{
    for (uint32_t i = 0; i < ht->size; i++)
    {
        while (ht->elements[i])
        {
            entry *tmp = ht->elements[i];
            ht->elements[i] = ht->elements[i]->next;
            free(tmp->key);
            ht->clean(tmp->object);
            free(tmp);
        }
    }
    
    free(ht->elements);
    free(ht);
}

void hash_table_print(hash_table *ht)
{
    printf("Start...\n");
    for (uint32_t i = 0; i < ht->size; i++)
    {
        if (ht->elements[i] != NULL)
        {
            printf("\t%i\t\n", i);
            entry *tmp = ht->elements[i];
            while(tmp != NULL)
            {
                printf("\"%s\"(%p) - ", tmp->key->name, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("end...\n");
}

// 判断哈希表是否为空
bool hash_table_is_empty(hash_table *ht)
{
    if (ht == NULL) return true;
    for (uint32_t i = 0; i < ht->size; i++)
    {
        if (ht->elements[i] != NULL) return false;
    }
    return true;
}

bool hash_table_insert(hash_table *ht, Student *key, void *obj)
{
    if (key == NULL || obj == NULL) return false;
    size_t index = hash_table_index(ht, key);

    if (hash_table_lookup(ht, key) != NULL) return false; 

    // 新的入口
    entry *e = calloc(1, sizeof(*e));
    e->object = obj;
    // 新的key
    e->key = calloc(1, sizeof(Student));
    memcpy(e->key, key, sizeof(Student));

    // 插入入口
    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}

void *hash_table_delete(hash_table *ht, Student *key)
{
    if (key == NULL || ht == NULL) return false;
    size_t index = hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;
    while(tmp != NULL && tmp->key->num != key->num)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL)
    {
        // 删除元素
        ht->elements[index] = tmp->next;
    }
    else
    {
        prev->next = tmp->next;
    }
    free(tmp);
    return NULL;
}

void *hash_table_lookup(hash_table *ht, Student *key)
{
    if (key == NULL || ht == NULL) return false;
    size_t index = hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    while(tmp != NULL && tmp->key->num != key->num)
    {
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    return tmp->object;
}

void *find_target(hash_table *ht, int target, size_t *index)
{
    if (ht == NULL) return false;
    *index = ht->hash(target, sizeof(Student)) % ht->size;

    entry *tmp = ht->elements[*index];
    while(tmp != NULL && tmp->key->num != target)
    {
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    return tmp->key;
}