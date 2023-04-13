//
// Created by Weibo on 8/18/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>


#include "data.h"
#include "array.h"


array_t *array_create(){
    array_t *arr = malloc(sizeof(*arr));
    assert(arr);
    int size = INIT_SIZE;
    arr->size = size;
    arr->A = malloc(size * sizeof(*(arr->A)));
    assert(arr->A);
    arr->n = 0;
    return(arr);
}

void array_free(array_t *arr){
    for(int i = 0; i < arr->n; i++){

        /* free a node of linked list here -- free inside the linked list */
        //free(arr->A[i]->data->address);
        //free(arr->A[i]->data->clueSa);
        //free(arr->A[i]->data->assetType);
        //free(arr->A[i]->data->segside);
        //free(arr->A[i]);

    }
    //free(arr->A);
    free(arr);
}

/* reduce size of array to the same as the number of element used*/
void array_shrink(array_t *arr){
    if(arr->size != arr->n){
        arr->size = (arr->n > INIT_SIZE) ? arr->n : INIT_SIZE;
        arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
        assert(arr->A);
    }
}

void array_ensure_size(array_t *arr){
    if(arr->n == arr->size){
        arr->size *= DOUBLE_SIZE;
        arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
        assert(arr->A);
    }
}

void sorted_array_insert(array_t *arr, node_t *node){
    int i;
    array_ensure_size(arr);

    if(arr->n == 0){
        /* when n=0, it's an empty array, insert one node into array*/
        arr->A[arr->n] = node;
        arr->n++;
    }else{
        /* if array size >= 1, we can insert in as a sorted_array*/
        for(i = arr->n-1; i>=0 && cmp_grade_one_in(node, arr->A[i]) == -1; i--){
            arr->A[i+1] = arr->A[i];
        }
        arr->A[i+1] = node;
        arr->n++;
    }
}

int cmp_grade_one_in(node_t *a, node_t *b){
    if(a->data->gradeLin < b->data->gradeLin) return(-1);
    if(a->data->gradeLin > b->data->gradeLin) return(+1);
    return(0);
}

/* return index of arr->A when we find the closest grade1in*/
int linear_search_array(array_t *arr, double target){

    int i, closest_match;
    double diff, min_diff;

    for(i = 0; i< arr->n; i++){

        diff = fabs(fabs(arr->A[i]->data->gradeLin) - fabs(target));
        //printf("Curr value: %lf, abs dif is %lf\n",arr->A[i]->data->gradeLin, diff);
        if(i == 0){
            min_diff = diff;
            closest_match = 0;
        } else{
            if(diff < min_diff){
                min_diff = diff;
                closest_match = i;
            }
        }
    }
    return(closest_match);
}

