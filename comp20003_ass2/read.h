//
// Created by Weibo on 9/6/2022.
//

#ifndef ASS_2_READ_H
#define ASS_2_READ_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LEN 512
#define MAX_STR_LEN 128
#define NUM_ATTRIBUTE 19
#define FALSE 0
#define TRUE 1
#define INIT_SIZE 2
#define DOUBLE_SIZE 2

typedef struct{
    int footpath_id;
    char* address;
    char* clue_sa;
    char* asset_type;
    double deltaz;
    double distance;
    double grade1in;
    int mcc_id;
    int mccid_int;
    double rlmax;
    double rlmin;
    char* segside;
    int status_id;
    int streetid;
    int street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
}record_t;

//Linked list structure prototype from Assignment1
typedef struct node node_t;

struct node{
    record_t *data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
}list_t;

typedef struct array array_t;



//linked_list operation from assignment1
list_t *make_empty_list(void);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, record_t *value);
void print_list(list_t *list);
int search_list(list_t *list, char* query, FILE *f);

//Data Operation and read all dataList
record_t *processData(char* buffer);
char** getAttribute(char* buffer);
void print_structure(record_t *record);

void fPrintStructure(record_t *record, FILE *file);
void free_data(record_t *data);



#endif //ASS_2_READ_H
