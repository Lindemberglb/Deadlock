#ifndef BANKER_H
#define BANKER_H

extern int NUMBER_OF_CUSTOMERS;
extern int NUMBER_OF_RESOURCES;
extern int *available;

int *criar_vetor(int tamanho);
void carregar_argumentos(int argc, char *argv[]);

#endif