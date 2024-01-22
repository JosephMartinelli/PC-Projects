//
// Created by Giuseppe on 15/01/2024.
//
#include "utils.h"
#include "math.h"

point point_init(float x, float y){
    point p = {x, y, -1};
    return p;
}


void k_means(point points[], point clusters[],int numPoints,int numClusters){
    int centroidIndex = 0; // Valore del centroide più vicinio al punto attuale (si usa per la selezione del cluster)
    float newX;
    float newY;
    int numPointsOfCluster = 0;
    int convergence = 0;

    while(convergence == 0)
    {

        // Caso migliore, convergiamo subito
        convergence = 1;

        // Calcolo del cluster di appartenenza per ciascuno dei punti a disposizione
        for (int i = 0; i < numPoints; i++) {
            centroidIndex = nearestCenter(points[i], clusters,numClusters);
            points[i].clusterId = centroidIndex; // Il punto "i" viene associato al cluster "centroidIndex"
        }


        // Aggiornamento delle coordinate dei centroidi
        for(int centroid = 0; centroid < numClusters; centroid++)
        {
            newX = 0;
            newY = 0;
            numPointsOfCluster = 0;

            // Prendiamo tutti i punti appartenenti a quel centroide
            for(int i = 0; i < numPoints; i++)
            {
                if(points[i].clusterId == centroid){
                    newX = newX + points[i].x;
                    newY = newY + points[i].y;
                    numPointsOfCluster++;
                }

            }
            // Se ci sono dei nuovi punti nel cluster, allora ci sarà un cambiamento di centroide
            if(numPointsOfCluster != 0){
                newX = newX / numPointsOfCluster;
                newY = newY / numPointsOfCluster;
            }
            // Caso in cui il centroide non è cambiato
            else{
                newX = clusters[centroid].x;
                newY = clusters[centroid].y;
            }
            // Verifica se c'è stato un effettivo cambiamento di centroide, se c'è stato allora l'algoritmo non è arrivato
            // alla convergenza
            if(newX != clusters[centroid].x || newY != clusters[centroid].y){
                clusters[centroid].x = newX;
                clusters[centroid].y = newY;
                convergence = 0;
            }
        }

    }


}

int euclideanDistance(point a, point b){
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

int nearestCenter(point actualPoint, point clusters[],int numClusters){
    double distance;
    int centroidIndex = 0;

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
