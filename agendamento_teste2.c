#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct paciente//Estrutura para guardar as infomrações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];

};

struct paciente paciente; //Inicializando uma estrutura

int main(){ //aloca os dados da consulta agendada pelo paciente
    int dia, mes, ano, hora, medicos; //declaracao de variaveis
    int i; // contador do loop

    //char confirmacao[3];

    //system("clear"); //Limpando o terminal - linux
    //system("cls");//Limpando o terminal - windows
    printf("Informe a data da consulta: (dia,mes,ano)\n"); scanf(" %d %d %d", &dia, &mes, &ano);
    paciente.dia[0] = dia; paciente.dia[1] = mes; paciente.dia[2] = ano;

    //Lendo e colocando o dia, o mes e o ano dentro do vetor
    printf("Horarios disponiveis: \n");
    printf("01 - 8:00\n02 - 10:00\n03 - 14:00\nR: "); scanf("%d", &hora);

    switch (hora) {
        case 01:
            paciente.horario = 8;

        case 02:
            paciente.horario = 10; //nao usar break

        case 03:
            paciente.horario = 14;

    } // aloca o horario escolhido pelo paciente na struct

    //system("cls");
    //system("clear"); -- Linux
    char meds[10][25] = {"Paulo", "Jose", "Rodrigo", "Paula", "Fernanda", "Flavia", "Fabricio", "Bruna", "Bruno", "Alex"};
    char espec[10][25] = {"Oftalmologia", "Ortopedia", "Oncologia", "Neurocirurgia", "Psiquiatria", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia", "Cirurgia-geral"}; //adequar para ter o numero de n medicos necessarios;

    i = 0;

    while ( i < 10 ) {

        printf("Opcao %d: %s - %s \n", i + 1, meds[i], espec[i] );
        i++;
    }

    scanf("%d", &medicos );
    strcpy(paciente.nome, meds[medicos - 1]);

    printf("\nDia: %02d/%02d/%d\nHorario: %d:00\nMedico: %s \nEspecialidade: %s\n", paciente.dia[0], paciente.dia[1], paciente.dia[2], paciente.horario, paciente.nome, espec[medicos - 1]);

    return 0;
}
