#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct // Estrutura para guardar as informações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];
    char medico[100];
    char cpf[12];
    short status; // = 0 cancelado, 1 = agendado
} dados_paciente;

typedef struct
{

    char nome[61];
    char senha[21];
    char cpf[12];
    char idade[4];
    char email[61];

} cadastro_save;


typedef struct
{
    char nome[61];
    char cpf[12];
    char idade[4];
    char email[61];
    short autenticado;
    
} usuario;

typedef struct
{
    int dia;
    int mes;
    int ano;
    int hora;
} tempo; // struct para armazenar a data de agora;



#endif
