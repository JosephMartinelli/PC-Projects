//
// Created by Giuseppe on 15/01/2024.
//
#include <stdio.h>
#include <omp.h>
#include "utils.h"
#define EXEC_N 10 // Numero di esecuzioni da fare data una configurazione




int main() {

    // Il numero dei punti e dei cluster viene chiesto all'utente
    // TODO: Automatizzare questa procedura per ottenere dei test case
    printf("WARNING: Numero di cores disponibili %d\n",omp_get_num_procs());
    printf("Inserire il numero dei punti e dei clusters\n");
    int numPoints,numClusters;
    scanf("%d %d",&numPoints,&numClusters);


    point points[numPoints]; // Vettore dei punti
    point clusters[numClusters]; // Vettore dei clusters
    double exec_times[EXEC_N] = {0}; // Vettore del tempo di ogni esecuzione
    // Il vettore sopra si salva così si può vedere nello specifico ogni esecuzione

    // Dichiarazione variabili relative alla misurazione dei tempi
    double start_Time = 0;
    double end_Time = 0;
    double execution_Time = 0;

    for(int i = 0; i < EXEC_N; i++) {

        // Sfruttiamo omp per misurare il tempo
        start_Time = omp_get_wtime();

        // Generazione di punti e clusters iniziali:
        for (int i = 0; i < numPoints; i++) {
            points[i] = point_init(i, numPoints - i);
        }

        for (int i = 0; i < numClusters; i++) {
            clusters[i] = point_init((i * numClusters) % (numPoints + 1),
                                     (numPoints + (i * numClusters)) % (numPoints - 2));
            clusters[i].clusterId = i;
        }


        // Esecuzione algoritmo
        k_means(points, clusters, numPoints, numClusters);


        // Stampa risultati

        //printf("\nESECUZIONE DELL'ALGORITMO K-MEANS SEQUENZIALE\n\n\n");
//    printf("Utilizzando K = %d clusters vengono definiti i seguenti punti:\n\n", numClusters);

//    for(int i = 0; i < numClusters; i++){
//        printf("\n\nCluster numero: %d\n", i);
//
//        printf("Lista dei punti associati al centroide (%f, %f):\n", clusters[i].x, clusters[i].y);
//        for(int point = 0; point < numPoints; point++) {
//            if(points[point].clusterId == i){
//                printf("(%f, %f)  ", points[point].x, points[point].y);
//            }
//        }
//    }


        end_Time = omp_get_wtime(); // Misurazione del tempo finale di esecuzione
        execution_Time = end_Time - start_Time; // Tempo complessivo di esecuzione
        exec_times[i] = execution_Time;
        printf("Tempo di esecuzione dell'algoritmo: %f, Esecuzione n: %d\n", execution_Time,i);
    }

    double sum = 0;
    // Calcolo tempo medio
    for(int i = 0; i < EXEC_N; i++)
        sum += exec_times[i];
    printf("Tempo Medio ottenuto: %lf",sum / EXEC_N);
    return 0;

}


