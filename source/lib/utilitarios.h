#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "structs.h"

// remover \n
void removerQuebraDeLinha(char *str);

// pegar a data de agora
void tempoagora(tempo *data);

// verifica a veracidade da data
int validardata(int dia, int mes);

// função para mostrar horários disponíveis, de acordo com a data
void horariosvalidos(int dia, int *vet);

// função para fazer o qsort comparar se um n é maior que o outro e ajustar em ordem crescente
int compare(const void *a, const void *b);

// função para preencher um vetor com valores aleatórios únicos dentro de um intervalo fechado [min, max]
void randomizar(int *rd, int tam, int min, int max);

// printa o texto em vermelho
void printf_vermelho(char *txt);

// printa o texto em verde
void printf_verde(char *txt);

#endif