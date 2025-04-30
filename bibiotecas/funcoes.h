#ifndef FUNCOES_H
#define FUNCOES_H
int menu();
void login(char cpfDigitado[12], char senhaDigitada[61], char nomeLogin[61], char idadeLogin[4], int *logado);
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50]);
void removerQuebraDeLinha(char *str);
void verificaData(int *hora);
void verificaHorario(int *escolha);
void lembrete(int *dia,int hora,char *med);
#endif
