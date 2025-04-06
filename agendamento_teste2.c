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

struct paciente paciente;//Inicializando uma estrutura

int main(){
    int dia;int mes;int ano;int medicos;
    char confirmacao[3];
    
    
    
    system("cls");//Limpando o terminal
    printf("Infome a data da consulta: (dia,mes,ano)\n");scanf(" %d %d %d",&dia,&mes,&ano);
    paciente.dia[0] = dia; paciente.dia[1] = mes; paciente.dia[2] = ano;
    //Lendo e colocando o dia, o mes e o ano dentro do vetor
    printf("Horarios disponiveis: \n");
    printf("01 - 8:00\n02 - 10:00\n03 - 14:00\nR: "); scanf("%d",&paciente.horario);
    switch(paciente.horario){
        case 1:
            paciente.horario = 8;
            break;
        case 2:
            paciente.horario = 10;
            break;
        case 3:
            paciente.horario = 14;
    }

    system("cls");
    printf("Escolha o médico responsável de acordo com o número:\n1. Paulo Roberto     /  Nutrólogo.\n2. José Moura        /  Cirurgião Geral.\n3. Rodrigo Coentrão  /  Urologista.\n4. Paula Pereira     /  Ginecologista.\n5. Fernanda Silva    /  Pediatra.\n6. Flavia Nunes      /  Ortopedista.\n7. Fabricio Mendes   /  Proctologista.\n8. Bruna Fernandes   /  Neurologista.\n9. Bruno Silva       /  Oftalmologista.\n10. Alex Jonas       /  Médico Clínico.\n");
  
    scanf( "%d", &medicos );
    switch ( medicos )
     {
      case 1 :
      printf("O médico escolhido foi Paulo Roberto  /  Nutrólogo\n");
      strcpy(paciente.nome,"Paulo Roberto");
      break;
      case 2 :
      printf("O médico escolhido foi José Moura  /  Cirurgião Geral\n");
      strcpy(paciente.nome,"José Moura");
      break;
      case 3 :
      printf("O médico escolhido foi Rodrigo Carvalho  /  Urologista\n");
      strcpy(paciente.nome,"Rodrigo Carvalho ");
      break;
      case 4 :
      printf("O médico escolhido foi Paula Pereira  /  Ginecologista\n");
      strcpy(paciente.nome,"Paula Pereira");
      break;
      case 5 :
      printf("O médico escolhido foi Fernanda Silva  /  Pediatra\n");
      strcpy(paciente.nome,"Fernanda Silva");
      break;
      case 6 :
      printf("O médico escolhido foi Flavia Nunes  /  Ortopedista\n");
      strcpy(paciente.nome,"Flavia Nunes");
      break;
      case 7 :
      printf("O médico escolhido foi Fabricio Mendes  /  Proctologista\n");
      strcpy(paciente.nome,"Fabricio Mendes ");
      break;
      case 8 :
      printf("O médico escolhido foi Bruna Fernandes  /  Neurologista\n");
      strcpy(paciente.nome,"Bruna Fernandes");
      break;
      case 9 :
      printf("O médico escolhido foi Bruno Silva  /  Oftalmologist\n");
      strcpy(paciente.nome,"Bruno Silva");
      break;
      case 10 :
      printf("O médico escolhido foi Alex Jonas  /  Médico Clínico\n");
      strcpy(paciente.nome,"Alex Jonas");
      break;
     }



    printf("\nDia: %02d/%02d/%d\nHorario: %d:00\nMedico: %s\n"
        ,paciente.dia[0],paciente.dia[1],paciente.dia[2],paciente.horario,paciente.nome);



    return 0;
    
    
}
