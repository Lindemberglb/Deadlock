#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "banker.h"

#define TAMANHO_LINHA 4096

static void encerrar_com_erro(const char *mensagem){
    fprintf(stderr, "%s\n", mensagem);
    exit(EXIT_FAILURE);
}

static void erro_formato(const char *nome_arquivo, int numero_linha){
    fprintf(stderr, "Erro: formato inválido na linha %d do arquivo %s\n", numero_linha, nome_arquivo);
    exit(EXIT_FAILURE);
}

int *criar_vetor(int tamanho){
    int *vetor = calloc(tamanho, sizeof(int));

    if (vetor == NULL) {
        encerrar_com_erro("Erro: memória insuficiente");
    }

    return vetor;
}

static int **criar_matriz(int linhas, int colunas){
    int **matriz = malloc(linhas * sizeof(int *));
    int i;

    if (matriz == NULL) {
        encerrar_com_erro("Erro: memória insuficiente");
    }

    for (i = 0; i < linhas; i++) {
        matriz[i] = criar_vetor(colunas);
    }

    return matriz;
}

static int ler_numero(const char *texto, int *valor){
    int digitos = 0;
    long long resultado = 0;

    while (texto[digitos] >= '0' && texto[digitos] <= '9') {
        resultado = resultado * 10 + (texto[digitos] - '0');
        if (resultado > INT_MAX) {
            return 0;
        }
        digitos++;
    }

    if (digitos == 0) {
        return 0;
    }

    *valor = (int) resultado;
    return digitos;
}

static int ler_linha(FILE *arquivo, char *linha){
    int tamanho;

    if (fgets(linha, TAMANHO_LINHA, arquivo) == NULL) {
        return 0;
    }

    tamanho = strlen(linha);

    if (tamanho > 0 && linha[tamanho - 1] == '\n') {
        linha[tamanho - 1] = '\0';
        tamanho--;
    } else if (!feof(arquivo)) {
        return -1;
    }

    if (tamanho > 0 && linha[tamanho - 1] == '\r') {
        linha[tamanho - 1] = '\0';
    }

    return 1;
}

void carregar_argumentos(int argc, char *argv[]){
    int i;

    if (argc < 2) {
        encerrar_com_erro("Erro: informe o número de instâncias de cada recurso. Exemplo: ./banker 10 5 7");
    }

    NUMBER_OF_RESOURCES = argc - 1;
    available = criar_vetor(NUMBER_OF_RESOURCES);

    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        int digitos = ler_numero(argv[i + 1], &available[i]);

        if (digitos == 0 || argv[i + 1][digitos] != '\0') {
            encerrar_com_erro("Erro: os argumentos devem ser números inteiros não negativos");
        }
    }
}

static int contar_valores(const char *linha){
    int quantidade = 1;
    int i;

    for (i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == ',') {
            quantidade++;
        }
    }

    return quantidade;
}

static int ler_linha_cliente(const char *linha, int *valores, int quantidade){
    int posicao = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        int digitos = ler_numero(linha + posicao, &valores[i]);

        if (digitos == 0) {
            return 0;
        }

        posicao += digitos;

        if (i < quantidade - 1) {
            if (linha[posicao] != ',') {
                return 0;
            }
            posicao++;
        }
    }

    return linha[posicao] == '\0';
}

void carregar_clientes(void){
    FILE *arquivo = fopen("customer.txt", "r");
    char linha[TAMANHO_LINHA];
    int status;
    int i, j;

    if (arquivo == NULL) {
        encerrar_com_erro("Erro: não foi possível abrir o arquivo customer.txt");
    }

    NUMBER_OF_CUSTOMERS = 0;

    while ((status = ler_linha(arquivo, linha)) != 0) {
        if (status == -1) {
            erro_formato("customer.txt", NUMBER_OF_CUSTOMERS + 1);
        }
        NUMBER_OF_CUSTOMERS++;
    }

    if (NUMBER_OF_CUSTOMERS == 0) {
        encerrar_com_erro("Erro: o arquivo customer.txt está vazio");
    }

    rewind(arquivo);

    maximum = criar_matriz(NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);
    allocation = criar_matriz(NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);
    need = criar_matriz(NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);

    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        ler_linha(arquivo, linha);

        if (i == 0 && contar_valores(linha) != NUMBER_OF_RESOURCES) {
            encerrar_com_erro("Erro: o número de argumentos é diferente da quantidade de recursos em customer.txt");
        }

        if (!ler_linha_cliente(linha, maximum[i], NUMBER_OF_RESOURCES)) {
            erro_formato("customer.txt", i + 1);
        }

        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j];
        }
    }
    fclose(arquivo);
}