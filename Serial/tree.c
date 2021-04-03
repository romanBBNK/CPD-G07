#include "tree.h"
#include <stdio.h>

node_t* build_tree(double **pts, int n_dims, long n_points){

    node_t* root = addNewNode(1, 0, 1, 2);
    node_t* left = addNewNode(1, 1, 3, 4);
    root->AddL=left;

    return 0;
}

int dump_tree(int root){
    printf("Tree: %d\n", root);
    return 0;
}

node_t* addNewNode(double radius, long id, long L, long R){
    node_t* newNode = (node_t*) malloc(sizeof(node_t));

    newNode->radius = radius;
    newNode->id = id;
    newNode->L;
    newNode->R;
    newNode->AddL = NULL;
    newNode->AddR = NULL;

    return newNode;
}