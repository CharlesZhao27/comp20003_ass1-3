//
// Created by Weibo on 8/18/2022.
//
#include "stage_two.h"

#include "data.h"
#include "linklist.h"
#include "array.h"

#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]){
    int value;
    double target;
    node_t *curr;
    
    char* inFile = argv[2];
    char* outFile = argv[3];
    
    /* read input file and store all data into linked list */
    FILE *in = fopen(inFile, "r");
    FILE *out = fopen(outFile, "w");
    assert(in && out);
    list_t *dictionary = readData(in);
    fclose(in);
    
    /* create an array to store the pointer to node in linked list*/
    array_t *sorted_arr = array_create();
    curr = dictionary->head;
    
    while(curr){
        sorted_array_insert(sorted_arr, curr);
        curr = curr->next;
    }
    array_shrink(sorted_arr);

    /* ask input from stdin and write output to the output.out*/
    while(scanf(" %lf\n", &target) == 1){
        fprintf(out, "%lf\n", target);
        value = linear_search_array(sorted_arr, target);
        stage_two_output(out, sorted_arr, value);
        printf("%g --> %g\n", target, sorted_arr->A[value]->data->gradeLin);
    }
    fclose(out);
    array_free(sorted_arr);
    free_list(dictionary);

}


void stage_two_output(FILE *out, array_t *arr, int index){

    fprintf(out, "--> footpath_id: %5d || address: %s || clue_sa: %s || asset_type: %s || "
               "deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
               "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d || "
               "streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf "
               "|| end_lat: %.6lf || end_lon: %.6lf ||\n",
            arr->A[index]->data->footpathId, arr->A[index]->data->address, arr->A[index]->data->clueSa, arr->A[index]->data->assetType,
            arr->A[index]->data->deltaz,arr->A[index]->data->distance, arr->A[index]->data->gradeLin, arr->A[index]->data->mccId,
            arr->A[index]->data->mccIdInt, arr->A[index]->data->rlmax, arr->A[index]->data->rlmin, arr->A[index]->data->segside,
            arr->A[index]->data->statusId, arr->A[index]->data->streetId, arr->A[index]->data->streetGroup,
            arr->A[index]->data->startLat, arr->A[index]->data->startLon, arr->A[index]->data->endLat, arr->A[index]->data->endLon);

}
