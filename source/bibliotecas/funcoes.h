#ifndef FUNCOES_H
#define FUNCOES_H

struct dados_paciente // Estrutura para guardar as informações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];
    char medico[100];
};

struct dados_paciente paciente; // Inicializando uma estrutura

typedef struct
{

    char nome[61];
    char senha[21];
    char cpf[12];
    char idade[4];

} cadastro_save;

cadastro_save cadastro;

typedef struct
{
    int dia;
    int mes;
    int ano;
    int hora;
} tempo; // struct para armazenar a data de agora;

// remover \n
void removerQuebraDeLinha(char *str);

// menu para escolha do que fazer
int menu();

// criação de conta
void cadastrarpaciente(int *pointer, cadastro_save cad);

// login na conta
void login(char cpfDigitado[12], char senhaDigitada[21], char nomeLogin[61], char idadeLogin[4], int *logado);

// funcao para selecionar o medico
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50]);

// pegar a data de agora
void tempoagora(tempo *data);

// verifica a veracidade da data
int validardata(int dia, int mes, int ano); 

// verifica a veracidade do horario
void verificaHorario(int *escolha);

//implementação dos lembretes
void lembrete(int *dia, int hora, char *med);

void buscar_consulta(const char *nome, const char *cpf);
void reagendar_consulta(const char *cpf);
void cancelar_consulta(const char *cpf);

// Funcao para buscar consultas já agendadas.
void buscar_consulta(const char *nome, const char *cpf);

// Funcao ara cancelar consultas.
void cancelar_consulta(const char *cpf);

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf);

// Funcao para ver todas as consultas agendadas de determinado medico.
void ver_consultas_medico();

// Funcao para ver todas as consultas agendadas em determinado dia.
void ver_consultas_no_dia();

// função para fazer o qsort comparar se um n é maior que o outro e ajustar em ordem crescente
int compare(const void *a, const void *b);

// gera inteiros aleatórios em razão do vetor, tamanho dele, e limites da geração de inteiros
void randomizar(int rd[], int tam, int min, int max); 

// printa o texto em vermelho
void printf_vermelho(const char *txt);




#endif
