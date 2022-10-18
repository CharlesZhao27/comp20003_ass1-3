//
// Created by Weibo on 9/9/2022.
//

#ifndef UNTITLED_STRUCT_H
#define UNTITLED_STRUCT_H

#include "read.h"

#define SW 0
#define NW 1
#define NE 2
#define SE 3
#define START 'h'
#define END 'e'
#define EPSILON 10e-13

//dataStructure for the 2D point
typedef struct location{
    long double x,y;
}point_t;

//dataStructure for a 2D rectangle, this structure include bot_left Point and top_right Point
typedef struct rectangle{
    point_t *bot_left, *top_right;
}rectangle_t;

//dataStructure for the
typedef struct dataPoint datapoint_t;
struct dataPoint{
    char status;
    point_t *location;
    record_t *footpath;
    datapoint_t *next;
};

//define a new linked list node form to store our dataList
typedef struct{
    datapoint_t *head;
    datapoint_t *foot;
}datalist_t;


//build an empty location point, 2D rectangle, and treeKey
point_t *buildPoint(long double x1, long double x2);
rectangle_t *createRectangle(point_t *bot_left, point_t *top_right);
datapoint_t *buildDataPoint(point_t *location, record_t *footpath);

void printPoint(point_t *point);
void printRectangle(rectangle_t *rectangle);
void printDataPoint(struct dataPoint *key);

//Three different free function for the different Data Structure
void freePoint(point_t *point);
void freeRectangle(rectangle_t *rectangle);
void freeDataPoint(struct dataPoint *key);


//helper function for search_tree, compare two point and return 1(TRUE) if two point are equivalent
int compare_point(point_t *point1, point_t *point2);

int inRectangle(point_t *point, rectangle_t *rectangle);
int determineQuadrant(point_t *point, rectangle_t *rectangle);

datalist_t *insertAtFoot(datalist_t *dataList, datapoint_t *new);

point_t *convertStringToPoint(char *buffer, int bufferSize);




#endif //UNTITLED_STRUCT_H
