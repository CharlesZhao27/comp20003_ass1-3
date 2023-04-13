#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linklist.h"
#include "data.h"

list_t *readData(FILE *f){

    char *buffer = malloc(sizeof(char) * MAX_LINE_LEN + 1);
    assert(buffer);

    fscanf(f, "%[^\n]\n", buffer);            // read the header file and skip the header

    list_t *list = make_empty_list();

    while(fscanf(f, "%[^\n]\n", buffer ) == 1){
        record_t *record = processData(buffer);            //process data and store it into a structure
        //print_structure(record);
        list = insert_at_foot(list, record);         //insert it into the linked list
    }
    free(buffer);
    return(list);
}

/* Process the data in buffer, buffer is one row in the csv file */
record_t *processData(char* buffer){

    record_t *record = malloc(sizeof(record_t));
    assert(record);

    char** attribute = getAttribute(buffer);               //split buffer and store all attribute into array

    /* Assign value to the node individually */
    record->footpathId = atoi(attribute[0]);

    //assign address to the record node
    record->address = malloc(sizeof(char) * strlen(attribute[1]) + 1);
    assert(record->address);
    strcpy(record->address, attribute[1]);

    //assign clue_sa to the record node
    record->clueSa = malloc(sizeof(char) * strlen(attribute[2]) + 1);
    assert(record->clueSa);
    strcpy(record->clueSa, attribute[2]);

    //assign assetType to the record node
    record->assetType = malloc(sizeof(char) * strlen(attribute[3]) + 1);
    assert(record->assetType);
    strcpy(record->assetType, attribute[3]);

    record->deltaz = atof(attribute[4]);
    record->distance = atof(attribute[5]);
    record->gradeLin = atof(attribute[6]);
    record->mccId = atoi(attribute[7]);
    record->mccIdInt = atoi(attribute[8]);
    record->rlmax = atof(attribute[9]);
    record->rlmin = atof(attribute[10]);

    //assign segside to the record node
    record->segside = malloc(sizeof(char) * strlen(attribute[11]) + 1);
    assert(record->segside);
    strcpy(record->segside, attribute[11]);

    record->statusId = atoi(attribute[12]);
    record->streetId = atoi(attribute[13]);
    record->streetGroup = atoi(attribute[14]);
    record->startLat = atof(attribute[15]);
    record->startLon = atof(attribute[16]);
    record->endLat = atof(attribute[17]);
    record->endLon = atof(attribute[18]);


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
           "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d || "
           "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
           "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
           record->footpathId, record->address, record->clueSa, record->assetType, record->deltaz,
           record->distance, record->gradeLin, record->mccId, record->mccIdInt, record->rlmax,
           record->rlmin, record->segside, record->statusId, record->streetId, record->streetGroup,
           record->startLat, record->startLon, record->endLat, record->endLon);
}
