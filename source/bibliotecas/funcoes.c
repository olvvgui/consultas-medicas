#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void agendar_consulta(int *logado, cadastro_save *usuario_logado) {
    if (*logado != 1) {
        printf("\n\tÉ necessário fazer login primeiro.\n");
        login(logado, &cadastro); // Função modificada para atualizar *logado

        if (*logado != 1) {
            return;
        }
    }

    dados_paciente nova_consulta;
    strcpy(nova_consulta.nome, usuario_logado->nome);

    printf("Agendamento");
    selecionar("Medico", "Rodrigo - Oftalmologia", "Sandro - Oncologia", nova_consulta.medico);

    printf("\nInforme a data da consulta (dia mes ano): ");
    scanf("%d %d %d", &nova_consulta.dia[0], &nova_consulta.dia[1], &nova_consulta.dia[2]);

    printf("\nHorários disponíveis:\n1. 08:00\n2. 10:00\n3. 14:00\nEscolha: ");
    int escolha_horario;
    scanf("%d", &escolha_horario);
    verificaHorario(&escolha_horario);

    switch (escolha_horario) {
        case 1: nova_consulta.horario = 8; break;
        case 2: nova_consulta.horario = 10; break;
        case 3: nova_consulta.horario = 14; break;
    }

    printf("\nDeseja adicionar alguma observação? ");
    getchar();
    fgets(nova_consulta.obs, sizeof(nova_consulta.obs), stdin);
    removerQuebraDeLinha(nova_consulta.obs);

    FILE *arquivo_consulta;

    arquivo_consulta = fopen("bin/dados_clientes.bin", "ab");

    if (arquivo_consulta == NULL) {
        exit(1);

    }

    fwrite(&nova_consulta, sizeof(nova_consulta), 1, arquivo_consulta);

    fclose(arquivo_consulta);

    printf("Agendado.");
}

void removerQuebraDeLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int menu()
{
    int escolha = 0;
    printf("\n\tEscolha o que deseja fazer:");
    printf("\n\t0.Sair do programa.");
    printf("\n\t1.Cadastramento de conta.");
    printf("\n\t2.Agendamento de consulta.");
    printf("\n\t3.Busca de agendamento.");
    printf("\n\t4.Cancelamento de consulta.");
    printf("\n\t5.Reagendamento de consulta.");
    printf("\n\t6.Buscar consultas por dia e medico.\n");
    printf("\n\tR: ");
    scanf("%d", &escolha);

    if (escolha == 0)
    {
        printf("\n\tFinalizando programa...");
        return 0;
    }

    if (escolha < 0 || escolha > 6)
    {

        printf("\nErro. Escolha uma opção válida.\n");
    }

    return escolha;
}

void cadastrar_conta(int *logado, cadastro_save *atual)
{
    if (*logado ==  1) {
        printf("Cadastro já realizado.!");
        return;
    }

    FILE *arquivo;
    arquivo = fopen("bin/cadastro.bin", "ab"); // abrindo (criando) o arquivo em modo append (adicionar)

    if (arquivo == NULL)
    {
        exit(1); // fecha o programa se o arquivo não abrir
    }

    fwrite(arquivo, sizeof(cadastro_save), 1, arquivo); // escreve no arquivo
    fclose(arquivo);                                 // fecha o arquivo

    *logado = 1;
}

void login(int *logado, cadastro_save *atual) {
    char cpf[12], senha[21];

    while (1) {
        printf("\n\tDigite o seu CPF (ou digite 'sair' para fechar o programa): ");
        fgets(cpf, sizeof(cpf), stdin);
        removerQuebraDeLinha(cpf);

        if (strcmp(cpf, "sair") == 0)
        {
            printf("\n\tFechando...");
            return; //em vez de quebrar o laço, encerra a funcao
        }

        FILE *lercadastro = fopen("bin/cadastro.bin", "rb");
        if (lercadastro == NULL)
        {
            printf("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
            return;
        }
        cadastro_save temp;
        int encontrado = 0;

        while (fread(&temp, sizeof(temp), 1, lercadastro) == 1)
        {

            if (strcmp(temp.cpf, cpf) == 0) // busca o cpf
            {
                encontrado = 1;
                break;
            }
        }
        fclose(lercadastro);

        if (!encontrado) {
            char opcao;
            printf("Usuario nao cadastrado. Deseja se cadastrar? ");

            scanf("%c", &opcao);
            getchar();

            if (opcao == 's' || opcao == 'S') {

                cadastrar_conta(logado, atual);
                return;

            }
            continue;
        }
            int tentativas = 3;
            while (tentativas > 0) {

                fgets(senha, sizeof(senha), stdin);
                removerQuebraDeLinha(senha);

                if (strcmp(temp.cpf, senha) == 0) {
                    *logado = 1;
                    *atual = temp;
                    printf("Bem vindo, %s", atual->nome);
                    return;
                }
                else {
                    printf("Senha invalida.");
                    tentativas-- ;
                }
            }

            printf("Tentativas esgotadas.");
            *logado = 0;
            return;
        }
    }


void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50])
{
    int escolha;
    printf("Escolha um %s:\n", selecao); // variavel de mesmo valor
    printf("\n1. %s\n", med1);
    printf("2. %s\n\n\tValor digitado: ", med2);
    scanf("%d", &escolha);
    while (escolha < 1 || escolha > 2)
    {
        printf("Opção inválida. Digite 1 ou 2.\n");
        printf("Escolha um %s:\n", selecao);
        printf("1. %s\n", med1);
        printf("2. %s\n", med2);
        scanf("%d", &escolha);
    }
    switch (escolha)
    {
    case 1:
        strcpy(nome_medico, med1);
        break;
    case 2:
        strcpy(nome_medico, med2);
        break;
    }
}

