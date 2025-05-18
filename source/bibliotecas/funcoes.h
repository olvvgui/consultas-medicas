#ifndef FUNCOES_H
#define FUNCOES_H

int menu();
void login(char cpfDigitado[12], char senhaDigitada[61], char nomeLogin[61], char idadeLogin[4], int *logado);
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50]);
void removerQuebraDeLinha(char *str);
void verificaData(int dta[3]);
void verificaHorario(int *escolha);
void lembrete(int *dia,int hora,char *med);
void buscar_consulta(const char *nome, const char *cpf);
void reagendar_consulta(const char *cpf);
void cancelar_consulta(const char *cpf);

struct dados_paciente // Estrutura para guardar as informações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];
    char medico[100];
};

struct dados_paciente paciente; // Inicializando uma estrutura

struct cadastro_save{

    char nome[61];
    char senha[21]; 
    char cpf[12];    
    char idade[4];

};

struct cadastro_save cadastro;

#endif
