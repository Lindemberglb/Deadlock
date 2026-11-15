#include <stdio.h>
#include <stdlib.h>
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

static int estado_seguro(void){
    int *trabalho = criar_vetor(NUMBER_OF_RESOURCES);
    int *terminou = criar_vetor(NUMBER_OF_CUSTOMERS);
    int finalizados = 0;
    int progresso;
    int i, j;

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        trabalho[j] = available[j];
    }

    do {
        progresso = 0;

        for (i = 0; i < NUMBER_OF_CUSTOMERS; i++){
            if (!terminou[i] && menor_ou_igual(need[i], trabalho)){
                for (j = 0; j < NUMBER_OF_RESOURCES; j++){
                    trabalho[j] += allocation[i][j];
                }
                terminou[i] = 1;
                finalizados++;
                progresso = 1;
            }
        }
    } while (progresso);

    free(trabalho);
    free(terminou);

    return finalizados == NUMBER_OF_CUSTOMERS;
}

int request_resources(int customer_num, int request[]){
    int j;

    if (!menor_ou_igual(request, need[customer_num])){
        fprintf(arquivo_resultado, "The customer %d request ", customer_num);
        escrever_vetor(request);
        fprintf(arquivo_resultado, " was denied because exceed its maximum allocation\n");
        return -1;
    }

    if (!menor_ou_igual(request, available)){
        fprintf(arquivo_resultado, "The resources ");
        escrever_vetor(available);
        fprintf(arquivo_resultado, " are not enough to customer %d request ", customer_num);
        escrever_vetor(request);
        fprintf(arquivo_resultado, " \n");
        return -1;
    }

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        available[j] -= request[j];
        allocation[customer_num][j] += request[j];
        need[customer_num][j] -= request[j];
    }

    if (!estado_seguro()){
        for (j = 0; j < NUMBER_OF_RESOURCES; j++){
            available[j] += request[j];
            allocation[customer_num][j] -= request[j];
            need[customer_num][j] += request[j];
        }

        fprintf(arquivo_resultado, "The customer %d request ", customer_num);
        escrever_vetor(request);
        fprintf(arquivo_resultado, " was denied because result in an unsafe state\n");
        return -1;
    }

    fprintf(arquivo_resultado, "Allocate to customer %d the resources ", customer_num);
    escrever_vetor(request);
    fprintf(arquivo_resultado, "\n");
    return 0;
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