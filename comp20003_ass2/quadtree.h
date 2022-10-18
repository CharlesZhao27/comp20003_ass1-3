//
// Created by Weibo on 9/9/2022.
//

#ifndef UNTITLED_QUADTREE_H
#define UNTITLED_QUADTREE_H


#include "struct.h"
#include "read.h"

#define INTERNAL 1
#define LEAF 0
#define FILLED -1



//quadtree dataStructure
typedef struct quadTreeNode treeNode_t;
struct quadTreeNode{

    //childNode of the quadTree node
    treeNode_t *sw;
    treeNode_t *nw;
    treeNode_t *ne;
    treeNode_t *se;

    int status; //status represent the type of node_t (Internal/Leaf/Filled)
    rectangle_t *region;
    datalist_t *key;

};

//build an Empty Node with its region and status is LeafNode
treeNode_t *buildTreeNode(rectangle_t *region);

void printNode(treeNode_t *node);
void printTree(treeNode_t *root);

void freeNode(treeNode_t *node);
void freeTree(treeNode_t *root);


treeNode_t *enumerateQuadrant(struct quadTreeNode *curr, int quadrant);
treeNode_t *initialChildNode(treeNode_t * node);



treeNode_t *addPoint(struct quadTreeNode *rootPtr, datapoint_t *data);




datalist_t *searchPoint(struct quadTreeNode *rootPtr, point_t *point);

treeNode_t *readData(FILE *f, treeNode_t *root);

#endif //UNTITLED_QUADTREE_H
