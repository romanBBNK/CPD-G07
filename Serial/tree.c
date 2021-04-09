#include "tree.h"
#include <stdio.h>
#include <unistd.h>

int n_dimensions;

double distance(double *pt1, double *pt2)
{
    double dist = 0.0;

    for(int d = 0; d < n_dimensions; d++){
        dist += (pt1[d] - pt2[d]) * (pt1[d] - pt2[d]);
    }

    return sqrt(dist);
}

double **create_array_pts1(int n_dims, long np)
{
    double *_p_arr;
    double **p_arr;

    _p_arr = (double *) malloc(n_dims * np * sizeof(double));
    p_arr = (double **) malloc(np * sizeof(double *));
    if((_p_arr == NULL) || (p_arr == NULL)){
        printf("Error allocating array of points, exiting.\n");
        exit(4);
    }

    for(long i = 0; i < np; i++)
        p_arr[i] = &_p_arr[i * n_dims];

    return p_arr;
}

int compareTo(const void *first, const void *second){

    const double (*a)[0] = first;
    const double (*b)[0] = second;
    if ( (*a)[0] < (*b)[0] ) return -1;
    if ( (*a)[0] > (*b)[0] ) return +1;
    return 0;

}

double inner_product(double* pt1, double* pt2){

    double sum = 0.0;

    for (int i = 0; i != n_dimensions; i++){
        sum += pt1[i] * pt2[i];
    }

    return sum;

}

double* subtraction(double* pt1, double* pt2){

    double* pt3 = malloc(n_dimensions * sizeof(double));

    for (int i = 0; i != n_dimensions; i++){
        pt3[i] = pt1[i] - pt2[i];
    }

    return pt3;

}

double* addition(double* pt1, double* pt2){

    double* pt3 = malloc(n_dimensions * sizeof(double));

    for (int i = 0; i != n_dimensions; i++){
        pt3[i] = pt1[i] + pt2[i];
    }

    return pt3;

}

double* multiply_by_scalar(double* pt1, double scalar){

    double* pt3 = malloc(n_dimensions * sizeof(double));

    for (int i = 0; i != n_dimensions; i++){
        pt3[i] = pt1[i] * scalar;
    }

    return pt3;

}

double* orthogonal_projection(double* a, double* b, double* p){

    double* pt3 = malloc(n_dimensions * sizeof(double));

    double* p_minus_a = subtraction(p, a);
    double* b_minus_a = subtraction(b, a);

    double first_term = inner_product(p_minus_a, b_minus_a) / inner_product(b_minus_a, b_minus_a);

    pt3 = addition(multiply_by_scalar(b_minus_a, first_term), a);

    return pt3;

}


/*void dump_tree(struct _node* node, int n_dimensions){

    printf("%ld %ld %ld %ld ", node->id, node->L, node->R, node->radius);
    for (int i = 0; i != n_dimensions; i++){
        printf("%f ", node->coordinates[i]);
    }
    printf("\n");

    if (node->L != -1){
        dump_tree(node->AddL, n_dimensions);
    }
    if (node->R != -1){
        dump_tree(node->AddR, n_dimensions);
    }

}*/

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

double* vector_avg(double* p1, double* p2){

    double* p3 = malloc(sizeof(double) * n_dimensions);

    for (int i = 0; i != n_dimensions; i++){
        p3[i] = (p1[i] + p2[i]) / 2;
    }
    return p3;

}

double* get_furthest_nodes(double **pts, int n_points){

    double dist = 0;
    double dist_temp;
    int *furthest_nodes = malloc(sizeof(int) * 2);

    for(int i = 0; i < n_points; i++) {
        for (int j = 0; j < n_points; j++) {
            if (i != j){
                dist_temp = distance(pts[i], pts[j]);
                if (dist_temp > dist){
                    dist = dist_temp;
                    furthest_nodes[0] = i;
                    furthest_nodes[1] = j;
                }
            }
        }
    }
    return furthest_nodes;

}

double** get_projections(int *furthest_nodes, double** pts, int n_points){

    int n_projections = 0;
    double** projections = create_array_pts1(n_dimensions, n_points - 2);

    int furthest_node_1 = furthest_nodes[0];
    int furthest_node_2 = furthest_nodes[1];

    for(int i = 0; i < n_points; i++) {
        if (i != furthest_node_1 && i != furthest_node_2){

            projections[n_projections] = orthogonal_projection(pts[furthest_node_1], pts[furthest_node_2], pts[i]);
            n_projections++;
        }
    }

    //printf("\n\nValues: %d %d %d\n\n ", furthest_node_1, furthest_node_2, n_points);
    //printf("\n\n");

    return projections;

}

double** sort(double** array1, int n_points){

    double *array_x = malloc (n_points * sizeof(double));

    for(int i = 0; i != n_points; i++){

        array_x[i] = array1[i][0];

    }

    qsort(array_x, n_points, sizeof(double), compareTo);
    double** sorted_array = create_array_pts1(n_dimensions, n_points);

    //FAZER QSORT DA LISTA PROJECTIONS EM VEZ DE ESTAR A FAZER ESTA TROCA
    for (int i = 0; i != n_points; i++){
        for (int j = 0; j != n_points; j++){
            if (array_x[i] == array1[j][0]){
                sorted_array[i] = array1[j];
            }
        }
    }

    return sorted_array;

}

