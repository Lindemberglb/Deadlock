#include <stdlib.h>
#include "banker.h"

int NUMBER_OF_CUSTOMERS;
int NUMBER_OF_RESOURCES;
int *available;
int **maximum;
int **allocation;
int **need;

static void liberar_matriz(int **matriz, int linhas){
    int i;
    
    for (i = 0; i < linhas; i++)
        free(matriz[i]);

    free(matriz);
}

static void liberar_memoria(void){
    free(available);
    liberar_matriz(maximum, NUMBER_OF_CUSTOMERS);
    liberar_matriz(allocation, NUMBER_OF_CUSTOMERS);
    liberar_matriz(need, NUMBER_OF_CUSTOMERS);
}

int main(int argc, char *argv[]){
    carregar_argumentos(argc, argv);
    carregar_clientes();
    liberar_memoria();
    return 0;
}