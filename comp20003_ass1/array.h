//
// Created by Weibo on 8/18/2022.
//

#ifndef ADS_ASS1_ARRAY_H
#define ADS_ASS1_ARRAY_H

#include "data.h"

#define INIT_SIZE 2
#define DOUBLE_SIZE 2

typedef struct array array_t;

struct array{
    node_t **A;
    int size;
    int n;
};


array_t *array_create();
void array_free(array_t *arr);
void array_shrink(array_t *arr);
void array_ensure_size(array_t *arr);
void sorted_array_insert(array_t *arr, node_t *node);
int cmp_grade_one_in(node_t *a, node_t *b);

int linear_search_array(array_t *arr, double target);
#endif //ADS_ASS1_ARRAY_H
