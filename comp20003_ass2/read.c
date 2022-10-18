//
// Created by Weibo on 9/6/2022.
//

#include "read.h"
#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


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
        free(prev->data->clue_sa);
        free(prev->data->asset_type);
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
                       "rlmax: %.2lf || rlmin: %.2lf || segside: %s || status_id: %d || "
                       "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
                       "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
                    curr->data->footpath_id, curr->data->address, curr->data->clue_sa, curr->data->asset_type,
                    curr->data->deltaz, curr->data->distance, curr->data->grade1in, curr->data->mcc_id,
                    curr->data->mccid_int, curr->data->rlmax, curr->data->rlmin, curr->data->segside,
                    curr->data->status_id, curr->data->streetid, curr->data->street_group,
                    curr->data->start_lat, curr->data->start_lon, curr->data->end_lat, curr->data->end_lon);
        }
        curr = curr->next;
    }



    return(match);
}


/* Process the dataList in buffer, buffer is one row in the csv file */
record_t *processData(char* buffer){

    record_t *record = malloc(sizeof(record_t));
    assert(record);

    char** attribute = getAttribute(buffer);               //split buffer and store all attribute into array

    /* Assign value to the node individually */
    char *ptr;
    record->footpath_id = atoi(attribute[0]);

    //assign address to the record node
    record->address = malloc(sizeof(char) * strlen(attribute[1]) + 1);
    assert(record->address);
    strcpy(record->address, attribute[1]);

    //assign clue_sa to the record node
    record->clue_sa = malloc(sizeof(char) * strlen(attribute[2]) + 1);
    assert(record->clue_sa);
    strcpy(record->clue_sa, attribute[2]);

    //assign assetType to the record node
    record->asset_type = malloc(sizeof(char) * strlen(attribute[3]) + 1);
    assert(record->asset_type);
    strcpy(record->asset_type, attribute[3]);

    record->deltaz = strtod(attribute[4], &ptr);
    record->distance = strtod(attribute[5], &ptr);
    record->grade1in = strtod(attribute[6], &ptr);
    record->mcc_id = atoi(attribute[7]);
    record->mccid_int = atoi(attribute[8]);
    record->rlmax = strtod(attribute[9], &ptr);
    record->rlmin = strtod(attribute[10], &ptr);

    //assign segside to the record node
    record->segside = malloc(sizeof(char) * strlen(attribute[11]) + 1);
    assert(record->segside);
    strcpy(record->segside, attribute[11]);

    record->status_id = atoi(attribute[12]);
    record->streetid = atoi(attribute[13]);
    record->street_group = atoi(attribute[14]);
    record->start_lat = strtod(attribute[15], &ptr);
    record->start_lon = strtod(attribute[16], &ptr);
    record->end_lat = strtod(attribute[17], &ptr);
    record->end_lon = strtod(attribute[18], &ptr);


    /* free attribute char array and inside the array */
    for(int i= 0; i < NUM_ATTRIBUTE; i++){
        free(attribute[i]);
    }
    free(attribute);

    return record;
}

/* split the buffer by deliminator and store all attribute into array*/
char** getAttribute(char* buffer){

    char** attribute = malloc(sizeof(char*) * NUM_ATTRIBUTE);
    assert(attribute);

    int i = 0;
    int quotationMark = 0;
    int field_index = 0;
    char temp[MAX_STR_LEN + 1];
    int temp_index = 0;

    /* loop through the buffer, and split the attribute by ",", contain 2 special case  */
    while(buffer[i] != '\0' && buffer[i] != EOF && buffer[i] != '\n'){

        if(buffer[i] == ','){
            if(quotationMark == FALSE){
                /* case: comma is the separator of different attribute */
                temp[temp_index] = '\0';
                attribute[field_index] = malloc(sizeof(char) * strlen(temp) + 1);
                assert(attribute[field_index]);

                strcpy(attribute[field_index], temp);

                /* process to next attribute */
                field_index++;
                i++;
                // 重置temp和temp的index
                temp_index = 0;

            }else{
                /* case: comma is a character in the string, keep reading into temp[] */
                temp[temp_index] = buffer[i];
                temp_index++;
                i++;
            }

        } else if(buffer[i] == '"'){
            /* check the quotation mark and does this influence the split of attribute */
            if(quotationMark == FALSE){
                quotationMark = TRUE;
                i++;
            }else{
                quotationMark = FALSE;
                i++;
            }
        } else{
            /* normal case, which we need to add buffer[i] char to the temp[] */
            temp[temp_index] = buffer[i];
            temp_index++;
            i++;
        }

    }

    /* store last temp value into attribute array */
    temp[temp_index] = '\0';
    attribute[field_index] = malloc(sizeof(char) * strlen(temp) + 1);
    assert(attribute[field_index]);
    strcpy(attribute[field_index], temp);

    return(attribute);
}


void print_structure(record_t *record){
    printf("--> footpath_id: %5d || address: %s || clue_sa: %s || asset_type: %s || "
           "deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
           "rlmax: %.2lf || rlmin: %.2lf || segside: %s || status_id: %d || "
           "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
           "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
           record->footpath_id, record->address, record->clue_sa, record->asset_type, record->deltaz,
           record->distance, record->grade1in, record->mcc_id, record->mccid_int, record->rlmax,
           record->rlmin, record->segside, record->status_id, record->streetid, record->street_group,
           record->start_lat, record->start_lon, record->end_lat, record->end_lon);
}


void fPrintStructure(record_t *record, FILE *file){
    fprintf(file,"--> footpath_id: %5d || address: %s || clue_sa: %s || asset_type: %s || "
                 "deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
                 "rlmax: %.2lf || rlmin: %.2lf || segside: %s || status_id: %d || "
                 "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
                 "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
            record->footpath_id, record->address, record->clue_sa, record->asset_type, record->deltaz,
            record->distance, record->grade1in, record->mcc_id, record->mccid_int, record->rlmax,
            record->rlmin, record->segside, record->status_id, record->streetid, record->street_group,
            record->start_lat, record->start_lon, record->end_lat, record->end_lon);
}

void free_data(record_t *data){
    //free allocated memory in data
    free(data->address);
    free(data->clue_sa);
    free(data->asset_type);
    free(data->segside);
    //free data pointer itself
    free(data);
}
