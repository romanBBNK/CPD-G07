#include <omp.h>
#include <stdio.h>
#include "../Common/gen_points.c"
#include "tree.h"

int main(int argc, char *argv[])
{
    double exec_time;
    exec_time = -omp_get_wtime();
    int n_dims;
    long n_points;

    double **pts = get_points(argc, argv, &n_dims, &n_points);
    node_t* root = build_tree(pts, n_dims, n_points);

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1lf\n", exec_time);
    dump_tree(root);
    return 0;
}


