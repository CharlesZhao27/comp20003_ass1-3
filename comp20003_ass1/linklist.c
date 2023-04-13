#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linklist.h"

list_t *make_empty_list(void) {
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->foot = NULL;
    return list;
}

/* free linked list */
void free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;

        /* free all char* type in the pointer to structure */
       free(prev->data->address);
       free(prev->data->clueSa);
       free(prev->data->assetType);
       free(prev->data->segside);
        /* free the structure and the node of the linked list */
        free(prev->data);
        free(prev);

    }
    free(list);
}

/* insert node at foot of the linked list */
list_t *insert_at_foot(list_t *list, record_t *value) {

    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(list!=NULL && new!=NULL);

    new->data = value;
    new->next = NULL;
    if (list->foot==NULL) {
        /* this is the first insertion into the list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

/* print_list */
void print_list(list_t *list){
    node_t *curr;
    curr = list->head;
    while (curr){
        print_structure(curr->data);
        curr = curr->next;
    }
}

int search_list(list_t *list, char* query, FILE *f){
    int match = 0;
    node_t  *curr;
    curr = list->head;

    while(curr){
        if(strcmp(curr->data->address, query) == 0){
            match += 1;
            fprintf(f, "--> footpath_id: %5d || address: %s || clue_sa: %s || asset_type: %s || "
                       "deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
                       "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d || "
                       "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
                       "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
                    curr->data->footpathId, curr->data->address, curr->data->clueSa, curr->data->assetType,
                    curr->data->deltaz,curr->data->distance, curr->data->gradeLin, curr->data->mccId,
                    curr->data->mccIdInt, curr->data->rlmax, curr->data->rlmin, curr->data->segside,
                    curr->data->statusId, curr->data->streetId, curr->data->streetGroup,
                    curr->data->startLat, curr->data->startLon, curr->data->endLat, curr->data->endLon);
        }
        curr = curr->next;
    }
    

    
    return(match);
}