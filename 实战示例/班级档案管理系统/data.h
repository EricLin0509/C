#ifndef DATA_H
#define DATA_H

#include <crypt.h>
#include <locale.h>
#include <libintl.h>
#include "hashmap.h"

void init_data(FILE *fp, hash_table *table);
void insert_data(FILE *fp, hash_table *table);
void delete_data(FILE *fp, hash_table *table);
void search_data(hash_table *table);
void modify_data(FILE *fp, hash_table *table);

#endif