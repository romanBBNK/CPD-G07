#ifndef CPD_G07_TREE_H
#define CPD_G07_TREE_H

typedef struct _node {
    double radius;
    long id;
    long L;
    long R;
    double* coordinates;
    struct _node* AddL;
    struct _node* AddR;
} node_t;

typedef struct _projection {
    double* projection;
    double* point;
};

node_t* build_tree(double **pts, int n_dims, long n_points, node_t* node);

node_t* addNewNode(double radius, long id, long L, long R);



#endif //CPD_G07_TREE_H