void verificaData(int dta[3])
{
    while (dta[0] > 31 || dta[1] > 12 || dta[2] < 2025)
    {
        printf("Data invalida. Tente novamente: (dia,mes,ano)\n");
        scanf("%d %d %d", &dta[0], &dta[1], &dta[2]);
    }
}

void verificaHorario(int *escolha)
{
    while (*escolha != 1 && *escolha != 2 && *escolha != 3)
    {
        printf("Horario invalido. Tente novamente: ");
        scanf("%d", &*escolha);
    }
}

void lembrete(int *dia, int hora, char *nome)
{
    for (int i = 0; i < 3; i++)
    {              // Mostra a mensagem 3 vezes
        sleep(10); // Tempo decorrido até aparecer a mensagem
        printf("LEMBRETE\nConsulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
               dia[0], dia[1], dia[2], hora, nome);
        // system("pause");//presisonar qualquer tecla para fechar a mensagem
        // system("cls");//limpar a tela
    }
}

// Funcao para ver todas as consultas agendadas em um determinado medico.
void ver_consultas_medico()
{

    int nome_med = 0;

    // Abre o arquivo com os dados das consultas.
    FILE *consultas = fopen("dados_clientes.bin", "rb");

    if (consultas == NULL)
    {
        printf("\nNenhuma consulta agendada.\n");
        return;
    }

    dados_paciente paciente;

    char *medicos[10] = {"\nDr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};
    // For para escolher o medico.
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
            printf("\nSelecione o medico: ");

        printf("%d. %s\n", i + 1, medicos[i]);
    }
    printf("R: ");

    scanf("%d", &nome_med);
    // Le o arquivo ate o fim.

    printf("\nConsultas marcadas por %s:\n\n", medicos[nome_med - 1]);
    while (fread(&paciente, sizeof(dados_paciente), 1, consultas) == 1)
    {
        // Compara o nome do medico escolhido com o nome do medico da consulta marcada.
        if (strcmp(paciente.medico, medicos[nome_med - 1]) == 0)
        {
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: %s\n", paciente.medico);
        }
    }

    // Fecha o arquivo.
    fclose(consultas);
}

// Funcao para ver todas as consultas agendadas em determinado dia.
void ver_consultas_no_dia()
{

    int diaesc[3];

    // Abre o arquivo com os dados das consultas.
    FILE *consultas = fopen("dados_clientes.bin", "rb");

    if (consultas == NULL)
    {
        printf("\nNenhuma consulta agendada ainda.\n");
        return;
    }

    dados_paciente paciente;

    // Escolher o dia.
    printf("\nDigite o dia (dia mes ano):\n");
    printf("R: ");

    scanf("%d %d %d", &diaesc[0], &diaesc[1], &diaesc[2]);

    printf("\nConsultas marcado no dia %02d/%02d/%04d\n", diaesc[0], diaesc[1], diaesc[2]);

    // Le o arquivo ate o fim.
    while (fread(&paciente, sizeof(dados_paciente), 1, consultas) == 1)
    {
        // Compara o dia escolhido com o dia da consulta marcada.

        if (paciente.dia[0] == diaesc[0] && paciente.dia[1] == diaesc[1] && paciente.dia[2] == diaesc[2])
        {
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: Dr. %s\n", paciente.medico);
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
        }

        // Fecha o arquivo.
        fclose(consultas);
    }
}

// Funcao para buscar consultas já agendadas.
void buscar_consulta(int *logado, cadastro_save *cadastro)
{
    // Abre o arquivo com os agendamentos salvos e lê.
    FILE *le_dados = fopen("dados_clientes.bin", "rb");

    char cpf[12];
    if (!logado)
        login(logado, cadastro);

    if (le_dados == NULL)
    {
        printf("\nNenhuma consulta agendada.\n");
        return;
    }

    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.
    dados_paciente paciente;


    printf("\n\n\t\t=== Consultas Agendadas ===\n\n");

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, le_dados) == 1)
    {
        // Remove quebras de linha.
        removerQuebraDeLinha(paciente.nome);
        removerQuebraDeLinha(cadastro->cpf);

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.

        if (strcmp(cadastro->cpf, cpf) == 0)
        {
            printf("\nPaciente CPF: %s", cadastro->cpf);
            printf("\nData: %02d/%02d/%d", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("\nHorário: %02d:00", paciente.horario);
            printf("\nMédico: %s", paciente.medico);
            printf("\nObservações: %s\n", paciente.obs);
            encontrado = 1;
        }
    }
    // Se não encontrou nenhuma consulta com o CPF digitado, imprime essa mensagem.
    if (!encontrado)
    {
        printf("\n\tNenhuma consulta encontrada para %s (CPF: %s).\n\n", paciente.nome, cpf);
    }
    // Fecha o arquivo.
    fclose(le_dados);
}

