//
// Created by Weibo on 8/17/2022.
//


#include "linklist.h"
#include "data.h"
#include <assert.h>
#include <stdio.h>

#define MAX_STR_LEN 128


int main(int argc, char *argv[]){
    char address[MAX_STR_LEN];
    int match = 0;
    
    char* inFile = argv[2];
    char* outFile = argv[3];
    
    FILE *file = fopen(inFile, "r");
    FILE *f = fopen(outFile, "w");
    assert(file && outFile);
    
    list_t *dictionary = readData(file);
    fclose(file);
    
    while (scanf("%[^\n]\n", address) == 1){
        fprintf(f, "%s\n", address);
        match = search_list(dictionary, address, f);
        if(match == 0){
            printf("%s --> NOTFOUND\n", address);
        }else{
            printf("%s --> %d\n", address, match);
        }
    }

    free_list(dictionary);
    fclose(f);

}
