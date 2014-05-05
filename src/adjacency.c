#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#include "adjacency.h"

typedef struct _hash_list
{
	int a,b;
	int res;

	struct _hash_list *next;
} hash_list;

typedef struct _hash_table
{
	int size;
	hash_list **tab;
} hash_table;


hash_table* create_hash_table(int size)
{
	if(size < 1){
		return NULL;
	}
	hash_table *res = malloc(sizeof(hash_table));
	res->tab = malloc(sizeof(hash_list)*size);

	for(int i = 0; i < size; i++){
		res->tab[i] = NULL;
	}

	res->size = size;

	return res;
}

void delete_hash_table(hash_table *table)
{
	if(table == NULL){
		return;
	}

	for(int i = 0; i < table->size; i++){
		hash_list *tmp, *list;
		list = table->tab[i];
		while(list != NULL){
			tmp = list;
			list =  list->next;
			free(tmp);
		}
	}

	free(table->tab);
	free(table);
}

int hash_function(int a, int b, hash_table *table)
{
	return ((a << 3) + b) % table->size;
}

int find_value(int a, int b, hash_table *table)
{
	int res = -1;
	int hash_val = hash_function(a, b, table);
	hash_list *list = table->tab[hash_val];

	int found = 0;
	while(list != NULL && !found){
		if(list->a == a && list->b == b){
			res = list->res;
			found = 1;
		}
		list = list->next;
	}
	return res;
}

void insert_value(int a, int b, int res, hash_table *table)
{
	int hash_value = hash_function(a, b, table);
	hash_list *list = table->tab[hash_value];

	hash_list *tmp = malloc(sizeof(hash_list));
	tmp->a = a;
	tmp->b = b;
	tmp->res = res;
	tmp->next = list;
	table->tab[hash_value] = tmp;
}


hash_table *h_table;

void create_adjacency_table(uint32_t size)
{
	h_table = create_hash_table(size);
}

void insert_neighbours(uint32_t a, uint32_t b, uint32_t c)
{
	insert_value(a, b, c, h_table);
	insert_value(b, c, a, h_table);
	insert_value(c, a, b, h_table);
}

void delete_adjacency_table()
{
	delete_hash_table(h_table);
}

int32_t find_neighbour(uint32_t a, uint32_t b)
{
	return find_value(b, a, h_table);
}
