#include <stdlib.h>
#include "banker.h"

int NUMBER_OF_CUSTOMERS;
int NUMBER_OF_RESOURCES;
int *available;
int **maximum;
int **allocation;
int **need;
Comando *comandos;
int quantidade_comandos;

static void liberar_matriz(int **matriz, int linhas){
    int i;

    for (i = 0; i < linhas; i++){
        free(matriz[i]);
    }

    free(matriz);
}

static void liberar_memoria(void){
    int i;

    free(available);
    liberar_matriz(maximum, NUMBER_OF_CUSTOMERS);
    liberar_matriz(allocation, NUMBER_OF_CUSTOMERS);
    liberar_matriz(need, NUMBER_OF_CUSTOMERS);

    for (i = 0; i < quantidade_comandos; i++){
        free(comandos[i].recursos);
    }

    free(comandos);
}

int main(int argc, char *argv[]){
    carregar_argumentos(argc, argv);
    carregar_clientes();
    carregar_comandos();
    liberar_memoria();
    return 0;
}