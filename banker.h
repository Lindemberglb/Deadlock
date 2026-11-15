#ifndef BANKER_H
#define BANKER_H

typedef struct {
    char tipo;
    int cliente;
    int *recursos;
} Comando;

extern int NUMBER_OF_CUSTOMERS;
extern int NUMBER_OF_RESOURCES;
extern int *available;
extern int **maximum;
extern int **allocation;
extern int **need;
extern Comando *comandos;
extern int quantidade_comandos;

int *criar_vetor(int tamanho);
void carregar_argumentos(int argc, char *argv[]);
void carregar_clientes(void);
void carregar_comandos(void);

#endif