#include <stdlib.h>
#include "banker.h"

int NUMBER_OF_CUSTOMERS;
int NUMBER_OF_RESOURCES;
int *available;

static void liberar_memoria(void){
    free(available);
}

int main(int argc, char *argv[]){
    carregar_argumentos(argc, argv);
    liberar_memoria();
    return 0;
}