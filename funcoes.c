#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>


void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50])
{
    int escolha;
    printf("Escolha um %s:\n", selecao); //variavel de mesmo valor
    printf("\n1. %s\n", med1);
    printf("2. %s\n\n\tValor digitado: ", med2);
    scanf("%d", &escolha);
    while (escolha < 1 || escolha > 2)
    {
        printf("Opção inválida. Digite 1 ou 2.\n");
        printf("Escolha um %s:\n", selecao);
        printf("1. %s\n", med1);
        printf("2. %s\n", med2);
        scanf("%d", &escolha);
    }
    switch (escolha)
    {
        case 1:
            strcpy(nome_medico, med1);
            break;
        case 2:
            strcpy(nome_medico, med2);
            break;
    }
}

void removerQuebraDeLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void verificaData(int dta[3]) {
    while(dta[0]>31 || dta[1]>12 || dta[2]<2025){
        printf("Data invalida. Tente novamente: (dia,mes,ano)\n"); scanf("%d %d %d",&dta[0],&dta[1],&dta[2]);
    }
}

void verificaHorario(int *escolha){
        while(*escolha != 1 && *escolha != 2 && *escolha != 3){
            printf("Horario invalido. Tente novamente: ");  scanf("%d", &*escolha);
        }
    }

void lembrete(int *dia,int hora,char *nome) {
    for(int i = 0;  i<3;  i++){//Mostra a mensagem 3 vezes
        sleep(10);//Tempo decorrido até aparecer a mensagem
        printf("LEMBRETE\nConsulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
            dia[0],dia[1],dia[2],hora,nome);
        system("pause");//presisonar qualquer tecla para fechar a mensagem
        system("cls");//limpar a tela
    }
}
