#include "tree.h"
#include <stdio.h>
#include <unistd.h>
#include <omp.h>


int n_dimensions;
int id = 0;

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

double* orthogonal_projection(double* a, double* b, double* p, double* b_minus_a, double inner_product_a_minus_b){

    double* pt3;

    double* p_minus_a = subtraction(p, a);

    double first_term = inner_product(p_minus_a, b_minus_a) / inner_product_a_minus_b;

    pt3 = addition(multiply_by_scalar(b_minus_a, first_term), a);

    if (pt3[0] < a[0] && pt3[0] < b[0]){
    }

    if (pt3[0] > a[0] && pt3[0] > b[0]){
    }

    return pt3;

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

#define new_max(x,y) (((x) >= (y)) ? (x) : (y))

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
    double* initial_point = pts[0];
    double* a;
    int *furthest_nodes = malloc(sizeof(int) * 2);

    for (int i = 0; i != n_points; i++){
        dist_temp = distance(initial_point, pts[i]);
        if (dist_temp > dist) {
            dist = dist_temp;
            furthest_nodes[0] = i;
            a = pts[i];
        }
    }

    dist = 0;

    for (int i = 0; i != n_points; i++){
        dist_temp = distance(a, pts[i]);
        if (dist_temp > dist) {
            dist = dist_temp;
            furthest_nodes[1] = i;
        }
    }

    return furthest_nodes;

}

int compareTo(const void *first, const void *second){

    const double (*a)[0] = first;
    const double (*b)[0] = second;
    if ( (*a)[0] < (*b)[0] ) return -1;
    if ( (*a)[0] > (*b)[0] ) return +1;
    return 0;

}

struct _projection* sortProjections(struct _projection* projections, int n_projections){

    struct _projection projection_temp;

    for (int i = 0; i < n_projections; ++i){

        for (int j = i + 1; j < n_projections; ++j){

            if (projections[i].projection[0] > projections[j].projection[0]){

                projection_temp =  projections[i];
                projections[i] = projections[j];
                projections[j] = projection_temp;

            }

        }

    }

    return projections;
}

void left_and_right_partitions(double **points, int n_points, double *center_node, double* right_partition_point, node_t* node) {

    //Não sei o tamanho destes vetores logo de início, portanto meti como n_points
    double **left_partition = create_array_pts1(n_dimensions, n_points);
    double **right_partition = create_array_pts1(n_dimensions, n_points);

    int n_left_partition = 0;
    int n_right_partition = 0;

    if (right_partition_point == NULL){
        for (int i = 0; i != n_points; i++) {
            if (points[i][0] < center_node[0]) {
                left_partition[n_left_partition] = points[i];
                n_left_partition++;
            } else {
                right_partition[n_right_partition] = points[i];
                n_right_partition++;
            }
        }
    }
    else {
        for (int i = 0; i != n_points; i++) {
            if (points[i][0] < center_node[0] && points[i][0] != right_partition_point[0]) {
                left_partition[n_left_partition] = points[i];
                n_left_partition++;
            }
            else if (points[i][0] > center_node[0] && points[i][0] != right_partition_point[0]) {
                right_partition[n_right_partition] = points[i];
                n_right_partition++;
            }
        }
        right_partition[n_right_partition] = right_partition_point;
        n_right_partition++;
    }

    if(n_points == 2 && points[0][0] == points[1][0]){
        right_partition[0] = points[0];
        n_right_partition = 1;
        left_partition[0] = points[0];
        n_left_partition = 1;
    }


    if (n_left_partition > 0 && n_right_partition == 0){
        node->R = -1;
        node->AddL = build_tree(left_partition, n_dimensions, n_left_partition, node->AddL);
        node->L = (node->AddL)->id;
        return;
    }

    else if (n_left_partition == 0 && n_right_partition > 0){
        node->L = -1;
        node->AddR = build_tree(right_partition, n_dimensions, n_right_partition, node->AddR);
        node->R = (node->AddR)->id;
        return;
    }
    else {
        int i;

        for (i = 0; i < 2; i++) {
            if (i == 0) {
                node->AddL = build_tree(left_partition, n_dimensions, n_left_partition, node->AddL);
                node->L = (node->AddL)->id;
            } else {
                node->AddR = build_tree(right_partition, n_dimensions, n_right_partition, node->AddR);
                node->R = (node->AddR)->id;
            }
        }
    }
}

