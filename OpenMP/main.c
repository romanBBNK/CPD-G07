#include <omp.h>
#include <stdio.h>
#include "../Common/gen_points.c"
#include "tree.h"
#include <omp.h>
#define NUMITER 30

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

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    double exec_time;
    exec_time = -omp_get_wtime();
    int n_dims;
    long n_points;

    double **pts = get_points(argc, argv, &n_dims, &n_points);

    //printf("N_Dims: %d ", n_dims);
    //printf("N_Points: %d\n", n_points);
    node_t* root;
    root = build_tree(pts, n_dims, n_points, root);

    exec_time += omp_get_wtime();
   // dump_tree(root, n_dims);
    printf("Acabei\n");
    fprintf(stderr, "%.1lf\n", exec_time);
    return 0;
}


