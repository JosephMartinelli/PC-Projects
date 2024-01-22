//
// Created by Giuseppe on 16/01/2024.
//


typedef struct{
    float x;
    float y;
    int clusterId;
}point;


point point_Initialization(float x, float y);
void k_means(point points[], point clustesr[],int numPoints,int numClusters,int nThreads);
int euclideanDistance(point a, point b);
int nearestCentroid(point actualPoint, point clusters[],int numClusters);
