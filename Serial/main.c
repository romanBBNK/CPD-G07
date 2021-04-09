#include <omp.h>
#include <stdio.h>
#include "../Common/gen_points.c"
#include "tree.h"

void dump_tree(struct _node* node, int n_dimensions){

    printf("%ld %ld %ld %ld ", node->id, node->L, node->R, node->radius);
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

    /*pts[0][0] = 3.4;
    pts[0][1] = 7.7;
    pts[1][0] = 7.8;
    pts[1][1] = 8.0;
    pts[2][0] = 2.8;
    pts[2][1] = 5.5;
    pts[3][0] = 9.1;
    pts[3][1] = 2.0;
    pts[4][0] = 8.4;
    pts[4][1] = 3.9;*/


    //printf("N_Dims: %d ", n_dims);
    //printf("N_Points: %d\n", n_points);
    node_t* root;
    root = build_tree(pts, n_dims, n_points, root);

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1lf\n", exec_time);
    dump_tree(root, n_dims);
    return 0;
}


