#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "banker.h"

static void encerrar_com_erro(const char *mensagem){
    fprintf(stderr, "%s\n", mensagem);
    exit(EXIT_FAILURE);
}

int *criar_vetor(int tamanho){
    int *vetor = calloc(tamanho, sizeof(int));

    if (vetor == NULL){
        encerrar_com_erro("Erro: memória insuficiente");
    }

    return vetor;
}

static int ler_numero(const char *texto, int *valor){
    int digitos = 0;
    long long resultado = 0;

    while (texto[digitos] >= '0' && texto[digitos] <= '9') {
        resultado = resultado * 10 + (texto[digitos] - '0');
        if (resultado > INT_MAX){
            return 0;
        }
        digitos++;
    }

    if (digitos == 0){
        return 0;
    }

    *valor = (int) resultado;
    return digitos;
}

void carregar_argumentos(int argc, char *argv[]){
    int i;

    if (argc < 2){
        encerrar_com_erro("Erro: informe o número de instâncias de cada recurso. Exemplo: ./banker 10 5 7");
    }

    NUMBER_OF_RESOURCES = argc - 1;
    available = criar_vetor(NUMBER_OF_RESOURCES);

    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        int digitos = ler_numero(argv[i + 1], &available[i]);

        if (digitos == 0 || argv[i + 1][digitos] != '\0'){
            encerrar_com_erro("Erro: os argumentos devem ser números inteiros não negativos");
        }
    }
}