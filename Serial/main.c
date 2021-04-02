#include <omp.h>


int main(int argc, char *argv[])
{
    double exec_time;
    exec_time = -omp_get_wtime();
    int n_dims = argv[1];
    int n_points = argv[2];
    int gen_seed = argv[3];

    pts = get_points(argc, argv, &n_dims, &n_points);
    root = build_tree();

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1lf\n", exec_time);
    dump_tree(root);
    return 0;
}


