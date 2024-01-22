//
// Created by Giuseppe on 15/01/2024.
//
#ifndef PARALLEL_K_MEANS_UTILS_H
#define PARALLEL_K_MEANS_UTILS_H

typedef struct{
    float x;
    float y;
    int clusterId;
}point;


point point_init(float x, float y);
void k_means(point points[], point clustesr[],int numPoints,int numClusters);
int euclideanDistance(point a, point b);
int nearestCenter(point actualPoint, point clusters[],int numClusters);



#endif //PARALLEL_K_MEANS_UTILS_H
