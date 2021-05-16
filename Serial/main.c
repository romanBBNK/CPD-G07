#include <omp.h>
#include <stdio.h>
#include "../Common/gen_points.c"
#include "tree.h"


void dump_tree(struct _node* node, int n_dimensions){

    printf("%ld %ld %ld %f ", node->id, node->L, node->R, node->radius);
    for (int i = 0; i != n_dimensions; i++){
        printf("%f ", node->coordinates[i]);
    }
    printf("\n");

    if (node->AddL != NULL){
        dump_tree(node->AddL, n_dimensions);
    }
    if (node->AddR != NULL){
        dump_tree(node->AddR, n_dimensions);
    }

}

int main(int argc, char *argv[])
{
    double exec_time;
    exec_time = -omp_get_wtime();
    int n_dims;
    long n_points;

    double **pts = get_points(argc, argv, &n_dims, &n_points);

    int* partition_indices = (int*) malloc(sizeof(int) * n_points);
    for (int i = 0; i != n_points; i++){
        partition_indices[i] = i;
    }

    node_t* root;
    root = build_tree(pts, partition_indices, n_dims, n_points, root);

    exec_time += omp_get_wtime();
    printf("%d %d\n", n_dims, getID());
    dump_tree(root, n_dims);
    fprintf(stderr, "%.1lf\n", exec_time);
    cleanMemory(pts, root, n_points);
    return 0;
}