// Funcao ara cancerlar consultas.
void cancelar_consulta(const char *cpf)
{

    // Abre o arquivo onde está salvo os dados das consultas.
    FILE *cancelar = fopen("dados_clientes.bin", "rb");
    if (cancelar == NULL)
    {
        printf("\nConsulta não encontrada.\n");
        return;
    }

    // Abre um arquivo para auxiliar no cancelamento de consultas.
    FILE *auxiliar_cancelar = fopen("auxiliar.bin", "wb");
    if (auxiliar_cancelar == NULL)
    {
        printf("\nErro ao criar arquivo temporário.\n");
        fclose(cancelar);
        return;
    }

    dados_paciente paciente;
    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, cancelar) == 1)
    {

        removerQuebraDeLinha(cadastro.cpf); // Remove quebras de linha.

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.
        if (strcmp(cadastro.cpf, cpf) == 0)
        {
            encontrado = 1;
            printf("\nConsulta cancelada com sucesso:\n");
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: %s\n", paciente.medico);
        }
        else
        {

            // Escreve no arquivo auxiliar as consultas que não serão canceladas.
            fwrite(&paciente, sizeof(dados_paciente), 1, auxiliar_cancelar);
        }
    }

    // Fecha os arquivos.
    fclose(cancelar);
    fclose(auxiliar_cancelar);

    if (!encontrado)
    {
        printf("\nConsulta não encontrada.\n");
        remove("auxiliar.bin");
    }
    else
    {

        // Apaga o arquivos que contem os dados de consultas e renomeia o arquivo auxiliar com o nome do antigo arquivo que armazenava os dados das consultas.
        remove("dados_clientes.bin");
        rename("auxiliar.bin", "dados_clientes.bin");
    }
}

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf)
{

    // Abre o arquivo com os dados de consultas agendadas.
    FILE *reagendar = fopen("dados_clientes.bin", "rb");
    if (reagendar == NULL)
    {
        printf("\nConsulta não encontrada.\n");
        return;
    }
    // Abre o arquivo para auxiliar o reagendamento de consultas.
    FILE *auxiliar_reagendar = fopen("temp.bin", "wb");
    if (auxiliar_reagendar == NULL)
    {
        printf("\nErro ao criar arquivo temporário.\n");
        fclose(reagendar);
        return;
    }

    dados_paciente paciente;
    int encontrado = 0; // Variavel para sabe se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, reagendar) == 1)
    {
        removerQuebraDeLinha(cadastro.cpf);

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.
        if (strcmp(cadastro.cpf, cpf) == 0)
        {
            encontrado = 1;
            printf("\nConsulta:\n");
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: %s\n", paciente.medico);
            // Questiona a nova data e hora da consulta.
            printf("\nInforme a data da consulta (dia mes ano): ");
            scanf("%d %d %d", &paciente.dia[0], &paciente.dia[1], &paciente.dia[2]);
            verificaData(paciente.dia);

            printf("\n\nHorários disponíveis:\n");
            printf("1. 08:00\n2. 10:00\n3. 14:00\nEscolha: ");
            int nova_hora; // Escaneia o novo horario da consulta.
            scanf("%d", &nova_hora);

            switch (nova_hora)
            {
            case 1:
                paciente.horario = 8;
                break;
            case 2:
                paciente.horario = 10;
                break;
            case 3:
                paciente.horario = 14;
                break;
            default:
            {
                printf("Opção inválida. Usando horário padrão as 08:00.\n");
                paciente.horario = 8;
            }
            }

            printf("\nConsulta reagendada com sucesso!\n");
        }
        fwrite(&paciente, sizeof(dados_paciente), 1, auxiliar_reagendar);
    }
    // Fecha os arquivos abertos.
    fclose(reagendar);
    fclose(auxiliar_reagendar);
    // Imprime a mensaem se não foi encotrado a consulta.
    if (!encontrado)
    {
        printf("\nConsulta não encontrada.\n");
        remove("temp.bin");
    }
    else
    {
        // Apaga o arquivos que contem os dados de consultas e renomeia o arquivo auxiliar com o nome do antigo arquivo que armazenava os dados das consultas.
        remove("dados_clientes.bin");
        rename("temp.bin", "dados_clientes.bin");
    }
}

