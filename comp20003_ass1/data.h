//
// Created by Weibo on 8/11/2022.
//
#include <stdio.h>
#include "linklist.h"

#ifndef _DATA_H_
#define _DATA_H_

/* define constants */
#define MAX_LINE_LEN 512
#define MAX_STR_LEN 128
#define NUM_ATTRIBUTE 19
#define FALSE 0
#define TRUE 1

/* typedef and struct */
typedef struct streetRecord{
    int footpathId;
    char *address;
    char *clueSa;
    char *assetType;
    double deltaz;
    double distance;
    double gradeLin;
    int mccId;
    int mccIdInt;
    double rlmax;
    double rlmin;
    char *segside;
    int statusId;
    int streetId;
    int streetGroup;
    double startLat;
    double startLon;
    double endLat;
    double endLon;
}record_t;

typedef struct node node_t;

struct node{
    record_t *data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
}list_t;

/* function prototype define */

list_t *readData(FILE *f);

record_t *processData(char* buffer);

char** getAttribute(char* buffer);

void print_structure(record_t *record);



#endif