struct _projection get_center_projection(struct _projection* projections, int n_projections, double* sorted_projections_x){

    struct _projection center_node;

    if (n_projections % 2 == 0){
        double center_x_1 = sorted_projections_x[(n_projections / 2) - 1];
        double center_x_2 = sorted_projections_x[n_projections / 2];
        double* center_node_1 = malloc(sizeof(double) * n_dimensions);
        double* center_node_2 = malloc(sizeof(double) * n_dimensions);
        for (int i = 0; i != n_projections; i++){
            if (projections[i].projection[0] == center_x_1){
                center_node_1 = projections[i].projection;
            }
            if (projections[i].projection[0] == center_x_2){
                center_node_2 = projections[i].projection;
            }
        }
        center_node.projection = vector_avg(center_node_1, center_node_2);
    }

    else {
        double center_x = sorted_projections_x[n_projections / 2];
        for (int i = 0; i != n_projections; i++){
            if (projections[i].projection[0] == center_x){
                center_node = projections[i];
                break;
            }
        }
    }

    return center_node;

}

node_t* build_tree(double **pts, int n_dims, long n_points, node_t* node){

    n_dimensions = n_dims;

    //if the number of points is larger than 2 we will use the normal algorithm
    if (n_points > 2){


        //Obtain furthest nodes within the given points
        int *furthest_nodes;
        furthest_nodes = get_furthest_nodes(pts, n_points);

        //Get the projections of the rest of the points
        struct _projection* projections = malloc(sizeof(struct _projection) * n_points);

        //Get Projections
        int n_projections = 0;
        double* projections_x = malloc(sizeof(double) * (n_points - 2));

        double* a = pts[furthest_nodes[1]];
        double* b = pts[furthest_nodes[0]];

        double* b_minus_a = subtraction(b, a);
        double inner_product_a_minus_b = inner_product(b_minus_a, b_minus_a);
        double* orthogonal_proj;

        for(int i = 0; i < n_points; i++) {
            if (i != furthest_nodes[0] && i != furthest_nodes[1]){

                orthogonal_proj = orthogonal_projection(pts[furthest_nodes[0]], pts[furthest_nodes[1]], pts[i], b_minus_a, inner_product_a_minus_b);
                projections_x[n_projections] = orthogonal_proj[0];
                projections[n_projections].projection = orthogonal_proj;
                projections[n_projections].point = pts[i];
                n_projections++;
            }
        }


        qsort(projections_x, n_points - 2, sizeof(double), compareTo);

        //Get center node
        struct _projection center_projection;

        //double* center_node = malloc(sizeof(double) * n_dimensions);
        if (n_projections == 1){
            center_projection = projections[0];  //The center node is going to be the only projection
        }
        else{
            center_projection = get_center_projection(projections, n_projections, projections_x);
        }

        double* point_with_center_projection = NULL;

        if (n_projections % 2 != 0) {
            point_with_center_projection = center_projection.point;
        }



        //Give the node the respective values
        node = addNewNode(-1, -1, -1, -1);
        node->id = id;
        id++;
        node->radius = new_max(distance(pts[furthest_nodes[0]], center_projection.projection), distance(pts[furthest_nodes[1]], center_projection.projection));
        node->coordinates = center_projection.projection;

        //Get Left and Right Partitions and do this function recursively
        left_and_right_partitions(pts, n_points, center_projection.projection, point_with_center_projection, node);

        return node;

    }

        //If there is only two points no projections are necessary, we only need to find the average of these two nodes to get the center node
    else if (n_points == 2){

        double* center_node = malloc (sizeof(double) * n_dims);
        center_node = vector_avg(pts[0], pts[1]);

        node = addNewNode(-1, -1, -1, -1);
        node->id = id;
        id++;
        node->radius = distance(pts[0], center_node);
        node->coordinates = center_node;

        //Get Left and Right Partitions and do this function recursively
        left_and_right_partitions(pts, n_points, center_node, NULL, node);

        return node;
    }

        //if there is only one point we just need to give the values to this node and stop the recursivity
    else if (n_points == 1){

        //printf("Only one: %f %f\n", pts[0][0], pts[0][1]);

        node = addNewNode(-1, -1, -1, -1);
        node->id = id;
        id++;
        node->coordinates = pts[0];
        node->L = -1;
        node->R = -1;
        node->radius = 0;

        return node;
    }
    return 0;
}