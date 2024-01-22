//
// Created by Giuseppe on 16/01/2024.
//
#include <stdio.h>
#include <omp.h>
#include "utils.h"

int main() {

    // Il numero dei punti e dei cluster viene chiesto all'utente
    // TODO: Automatizzare questa procedura per ottenere dei test case
    int ncores = omp_get_num_procs();
    printf("WARNING: Numero di cores disponibili %d\n",ncores);
    printf("Inserire il numero dei punti,clusters e threads\n");
    int numPoints,numClusters,nThreads;;
    scanf("%d %d %d",&numPoints,&numClusters,&nThreads);



    // Generazione di punti e clusters iniziali:
    point points[numPoints]; // Vettore dei punti
    point clusters[numClusters]; // Vettore dei clusters

    // Dichiarazione variabili relative alla misurazione dei tempi
    double start_Time = 0;
    double end_Time = 0;
    double execution_Time = 0;


    start_Time = omp_get_wtime(); // Inizio della misurazione del tempo di esecuzione
#pragma omp parallel num_threads(nThreads)
        {
#pragma omp for schedule(auto) nowait
            for (int i = 0; i < numPoints; i++) {
                points[i] = point_Initialization(i, numPoints - i);
                //points[i] = point_Initialization(i, pow(i,2));  //Per visualizzare eventualmente anche clusterID nei centroidi, qualora si volesse
            }
            // Si utilizza nowait perchè i due cicli sono indipendenti e non serve la barriera dopo il primo for
            // La schedule(auto) decide se schedulare/distribuire i valori tra i thread in modo statico o dinamico a seconda delle esigenze

#pragma omp for schedule(auto)
            for (int i = 0; i < numClusters; i++) {
                clusters[i] = point_Initialization((i * numClusters) % (numPoints + 1),
                                                   (numPoints + i * numClusters) % (numPoints - 2));
                clusters[i].clusterId = i;
            }
        }


        k_means(points, clusters, numPoints, numClusters, nThreads);


        // STAMPA DEI RISULTATI

//        printf("\nESECUZIONE DELL'ALGORITMO K-MEANS PARALLELO\n\n\n");
//        printf("Utilizzando K = %d clusters vengono definiti i seguenti punti:\n\n", numClusters);

//    for(int i = 0; i < numClusters; i++){
//        printf("\n\nCluster numero: %d\n", i);
//
//        printf("Lista dei punti associati al centroide (%f, %f):\n", clusters[i].x, clusters[i].y);
//
//#pragma omp parallel for schedule(auto) num_threads(nThreads)
//        for(int point = 0; point < numPoints; point++) {
//            if(points[point].clusterId == i){
//                printf("(%f, %f)  ", points[point].x, points[point].y);
//            }
//        }
//    }


        end_Time = omp_get_wtime(); // Misurazione del tempo finale di esecuzione
        execution_Time = end_Time - start_Time; // Tempo complessivo di esecuzione
        printf("Tempo di esecuzione dell'algoritmo: %f\n",execution_Time);//,i);

    return 0;
}


