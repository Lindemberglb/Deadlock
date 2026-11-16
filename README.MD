# Algoritmo de Banker

Atividade de **Infraestrutura de Software** (CESAR School).

## Objetivo

Implementar o **Algoritmo de banker**, para evitar deadlock (processos travados esperando uns aos outros). O programa só aceita um pedido de recursos se o sistema continuar em estado seguro, ou seja, se ainda existir uma ordem em que todos os clientes conseguem terminar.

## O que o programa faz

1. Lê as unidades disponíveis de cada recurso (argumentos).
2. Lê o máximo que cada cliente pode precisar (`customer.txt`).
3. Lê e executa os comandos (`commands.txt`):
   - `RQ` pede recursos
   - `RL` devolve recursos
   - `*` mostra o estado atual

## Ambiente

- **Linguagem:** C
- **Compilador:** GCC
- **Sistema:** Linux (WSL Ubuntu no Windows 11)

## Arquivos

```
.
├── Makefile          # Compila com o comando `make` e gera o executável `banker`
├── main.c            # Chama a leitura dos dados e executa os comandos, um por vez, na ordem
├── banker.c          # Decide se um pedido (RQ) é seguro e atualiza os dados em RQ e RL
├── banker.h          # Declara as variáveis globais (available, maximum, allocation, need), a struct Comando e as funções
├── entrada.c         # Lê argumentos, customer.txt e commands.txt, valida o formato e encerra com mensagem de erro se algo estiver errado
├── customer.txt      # Contêm uma linha por cliente, com o máximo de cada recurso separado por vírgula
├── commands.txt      # Contêm um comando por linha (RQ pede, RL devolve, * mostra o estado), com valores separados por espaço
├── result.txt        # Arquivo gerado que mostra o resultado ao rodar o código
├── evidencias.log    # Arquivo que gravou todos os comandos inseridos no terminal durante a implementação da atividade
└── .gitignore        # Lista o que o Git deve ignorar, como o executável
```

## Formato das entradas

**Argumentos:** um número por recurso.
```bash
./banker 10 5 7
```

**`customer.txt`:** uma linha por cliente, valores separados por vírgula, um por recurso.
```
7,5,3
3,2,2
```

**`commands.txt`:** um comando por linha, valores separados por espaço. Clientes começam em 0.
```
RQ 0 0 1 0
RL 0 0 1 0
*
```

## Como compilar e rodar(exemplo)

```bash
make
./banker 10 5 7
```

## Como limpar(remover o arquivo executável)

```bash
make clean
```

Os arquivos `customer.txt` e `commands.txt` devem estar na pasta onde o programa é executado.
