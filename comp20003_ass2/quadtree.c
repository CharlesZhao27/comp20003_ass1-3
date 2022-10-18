//
// Created by Weibo on 9/9/2022.
//

#include "quadtree.h"
#include "struct.h"
#include <assert.h>



//add a point into the quadtree
treeNode_t *addPoint(struct quadTreeNode *rootPtr, datapoint_t *data){

    int quadrant;

    assert(rootPtr);
    if(rootPtr->status == LEAF){
        //Leaf node: directly insert and update

        //create list for the dataList and insert dataList into list
        rootPtr->key = malloc(sizeof(datalist_t));
        assert(rootPtr->key);
        rootPtr->key->head =  rootPtr->key->foot = NULL;
        rootPtr->key = insertAtFoot(rootPtr->key, data);

        //update status to filled node now and finish insertion
        rootPtr->status = FILLED;
        return rootPtr;
    }else if(rootPtr->status == INTERNAL){
        //Internal node: No data insertion, goes to it's child node

        //determine quadrant
        quadrant = determineQuadrant(data->location, rootPtr->region);
        
        //goes to its child node by given quadrant
        if(quadrant == SW){
            rootPtr->sw = addPoint(rootPtr->sw, data);
        }else if(quadrant == NW){
            rootPtr->nw = addPoint(rootPtr->nw, data);
        }else if(quadrant == NE){
            rootPtr->ne = addPoint(rootPtr->ne, data);
        }else if(quadrant == SE){
            rootPtr->se = addPoint(rootPtr->se, data);
        }
    } else if(rootPtr->status == FILLED){
        //Filled Node: we have multiple case

        if(compare_point(data->location,rootPtr->key->head->location) == 1){
            //Two point are same, and we can add new point into the datalist
            rootPtr->key = insertAtFoot(rootPtr->key, data);
            return rootPtr;
        }else{
            //Two point are not same, and we switch this node to `Internal` node
            rootPtr = initialChildNode(rootPtr);

            //re-insert the datapoint to this rootPtr
            quadrant = determineQuadrant(rootPtr->key->head->location, rootPtr->region);
            if(quadrant == SW){
                rootPtr->sw = addPoint(rootPtr->sw, rootPtr->key->head);
            }else if(quadrant == NW){
                rootPtr->nw = addPoint(rootPtr->nw, rootPtr->key->head);
            }else if(quadrant == NE){
                rootPtr->ne = addPoint(rootPtr->ne, rootPtr->key->head);
            }else if(quadrant == SE){
                rootPtr->se = addPoint(rootPtr->se, rootPtr->key->head);
            }
            //remove the content in the rootPtr
            free(rootPtr->key);
            //add new datapoint into the rootPtr
            addPoint(rootPtr, data);
        }
    }
    return rootPtr;
}



//select a pointer to corresponding child node by given quadrant number
//treeNode_t *enumerateQuadrant(struct quadTreeNode *curr, int quadrant){
//
//  if(curr->status != 1){
//      exit(EXIT_FAILURE);
//  }
//
//  if(quadrant == SW){
//      return curr->sw;
//  }else if(quadrant == NW){
//      return curr->nw;
//  }else if(quadrant == NE){
//      return curr->ne;
//  }else if(quadrant == SE){
//      return curr->se;
//  }
//  
//}


treeNode_t *buildTreeNode(rectangle_t *region){

    treeNode_t *node;
    node = malloc(sizeof(treeNode_t));
    assert(node);

    node->sw = NULL;
    node->nw = NULL;
    node->ne = NULL;
    node->se = NULL;
    node->status = 0; //Leaf node when we initialize it
    node->key = NULL;
    node->region = region;

    return node;
}

treeNode_t *initialChildNode(treeNode_t * node){

    //find the center of the rectangle
    long double xMid, yMid;
    xMid = 0.5 *(node->region->top_right->x + node->region->bot_left->x);
    yMid = 0.5 *(node->region->top_right->y + node->region->bot_left->y);
    
    //find four quadrant and sub rectangle for this quadrant
    point_t *temp1, *temp2;
    rectangle_t *region_nw, *region_sw, *region_ne, *region_se;
    temp1 = buildPoint(node->region->bot_left->x, yMid);
    temp2 = buildPoint(xMid, node->region->top_right->y);
    region_nw = createRectangle(temp1, temp2);

    temp2 = buildPoint(xMid, yMid);
    region_sw = createRectangle(node->region->bot_left, temp2);

    temp1 = buildPoint(xMid, yMid);
    region_ne = createRectangle(temp1, node->region->top_right);

    temp1 = buildPoint(xMid,node->region->bot_left->y);
    temp2 = buildPoint(node->region->top_right->x, yMid);
    region_se = createRectangle(temp1, temp2);

    //malloc four node
    node->sw = buildTreeNode(region_sw);
    node->nw = buildTreeNode(region_nw);
    node->ne = buildTreeNode(region_ne);
    node->se = buildTreeNode(region_se);

    //update node
    node->status = INTERNAL;

    return node;
}

void printNode(treeNode_t *node){
    if(node){
        printf("Inspecting for status: %d\n", node->status);
        //printRectangle(node->region);
        if(node->status == -1){
            datapoint_t *curr = node->key->head;
            while(curr){
                print_structure(curr->footpath);
                curr = curr->next;
            }
        }
    }
}


void printTree(treeNode_t *root){

    assert(root);
    printNode(root);
    if(root->status == 1){
        printTree(root->sw);
        printTree(root->nw);
        printTree(root->ne);
        printTree(root->se);
    }
}


void freeNode(treeNode_t *node){
    if(node){
        freeRectangle(node->region);
        if(node->status == -1){
            freeDataPoint(node->key->head);
        }
    }
}


void freeTree(treeNode_t *root){
    assert(root);
    if(root->status == 1){
        printTree(root->sw);
        printTree(root->nw);
        printTree(root->ne);
        printTree(root->se);
    }
    freeNode(root);
}


datalist_t *searchPoint(struct quadTreeNode *rootPtr, point_t *point){
    int quadrant;
    assert(rootPtr);
    if(rootPtr->status == -1){
        if(compare_point(rootPtr->key->head->location, point) == 1){
            return rootPtr->key;
        }
    }else if(rootPtr->status == 0){
        printf("Error Message(Search): rootPtr is an leaf node and it's empty\n");
        return NULL;
    }else{
        quadrant = determineQuadrant(point, rootPtr->region);
        if(quadrant == SW){
            printf(" SW");
            searchPoint(rootPtr->sw, point);
        }else if(quadrant == NW){
            printf(" NW");
            searchPoint(rootPtr->nw, point);
        }else if(quadrant == NE){
            printf(" NE");
            searchPoint(rootPtr->ne, point);
        }else{
            printf(" SE");
            searchPoint(rootPtr->se, point);
        }
    }
}


treeNode_t *readData(FILE *f, treeNode_t *root){

    char *buffer = malloc(sizeof(char) * MAX_LINE_LEN + 1);
    assert(buffer);

    fscanf(f, "%[^\n]\n", buffer);            // read the header file and skip the header

    while(fscanf(f, "%[^\n]\n", buffer ) == 1){
        record_t *record = processData(buffer);            //process dataList and store it into a structure
        datapoint_t *start = buildDataPoint(buildPoint(record->start_lon, record->start_lat), record);
        datapoint_t *end = buildDataPoint(buildPoint(record->end_lon, record->end_lat), record);

        root = addPoint(root, start);
        root = addPoint(root, end);

    }
    free(buffer);
    return root;
}
