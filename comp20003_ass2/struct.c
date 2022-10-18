//
// Created by Weibo on 9/9/2022.
//

#include "struct.h"
#include <assert.h>
#include <math.h>


//build an empty location point
point_t *buildPoint(long double x1, long double x2){

    //initial and allocate space for the location point
    point_t *newPoint;
    newPoint = malloc(sizeof(point_t));
    assert(newPoint);

    //assign Value to the point
    newPoint->x = x1;
    newPoint->y = x2;

    return newPoint;
}


rectangle_t *createRectangle(point_t *bot_left, point_t *top_right){

    //initial and allocate space for the rectangle
    rectangle_t *region;
    region = malloc(sizeof(rectangle_t));
    assert(region);

    //assign Value to the region
    region->bot_left = bot_left;
    region->top_right = top_right;

    return region;
}

datapoint_t *buildDataPoint(point_t *location, record_t *footpath){

    struct dataPoint *key;
    key = malloc(sizeof(datapoint_t));
    assert(key);
    key->location = location;
    key->footpath = footpath;
    if(footpath->start_lon == location->x){
        key->status = START;
    }else{
        key->status = END;
    }

    key->next = NULL;
    return key;
}


//helper function for search_tree, compare two point and return 1(TRUE) if two point are equivalent
//TODO: Use EPSILON instead, significant number be 13~14, Equal not Work in searchPoint
int compare_point(point_t *point1, point_t *point2){
    if(fabsl(point1->x - point2->x) < EPSILON && fabsl(point1->y - point2->y) <EPSILON){
        return(1);
    }else return(0);

//    if(point1->x == point2->x && point1->y == point2->y) return(1);
//    return(0);
}


//determine a point in the rectangle or not, return 1(TRUE) if it does
// the lower boundary and right boundary
int inRectangle(point_t *point, rectangle_t *rectangle){

    int status = 0;
    //check horizontally position,does the point located in the rectangle or on right bound
    if (point->x <= rectangle->top_right->x && point->x > rectangle->bot_left->x
        && point->y >= rectangle->bot_left->y && point->y < rectangle->top_right->y)
        status = 1;

    return(status);
}



//determine the quadrant of a point inthe rectangle
int determineQuadrant(point_t *point, rectangle_t *rectangle){

    //determine inRectangle or Not
    int quadrant = -1;
    if(!inRectangle(point, rectangle)){
        printf("it's not in the boundary, force quit the insertion\n");
        return(EXIT_FAILURE);
    }

    //calculate the Center point
    long double xMid, yMid;
    xMid = 0.5 *(rectangle->top_right->x + rectangle->bot_left->x);
    yMid = 0.5 *(rectangle->top_right->y + rectangle->bot_left->y);

    //determine quadrant
    if (point->x <= xMid && point->y < yMid){
        quadrant = SW;
    } else if(point->x <= xMid && point->y >= yMid){
        quadrant = NW;
    } else if(point->x > xMid && point->y >= yMid){
        quadrant = NE;
    } else if(point->x > xMid && point->y < yMid){
        quadrant = SE;
    }
    return(quadrant);
}




//helper function to free the point/rectangle/datapoint DataStructure
void freePoint(point_t *point){
    assert(point);
    free(point);
}

void freeRectangle(rectangle_t *rectangle){
    assert(rectangle);
    freePoint(rectangle->bot_left);
    freePoint(rectangle->top_right);
    free(rectangle);
}

void freeDataPoint(struct dataPoint *key){
    freePoint(key->location);
    //free footpath and double free
    if(key->status == START){
        //free footpath
        free_data(key->footpath);
    }
}


datalist_t *insertAtFoot(datalist_t *dataList, datapoint_t *new){


    //check if the list is empty and insert the new node to head and foot
    if(dataList->head == NULL){
        dataList->head = dataList->foot = new;
        new->next = NULL;
        return dataList;
    }

    //initial two node curr and prev for sort
    datapoint_t *curr = dataList->head;
    datapoint_t *prev = NULL;

    //Loop through the list and find the position to insert
    while(curr){
        //compare the current node and the new node
        if(curr->footpath->footpath_id == new->footpath->footpath_id){
            //same footpath_id, thus we don't insert into the list
            return dataList;
        }

        if(curr->footpath->footpath_id > new->footpath->footpath_id){
            //we need to insert this node before curr and after prev
            new->next = curr;
            if(prev) prev->next = new;
            else dataList->head = new;
            break;
        }

        prev = curr;
        curr = curr->next;
    }
    //we finish the run and curr is the last point of the linked-list
    if(curr == NULL){
        dataList->foot->next = new;
        new->next = NULL;
        dataList->foot = new;
    }

//    if(dataList->foot == NULL){
//        dataList->head = dataList->foot = new;
//    }else{
//        dataList->foot->next = new;
//        dataList->foot = new;
//    }
//    return dataList;
}

point_t *convertStringToPoint(char *buffer, int bufferSize){
    double x1, x2;
    int i, j = 0, flag;
    char *ptr, temp1[MAX_STR_LEN + 1], temp2[MAX_STR_LEN + 1];

    //find whitespace or newline character in the buffer
    for(i = 0; i<bufferSize; i++){
        if(buffer[i] == '\n' || buffer[i] == ' '){
            flag = i;
        }
    }

    //slice first half string for the long double x1
    for(i = 0; i<flag; i++){
        temp1[i] = buffer[i];
    }
    temp1[i] = '\0';
    x1 = strtod(temp1, &ptr);

    //slice for the second half for the long double x2
    for(i = flag; i<bufferSize;i++){
        temp2[j] = buffer[i];
        j++;
    }
    temp2[j] = '\0';
    x2 = strtod(temp2, &ptr);

    //build point and return value
    point_t *queryNode;
    queryNode = buildPoint(x1, x2);
    return  queryNode;
}

void printPoint(point_t *point){
    assert(point);
    printf("value in this point is (%Lf, %Lf)\n", point->x, point->y);
}

void printRectangle(rectangle_t *rectangle){
    assert(rectangle);
    printf("Now we are printing the rectangle in order of: bot_left & top_right");
    printPoint(rectangle->bot_left);
    printPoint(rectangle->top_right);
}

void printDataPoint(struct dataPoint *key){
    assert(key);
    printPoint(key->location);
    print_structure(key->footpath);
    while(key->next){
        printf("we are now process to the next point in the key");
        printDataPoint(key->next);
    }
}

