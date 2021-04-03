#ifndef CPD_G07_TREE_H
#define CPD_G07_TREE_H

typedef struct _node {
    double radius;
    long id;
    long L;
    long R;
    struct _node* AddL;
    struct _node* AddR;
} node_t;

node_t* build_tree(double **pts, int n_dims, long n_points);

int dump_tree(int root);

node_t* addNewNode(double radius, long id, long L, long R);

#endif //CPD_G07_TREE_H
