#include <stdio.h>
#include <stdlib.h>
struct paciente//Estrutura para guardar as infomrações
{
    int dia[3];
    int horario;
    char nome[61];

};

struct paciente paciente;//Inicializando a estrutura

int main(){
    int dia;int mes;int ano;
    
    
    system("cls");//Limpando o terminal
    printf("Infome a data da consulta: (dia,mes,ano) ");scanf("%d %d %d",&dia,&mes,&ano);
    paciente.dia[0] = dia; paciente.dia[1] = mes; paciente.dia[2] = ano;
    //Lendo e colocando o dia, o mes e o ano dentro do vetor
    printf("Horarios disponiveis: \n");
    printf("01 - 8:00\n02 - 10:00\n03 - 14:00\nR: "); scanf("%d",&paciente.horario);
    switch(paciente.horario){
        case 01:
            paciente.horario = 8;
            break;
        case 02:
            paciente.horario = 10;
            break;
        case 03:
            paciente.horario = 14;
    }
    fflush(stdin);//limpando a memoria do buffer
    printf("Informe o nome do médico: ");gets(paciente.nome);

    printf("Dia: %02d/%02d/%d\nHorario: %d:00\nMedico: %s"
        ,paciente.dia[0],paciente.dia[1],paciente.dia[2],paciente.horario,paciente.nome);



    return 0;
