#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include "funcoes.c"
// Essa função remove o '\n' que o fgets captura do teclado.
// Exemplo: se você digita "joao", o fgets salva "joao\n", o que atrapalha a comparação.
// Essa função localiza o '\n' e troca por '\0', o caractere de fim de string.

struct dados_paciente // Estrutura para guardar as informações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];
    char medico[100];
};

struct dados_paciente paciente; // Inicializando uma estrutura

void ler_dados_agendamento();

int menu();

void login(char cpfDigitado[12], char senhaDigitada[61], char nomeLogin[61], char idadeLogin[4], int *logado);

int main()
{

    int choose = menu();

    char nome[61];   // criando a string do nome com máximo de 60 caracteres
    char senha1[61]; // máximo de 60 caracteres
    char senha2[61]; // máximo de 60 caracteres
    char cpf[12];    // máximo de 11 caracteres
    char idade[4];
    char cpfDigitado[12];
    char senhaDigitada[61];
    int logado = 0;
    int *plog;
    plog = &logado;

    if (choose == 1)
    {
        FILE *arquivo;
        arquivo = fopen("cadastro.txt", "a"); // abrindo (criando) o arquivo em modo append (adicionar)

        if (arquivo == NULL)
        {
            return 1; // fecha o programa se o arquivo não abrir
        }

        printf("\n\t\t=== SIGN IN ===\n");

        getchar(); // limpa o buffer pra iniciar

        printf("\n\tDigite o seu nome e sobrenome: ");
        fgets(nome, sizeof(nome), stdin);

        /* fgets funcina melhor que o scanf para pegar string (lê espaço).
        sizeof é pra garantir que o fgts n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */

        nome[strcspn(nome, "\n")] = 0; // remove o \n da string
        strcpy(paciente.nome, nome);

        printf("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf                                             // limpa o buffer pra iniciar
        scanf("%s", cpf);
        removerQuebraDeLinha(cpf);

        while (strlen(cpf) != 11)
        { // loop que lê o cpf vê se ele é igual ou diferente de 11

            printf("\n\tSeu CPF é inválido! Digite ele novamente: ");
            scanf("%s", cpf);
        }

        printf("\n\tDigite a sua senha: ");
        scanf("%s", senha1);

        do
        {
            printf("\n\tDigite sua senha novamente: ");
            scanf("%s", senha2); // verificar senha

            if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
                printf("\n\tAs senhas são diferentes! Tente novamente.\n");

        } while (strcmp(senha1, senha2) != 0); // loop até as senhas serem iguais

        printf("\n\tDigite a sua idade: ");
        scanf("%s", idade);

        removerQuebraDeLinha(cpf);
        removerQuebraDeLinha(nome);
        removerQuebraDeLinha(senha2);
        removerQuebraDeLinha(idade);

        fprintf(arquivo, "%s;%s;%s;%s\n", cpf, nome, senha2, idade); // escreve no arquivo
        fclose(arquivo);                                             // fecha o arquivo

        printf("\t\nParabens, voce está cadastrado! O que deseja fazer agora?\n\n");

        logado = 1;
        strcpy (cpfDigitado, cpf);
        choose = menu ();
    }

    if (choose == 2)
    {
        if (logado = 1)
        login(cpfDigitado, senhaDigitada, nome, idade, plog);

        printf("Bem vindo, Senhor(a) %s", nome);

        char *espec[10] = {"Clinica", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia", "Neurologia", "Ortopedia", "Psiquiatria", "Oftalmologia", "Oncologia"};
        char *medicos[10] = {"Joao", "Medina", "Carlos", "Socrates", "Arnaldo", "Braulio", "Ulisses", "Laura", "Eneida", "Maria"};
        // Pergunta e escaneia a especialidade medica desejada.

        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                printf("\nSelecione o medico: ");

            printf("\n%d. %s - %s", i + 1, medicos[i], espec[i]);
        }
        printf("\n");
        // Testes comparando a especialidade escolhida e o nome do médico.

        int nome_med = 0;
        scanf("%d", &nome_med);

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("Medico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, ano, hora; // declaracao de variaveis // contador do loop

        // char confirmacao[3];

        // system("clear"); //Limpando o terminal - linux
        // system("cls");//Limpando o terminal - windows
        printf("\nInforme a data da consulta (dia mês ano): ");
        scanf(" %d %d %d", &dia, &mes, &ano);
        paciente.dia[0] = dia;
        paciente.dia[1] = mes;
        paciente.dia[2] = ano;

        // Lendo e colocando o dia, o mes e o ano dentro do vetor
        printf("\nHorarios disponiveis:\n\n");
        printf("\n01 - 8:00\n02 - 10:00\n03 - 14:00\n\nR: ");
        scanf("%d", &hora);

        switch (hora)
        {
        case 01:
            paciente.horario = 8;
            break;
        case 02:
            paciente.horario = 10;
            break;
        case 03:
            paciente.horario = 14;
            break;

        default:
            paciente.horario = 0;

        } // aloca o horario escolhido pelo paciente na struct
        // Pergunta se deseja adicionar alguma observacao e salva o que foi digitado.
        printf("Adicione alguma observacao: \n");
        getchar();
        fgets(paciente.obs, sizeof(paciente.obs), stdin);
        paciente.obs[strcspn(paciente.obs, "\n")] = 0;

        // Salva os dados obtidos no arquivo dados_clientes.bin.
        FILE *salvar_dados = fopen("dados_clientes.bin", "ab");
        fwrite(&paciente, sizeof(struct dados_paciente), 1, salvar_dados);
        fclose(salvar_dados);

        printf("\n\tConsulta agendada com sucesso!\n\n");

        // Funcao para ler todos os dados adicionados.
        ler_dados_agendamento();
    }

    return 0; // encerra o programa com sucesso
}

// Funcao temporaria para ler todos os dados salvos no arquivo.
void ler_dados_agendamento()
{
    // Funcao que le todos os dados contidos no arquivo dados_clientes.bin.
    FILE *ler_dados_agendados = fopen("dados_clientes.bin", "rb");
    while (fread(&paciente, sizeof(struct dados_paciente), 1, ler_dados_agendados) == 1)
    {
        printf("Dia: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
        printf("Horario: %02d:00\n", paciente.horario);
        printf("Medico: %s\n", paciente.medico);
        printf("Observacao: %s\n", paciente.obs);
    }
    fclose(ler_dados_agendados);
}