//
// Created by Giuseppe on 16/01/2024.
//
#include "utils.h"
#include <math.h>



point point_Initialization(float x, float y){
    point p = {x, y, -1};
    return p;
}


void k_means(point points[], point clusters[],int numPoints,int numClusters,int nThreads){
    int centroidIndex = 0; // Valore del centroide più vicinio al punto attuale (si usa per la selezione del cluster)

    float newX;
    float newY;
    int numPointsOfCluster = 0;
    int convergence = 0; // Flag di verifica per la convergenza dell'algoritmo
    int iterazioni = 0;


    while(convergence == 0){ // Condizione di convergenza

        convergence = 1;


        // Calcolo del cluster di appartenenza per ciascuno dei punti a disposizione
#pragma omp parallel num_threads(nThreads)
        {
#pragma omp for schedule(auto) private(centroidIndex)
            for (int i = 0; i < numPoints; i++) { // Scansione dei punti

                centroidIndex = nearestCentroid(points[i], clusters,numClusters);

                points[i].clusterId = centroidIndex; // Il punto "i" viene associato al cluster "centroidIndex"

            }


            // Aggiornamento delle coordinate dei centroidi
#pragma omp for schedule(auto) private(newX, newY)
            for(int centroid = 0; centroid < numClusters; centroid++){
                newX = 0;
                newY = 0;
                numPointsOfCluster = 0;


                for(int i = 0; i < numPoints; i++){
                    if(points[i].clusterId == centroid){
                        newX = newX + points[i].x;
                        newY = newY + points[i].y;
                        numPointsOfCluster++;
                    }

                }

                if(numPointsOfCluster != 0){
                    newX = newX / numPointsOfCluster;
                    newY = newY / numPointsOfCluster;
                }
                else{
                    newX = clusters[centroid].x;
                    newY = clusters[centroid].y;
                }

                if(newX != clusters[centroid].x || newY != clusters[centroid].y){
                    clusters[centroid].x = newX;
                    clusters[centroid].y = newY;
                    convergence = 0;
                }
            }
        }


    }


}



int euclideanDistance(point a, point b){
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

int nearestCentroid(point actualPoint, point clusters[],int numClusters){
    double distance;
    int centroidIndex;

    // Confronto del punto col primo centroide per inizializzare la distanza minima
    double minDistance = euclideanDistance(actualPoint, clusters[0]);
    // minDistance viene usata per mantenersi la distanza minore ed individuare il cluster di
    // appartenenza di un determinato punto


    for (int centroid = 1; centroid < numClusters; centroid++) { // Scansione dei centroidi
        distance = euclideanDistance(actualPoint, clusters[centroid]); // Calcolo della distanza Euclidea

        if (distance < minDistance) {
            minDistance = distance;
            centroidIndex = centroid;
        }

    }

    return centroidIndex;
}