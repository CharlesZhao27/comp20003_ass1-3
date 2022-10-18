#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadtree.h"
#include "struct.h"
#include "read.h"

#define MINARGS 4
#define EXPECTED_STAGE "3"

int main(int argc, char *argv[]) {

    //check the argument input when calling this function
    if(argc < MINARGS){
        fprintf(stderr, "Insufficient arguments, run in form:\n"
                        "\t./dict3 3 <input dataset> <output file> < <keys file>\n");
        exit(EXIT_FAILURE);
    }

    //check the stage number when calling this function
    if (strcmp(EXPECTED_STAGE, argv[1]) != 0){
        fprintf(stderr, "Expected stage was %s, received %s\n", EXPECTED_STAGE, argv[1]);
        exit(EXIT_FAILURE);
    }

    //file operation and check the input and output file
    FILE* inFIle = fopen(argv[2],"r");
    FILE* outFile = fopen(argv[3], "w");
    assert(inFIle && outFile);


    //find initial bound
    char *ptr;
    point_t *bot_left, *top_right;
    bot_left = buildPoint(strtold(argv[4], &ptr), strtold(argv[5], &ptr));
    top_right = buildPoint(strtold(argv[6], &ptr), strtold(argv[7], &ptr));
    rectangle_t *initial_region;
    initial_region = createRectangle(bot_left, top_right);

    //initial a quadtree node 
    treeNode_t *root;
    root = buildTreeNode(initial_region);


    //read data from CSV file and insert them into the quadTree
    root = readData(inFIle, root);
    fclose(inFIle);

    //accept query file from stdin and search position inside the tree
    char* temp1 = malloc(sizeof(MAX_STR_LEN + 1));
    char* temp2 = malloc(sizeof(MAX_STR_LEN + 1));
    assert(temp1 && temp2);
    
    while(scanf("%s %s\n", temp1, temp2) == 2){
        
        //print header
        fprintf(outFile, "%s %s\n ", temp1, temp2);
        printf("%s %s -->", temp1, temp2);
//      printf("Inspecting temp1: %s %s\n", temp1, temp2);
        double x1, x2;
        x1 = strtod(temp1, &ptr);
        x2 = strtod(temp2, &ptr);
        
        datalist_t* result = searchPoint(root, buildPoint(x1, x2));
        datapoint_t* curr = result->head;
        while(curr){
            fPrintStructure(curr->footpath, outFile);
            curr = curr->next;
        }
        printf("\n");
    }

    
//  point_t *queryPoint;
//  char *query = malloc(sizeof(char)*(MAX_STR_LEN + 1));
//  while(fgets(query, (MAX_STR_LEN + 1), stdin) != NULL){
//      query[strlen(query) - 1] = '\0';
////        printf("Searching for: %s\n", query);
//      queryPoint = convertStringToPoint(query, strlen(query));
//
//      //print result header
//      fprintf(outFile, "%s\n ", query);
//      printf("%s -->", query);
//
//      //search point and return a list of value
//      datalist_t *result  = searchPoint(root, queryPoint);
//      datapoint_t *curr;
//      curr = result->head;
//      while(curr){
//          fPrintStructure(curr->footpath, outFile);
//          curr = curr->next;
//      }
//      printf("\n");
//  }


//  fclose(outFile);
//  freeRectangle(initial_region);
//  free(query);
//  freeTree(root);


    return(EXIT_SUCCESS);
}
