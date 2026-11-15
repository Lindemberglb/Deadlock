#include <stdio.h>
#include "banker.h"

static int menor_ou_igual(const int *primeiro, const int *segundo){
    int j;

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        if (primeiro[j] > segundo[j]){
            return 0;
        }
    }

    return 1;
}

static void escrever_vetor(const int *vetor){
    int j;

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        if (j > 0){
            fprintf(arquivo_resultado, " ");
        }
        fprintf(arquivo_resultado, "%d", vetor[j]);
    }
}

void imprimir_estado(void){
    int i;

    fprintf(arquivo_resultado, "MAXIMUM   |   ALLOCATION  |   NEED\n");

    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++){
        escrever_vetor(maximum[i]);
        fprintf(arquivo_resultado, "     |   ");
        escrever_vetor(allocation[i]);
        fprintf(arquivo_resultado, "       |   ");
        escrever_vetor(need[i]);
        fprintf(arquivo_resultado, " \n");
    }

    fprintf(arquivo_resultado, "AVAILABLE ");
    escrever_vetor(available);
    fprintf(arquivo_resultado, " \n");
}

void release_resources(int customer_num, int release[]){
    int j;

    if (!menor_ou_igual(release, allocation[customer_num])){
        fprintf(arquivo_resultado, "The customer %d release ", customer_num);
        escrever_vetor(release);
        fprintf(arquivo_resultado, " was denied because exceed its allocation\n");
        return;
    }

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        available[j] += release[j];
        allocation[customer_num][j] -= release[j];
        need[customer_num][j] += release[j];
    }

    fprintf(arquivo_resultado, "Release from customer %d the resources ", customer_num);
    escrever_vetor(release);
    fprintf(arquivo_resultado, "\n");
}