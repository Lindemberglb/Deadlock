#ifndef BANKER_H
#define BANKER_H

extern int NUMBER_OF_CUSTOMERS;
extern int NUMBER_OF_RESOURCES;
extern int *available;
extern int **maximum;
extern int **allocation;
extern int **need;

int *criar_vetor(int tamanho);
void carregar_argumentos(int argc, char *argv[]);
void carregar_clientes(void);

#endif