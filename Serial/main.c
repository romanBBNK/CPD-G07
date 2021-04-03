#include <omp.h>
#include <stdio.h>
#include "../Common/gen_points.c"
#include "tree.h"

int main(int argc, char *argv[])
{
    double exec_time;
    exec_time = -omp_get_wtime();
    int n_dims;
    int n_points;
    int gen_seed;

    double **pts = get_points(argc, argv, &n_dims, &n_points);
    int root = build_tree();

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1lf\n", exec_time);
    dump_tree(root);
    return 0;
}


