#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct  // Estrutura para guardar as informações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];
    char medico[100];
} dados_paciente;

typedef struct
{

    char nome[61];
    char senha[21];
    char cpf[12];
    char idade[4];

} cadastro_save;

cadastro_save cadastro;
dados_paciente paciente;

// remover \n
void removerQuebraDeLinha(char *str);

// menu para escolha do que fazer
int menu();
void agendar_consulta(int *logado, cadastro_save *usuario_logado);
// criação de conta
void cadastrar_conta(int *logado, cadastro_save *atual);

// login na conta
void login(int *logado, cadastro_save *atual);

// funcao para selecionar o medico
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50]);

// verifica a veracidade da data
void verificaData(int dta[3]);

// verifica a veracidade do horario
void verificaHorario(int *escolha);

//implementação dos lembretes
void lembrete(int *dia, int hora, char *med);

void buscar_consulta(int *logado, cadastro_save *cadastro);
void reagendar_consulta(const char *cpf);
void cancelar_consulta(const char *cpf);

// Funcao para buscar consultas já agendadas.

// Funcao ara cancelar consultas.
void cancelar_consulta(const char *cpf);

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf);

// Funcao para ver todas as consultas agendadas de determinado medico.
void ver_consultas_medico();

// Funcao para ver todas as consultas agendadas em determinado dia.
void ver_consultas_no_dia();




#endif