void left_and_right_partitions(double **sorted_points, int n_points, double *center_node, node_t* node) {

    //Não sei o tamanho destes vetores logo de início, portanto meti como n_points
    double **left_partition = create_array_pts1(n_dimensions, n_points);
    double **right_partition = create_array_pts1(n_dimensions, n_points);

    int n_left_partition = 0;
    int n_right_partition = 0;

    for (int i = 0; i != n_points; i++) {
        if (sorted_points[i][0] < center_node[0]) {
            left_partition[n_left_partition] = sorted_points[i];
            n_left_partition++;
        } else {
            right_partition[n_right_partition] = sorted_points[i];
            n_right_partition++;
        }
    }

    for (int i = 0; i != n_left_partition; i++) {
        printf("Left partition: %f %f\n", left_partition[i][0], left_partition[i][1]);
    }
    printf("\n\n");

    for (int i = 0; i != n_right_partition; i++) {
        printf("Right partition: %f %f\n", right_partition[i][0], right_partition[i][1]);
    }

    if (n_left_partition > 0 && n_right_partition == 0){
        printf("\n\n\n ---------LeftPartition---------\n");
        node->AddL = build_tree(left_partition, n_dimensions, n_left_partition, node->AddL);
        return;
    }

    else if (n_left_partition == 0 && n_right_partition > 0){
        printf("\n\n\n ---------RightPartition---------\n");
        node->AddR = build_tree(right_partition, n_dimensions, n_right_partition, node->AddR);
        return;
    }
    else {
        printf("\n\n\n ---------RightPartition---------\n");
        node->AddR = build_tree(right_partition, n_dimensions, n_right_partition, node->AddR);
        printf("\n\n\n ---------LeftPartition---------\n");
        node->AddL = build_tree(left_partition, n_dimensions, n_left_partition, node->AddL);

    }
}

double* get_center_node(double** sorted_projections, int n_projections){

    double* center_node = malloc (sizeof(double) * n_dimensions);

    if (n_projections % 2 == 0){
        center_node = vector_avg(sorted_projections[(n_projections / 2) - 1], sorted_projections[(n_projections / 2)]);
    }

    else {
        int center_node_ID = round(n_projections / 2);
        center_node = sorted_projections[center_node_ID];
    }

    return center_node;

}

node_t* build_tree(double **pts, int n_dims, long n_points, node_t* node){
    //sleep(3);

    n_dimensions = n_dims;

    printf("N_Dims: %d \n", n_dims);
    printf("N_Points: %d\n", n_points);

    int i;
    int j;

    //Obtain furthest nodes within the given points
    int *furthest_nodes = malloc (sizeof(int) * 2);
    furthest_nodes = get_furthest_nodes(pts, n_points);

    printf("Furthest nodes: %d %d\n", furthest_nodes[0], furthest_nodes[1]);

    //if the number of points is larger than 2 we will use the normal algorithm
    if (n_points > 2){

        //Sort points according to their Xs
        double** sorted_points = create_array_pts1(n_dimensions, n_points);
        sorted_points = sort(pts, n_points);

        for (int i = 0; i != n_points; i++){
            printf("Sorted points: %f %f\n", sorted_points[i][0], sorted_points[i][1]);
        }
        printf("\n\n");

        //Get the projections of the rest of the points
        double** projections = create_array_pts1(n_dimensions, n_points - 2);
        projections = get_projections(furthest_nodes, pts, n_points);
        int n_projections = n_points - 2; //This is because the two furthest points are the only ones without a projection

        //Sort projections according to their Xs
        double** sorted_projections = create_array_pts1(n_dimensions, n_points - 2);
        sorted_projections = sort(projections, n_points - 2);

        for (int i = 0; i != n_points - 2; i++){
            printf("Projetions: %f %f \n", sorted_projections[i][0], sorted_projections[i][1]);
        }
        printf("\n\n");

        //Get center node
        double* center_node = malloc(sizeof(double) * n_dimensions);
        if (n_projections == 1){
            center_node = sorted_projections[0];  //The center node is going to only projection
        }
        else{
            center_node = get_center_node(sorted_projections, n_projections);
        }

        printf("Center node: %f %f\n", center_node[0], center_node[1]);

        //Give the node the respective values
        node = addNewNode(1, 0, 1, 2);
        node->coordinates = malloc(sizeof(double) * n_dims);
        for (int i = 0; i != n_dims; i++){
            node->coordinates[i] = center_node[i];
        }

        //Get Left and Right Partitions and do this function recursively
        left_and_right_partitions(sorted_points, n_points, center_node, node);

        return node;

    }

    //If there is only two points no projections are necessary, we only need to find the average of these two nodes to get the center node
    else if (n_points == 2){

        for (int i = 0; i != n_points; i++){
            printf("Points: %f %f\n", pts[i][0], pts[i][1]);
        }
        printf("\n\n");

        double* center_node = malloc (sizeof(double) * n_dims);
        center_node = vector_avg(pts[furthest_nodes[0]], pts[furthest_nodes[1]]);

        printf("Center node: %f %f\n", center_node[0], center_node[1]);

        node = addNewNode(6, 0, 1, 2);
        node->coordinates = malloc(sizeof(double) * n_dims);
        for (int i = 0; i != n_dims; i++){
            node->coordinates[i] = center_node[i];
        }

        //Get Left and Right Partitions and do this function recursively
        left_and_right_partitions(pts, n_points, center_node, node);

        return node;
    }

    //if there is only one point we just need to give the values to this node and stop the recursivity
    else if (n_points == 1){

        printf("Only one: %f %f\n", pts[0][0], pts[0][1]);

        node = addNewNode(6, 0, -1, -1);
        node->coordinates = malloc(sizeof(double) * n_dims);
        for (int i = 0; i != n_dims; i++){
            node->coordinates[i] = pts[0][i];
        }

        return node;
    }

    return 0;
}