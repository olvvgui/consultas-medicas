#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../utilitarios.h"

void removerQuebraDeLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void tempoagora(tempo *data) // função para coletar o tempo de agora e armazenar na struct.
{                            // serve para impedir o usuário de digitar uma data anterior da data de hoje

    time_t agora;    // variável do tipo time para armazenar o tempo atual em segundos desde 1970
    struct tm *info; // ponteiro para a struct da função que armazena data e hora

    time(&agora); // obtem os segundos desde 1970 e armazena na varável agora

    info = localtime(&agora); // converte os segundos para o tempo local do computador

    // armazena na struct a data em que o ponteiro *info aponta
    data->dia = info->tm_mday;        //  dia do mês (1-31)
    data->mes = info->tm_mon + 1;     // meses de (0-11) + 1 =  (1-12)
    data->ano = info->tm_year + 1900; // anos desde 1900 + 1900
    data->hora = info->tm_hour;       // hora de agora
}

int validardata(int dia, int mes)
{

    tempo data;
    tempoagora(&data);
    if (mes < 1 || mes > 12 || dia < 1) // retorna erro se a data for menor ou maior que os limites (mes 13, mes -1, dia -1, ano menor que o ano de agora)
        return 0;                       // data invalida

    if (mes < data.mes)
        return 0; // se o mes for anterior ao de hoje, erro

    if (mes == data.mes && dia < data.dia)
        return 0; // se, nesse mes, o dia for anterior ao de hoje

    int domingos[][7] = {
        {15, 22, 29},        // mes 6
        {6, 13, 20, 27},     // mes 7
        {3, 10, 17, 24, 31}, // mes 8
        {7, 14, 21, 28},     // mes 9
        {5, 12, 19, 26},     // mes 10
        {2, 9, 16, 23, 30},  // mes 11
        {7, 14, 21, 28}      // mes 12
    };

    int feriados[][7] = {
        {19},        // mes 6
        {0},         // mes 7
        {5},         // mes 8
        {7},         // mes 9
        {12, 24},    // mes 10
        {2, 15, 24}, // mes 11
        {25}         // mes 12
    };

    int qtdDomingos[7] = {3, 4, 5, 4, 4, 5, 4};
    int qtdFeriados[7] = {1, 0, 1, 1, 2, 3, 1};

    int j = mes - 6;
    if (j >= 0 && j < 7)
    {
        for (int i = 0; i < qtdDomingos[j]; i++)
        {
            if (domingos[j][i] == dia)
                return 0;
        }

        if (mes != 7)
        {
            for (int i = 0; i < qtdFeriados[j]; i++)
            {
                if (feriados[j][i] == dia && feriados[j][i] != 0)
                    return 0; //
            }
        }
    }

    switch (mes) // break é redundante nesse switch (mes)
    {
    case 6:
    case 9:
    case 11: // casos para meses de 30 dias

        if (dia <= 30)
            return 1;

        else
            return 0;

    default: // padrão para meses de 31 dias
        if (dia <= 31)
            return 1;

        else
            return 0;
    }
}

void horariosvalidos(int dia, int *vet)
{
    int rd[4] = {0};

    tempo data;
    tempoagora(&data);

    int min_hora, max_hora;
    min_hora = 6;
    max_hora = 17; // só pode marcar até 17h (17h-18h)

    if (dia == data.dia)
    {
        // se for pra hoje, só pode horários depois da hora atual
        // ex: agora é 13h, só pode marcar a partir das 14h
        min_hora = data.hora + 1;

        if (min_hora > max_hora)
        {
            printf_vermelho("\nNão há horários disponíveis para hoje!\n");
            return;
        }

        // preenche o vetor rd com horários únicos, dentro do intervalo correto
        randomizar(rd, 4, min_hora, max_hora);

        int disponiveis = 0;
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
            if (rd[i] != 0)
            {
                vet[i] = rd[i];
                printf("\n%d:00", rd[i]);
                disponiveis++;
            }
        }

        if (disponiveis == 0)
        {
            printf_vermelho("\nNão há horários disponíveis para hoje!\n");
            return;
        }
    }
    else
    {
        // para outras datas, pode de 6 até 17
        randomizar(rd, 4, min_hora, max_hora);

        int disponiveis = 0;
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
            if (rd[i] != 0)
            {
                vet[i] = rd[i];
                printf("\n%d:00", rd[i]);
                disponiveis++;
            }
        }
        if (disponiveis == 0)
        {
            printf_vermelho("\nNão há horários disponíveis!\n");
            return;
        }
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // ajustando o qsort para comparar o vetor
}

void randomizar(int *rd, int tam, int min, int max)
{
    int total = max - min + 1; // total de opções

    if (total < tam) // se houver menos opções do que posições, zera tudo
    {
        for (int i = 0; i < tam; i++)
            rd[i] = 0;
        return;
    }

    int pool[32]; // no máximo 32 opções
    // pool de piscina, no caso, piscina de inteiros pseudo-aleatórios com um limite definido
    for (int i = 0; i < total; i++)
        pool[i] = min + i; // preenche a pool com todos valores possíveis

    srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        int r = rand() % (total - i); // sorteia um índice dentro do ainda disponível
        rd[i] = pool[r];              // pega o valor sorteado
        // remove o valor já usado da pool (troca com o último disponível)
        int temp = pool[r];            // guarda temporariamente o valor sorteado
        pool[r] = pool[total - i - 1]; // coloca o último disponível no lugar do sorteado
        pool[total - i - 1] = temp;    // e coloca o sorteado no fim do pool (fora do próximo sorteio)
    }

    qsort(rd, tam, sizeof(int), compare); // ordena os horários para exibir em ordem
}

void printf_vermelho(char *txt)
{
    printf("\033[1;31m%s\033[0m", txt);
    // "\033[" ativa a sequencia ANSI (formastação espciacial d textos pro terminal)
    // "1;31m", "1" = negrito,  "31m" = vermelho
    // "\033[0m" reseta o texto pro normal do terminal
}

void printf_verde(char *txt)
{
    printf("\033[1;32m%s\033[0m", txt);
}