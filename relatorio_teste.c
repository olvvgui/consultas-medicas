#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dia[3];
    int horario;
    char nome[61];
    char medico[100];
    char cpf[12];

}dados_paciente;


void imprimeRelatorio(dados_paciente paciente); 

void relatorio(dados_paciente paciente){
    FILE *pt;
    short int existe = 0;
    short int escolha;
    char procura_nome[50];
    int procura_data[3];

    if((pt = fopen("relatorio.bin","rb"))==NULL){//Abre o arquivo binário para leitura dos registros
        printf("Erro ao tentar criar o arquivo.");
        system("pause");
        exit(1);
    }

    printf("\n<<Opcoes de busca>>\n");
    do{//Verifica se a escolha é coerente
        printf("1-Nome\n2-Data\n"); scanf("%hd",&escolha);
    while(getchar()!='\n');
    }while(escolha != 1 && escolha!= 2);//Relatório por médico ou por data

    switch(escolha){
        case 1:
            printf("Insira o Nome do Medico(a): "); fgets(procura_nome,sizeof(procura_nome),stdin);
            procura_nome[strcspn(procura_nome,"\n")]='\0';
            break;
        case 2:
            printf("Insira a Data de Agendamento: \n"); scanf("%d %d %d",&procura_data[0],&procura_data[1],&procura_data[2]);
            break;
    }

    while(fread(&paciente,sizeof(dados_paciente),1,pt)==1)//Lê os dados salvos no arquivo e compara
    {
        if(escolha == 1 && strcmp(paciente.medico,procura_nome)==0)
        {   
            imprimeRelatorio(paciente);  
            existe = 1;
        }
        if(escolha == 2 && paciente.dia[0]==procura_data[0]&&paciente.dia[1]==procura_data[1]&&paciente.dia[2]==procura_data[2])
        {
            imprimeRelatorio(paciente);
            existe = 1;
        }
    }
    if(!existe) printf("Nao ha registros");

    fclose(pt);
    return 0;
}

void imprimeRelatorio(dados_paciente paciente){//imprime os dados
    printf("Nome: %s\nCPF: %s\nDia: %02d/%02d/%d\nHorario: %02d:00\nMedico(a): %s\n",
    paciente.nome,paciente.cpf,paciente.dia[0], paciente.dia[1], paciente.dia[2],paciente.horario,paciente.medico);
    printf("------------------------------------------------------------\n");
    }
