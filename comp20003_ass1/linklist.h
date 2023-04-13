#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "data.h"


/* function prototype */
list_t *make_empty_list(void);

void free_list(list_t *list);

list_t *insert_at_foot(list_t *list, record_t *value);

void print_list(list_t *list);

int search_list(list_t *list, char* query, FILE *f);

#endif