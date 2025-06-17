
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../consultas.h"


void lembrete(int *dia, int hora, char *medico, char *email)
{
    printf("\a"); // beep
    sleep(2);     // Tempo decorrido até aparecer a mensagem
    printf("Para: %s\n\n", email);
    printf_vermelho("\t====LEMBRETE====\n");
    printf("Consulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
           dia[0], dia[1], dia[2], hora, medico); // adicionar email
}

// Funcao para ver todas as consultas agendadas em um determinado medico.
void ver_consultas_medico()
{

    int nome_med = 0;

    // Abre o arquivo com os dados das consultas.
    FILE *consultas = fopen("bin/dados_clientes.bin", "rb");

    if (consultas == NULL)
    {
        printf_vermelho("\n\tNenhuma consulta agendada.\n");
        return;
    }

    dados_paciente paciente;

    char *medicos[10] = {"Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};
    // For para escolher o medico.

    while (nome_med > 10 || nome_med < 1)
    {

        printf_verde("\nSelecione o medico: \n");

        for (int i = 0; i < 10; i++)
        {
            printf("%d. %s\n", i + 1, medicos[i]);
        }

        printf("R: ");

        scanf("%d", &nome_med);

        if (nome_med > 10 || nome_med < 1)
        {
            printf_vermelho("\nMedico inválido\n");
        }
    }

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
    FILE *consultas = fopen("bin/dados_clientes.bin", "rb");

    if (consultas == NULL)
    {
        printf_vermelho("\nNenhuma consulta agendada ainda.\n");
        return;
    }

    dados_paciente paciente;
    // Escolher o dia.
    printf("\nDigite o dia (dia/mes/ano):\n");
    printf("R: ");

    scanf("%d/%d/%d", &diaesc[0], &diaesc[1], &diaesc[2]);

    printf("\nConsultas marcado no dia %02d/%02d/%04d\n", diaesc[0], diaesc[1], diaesc[2]);

    // Le o arquivo ate o fim.
    while (fread(&paciente, sizeof(dados_paciente), 1, consultas) == 1)
    {
        // Compara o dia escolhido com o dia da consulta marcada.

        if (paciente.dia[0] == diaesc[0] && paciente.dia[1] == diaesc[1] && paciente.dia[2] == diaesc[2])
        {
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: %s\n", paciente.medico);
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
        }

        // Fecha o arquivo.
        fclose(consultas);
    }
}

// Funcao para buscar consultas já agendadas.
void buscar_consulta(const char *nome, const char *cpf)
{
    dados_paciente paciente;
    // Abre o arquivo com os agendamentos salvos e lê.

    FILE *le_dados = fopen("bin/dados_clientes.bin", "rb");

    if (le_dados == NULL)
    {
        printf_vermelho("\nErro ao buscar consultas.\n");
        return;
    }

    int encontrado = 0; // flag para saber se encontrou alguma consulta.

    printf_verde("\n\n\t\t=== Consultas Agendadas ===\n\n");

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, le_dados) == 1)
    {
        // Remove quebras de linha.
        removerQuebraDeLinha(paciente.nome);
        removerQuebraDeLinha(paciente.cpf);

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.

        if (strcmp(paciente.cpf, cpf) == 0)
        {
            printf("\nPaciente CPF: %s", paciente.cpf);
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
        printf_vermelho("\n\tNenhuma consulta encontrada para");
        printf(" %s (CPF: %s).\n\n", nome, cpf);
    }
    // Fecha o arquivo.
    fclose(le_dados);
}

// Funcao para cancerlar consultas.
void cancelar_consulta(const char *cpf)
{

    // Abre o arquivo onde está salvo os dados das consultas.
    FILE *cancelar = fopen("bin/dados_clientes.bin", "rb");
    if (cancelar == NULL)
    {
        printf_vermelho("\n\nConsulta não encontrada.\n");
        return;
    }

    // Abre um arquivo para auxiliar no cancelamento de consultas.
    FILE *auxiliar_cancelar = fopen("bin/auxiliar.bin", "wb");
    if (auxiliar_cancelar == NULL)
    {
        printf_vermelho("\nErro ao criar arquivo temporário.\n");
        fclose(cancelar);
        return;
    }

    dados_paciente paciente;
    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, cancelar) == 1)
    {

        removerQuebraDeLinha(paciente.cpf); // Remove quebras de linha.

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.
        if (strcmp(paciente.cpf, cpf) == 0)
        {
            encontrado = 1;
            printf_verde("\n\n\tConsulta cancelada com sucesso:\n");
            printf("\tData: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("\tHorário: %02d:00\n", paciente.horario);
            printf("\tMédico: %s\n", paciente.medico);
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
        printf_vermelho("\nConsulta não encontrada.\n");
        remove("bin/auxiliar.bin");
    }
    else
    {

        // Apaga o arquivos que contem os dados de consultas e renomeia o arquivo auxiliar com o nome do antigo arquivo que armazenava os dados das consultas.
        remove("bin/dados_clientes.bin");
        rename("bin/auxiliar.bin", "bin/dados_clientes.bin");
    }
}

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf)
{


    // Abre o arquivo com os dados de consultas agendadas.
    FILE *reagendar = fopen("bin/dados_clientes.bin", "rb");
    if (reagendar == NULL)
    {
        printf_vermelho("\nConsulta não encontrada.\n");
        return;
    }
    // Abre o arquivo para auxiliar o reagendamento de consultas.
    FILE *auxiliar_reagendar = fopen("bin/temp.bin", "wb");
    if (auxiliar_reagendar == NULL)
    {
        printf_vermelho("\nErro ao criar arquivo temporário.\n");
        fclose(reagendar);
        return;
    }

    dados_paciente paciente;
    int encontrado = 0; // Variavel para sabe se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, reagendar) == 1)
    {
        removerQuebraDeLinha(paciente.cpf);

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.
        if (strcmp(paciente.cpf, cpf) == 0)
        {
            encontrado = 1;
            printf("\nConsulta:\n");
            printf("Data: %02d/%02d/%d\n", paciente.dia[0], paciente.dia[1], paciente.dia[2]);
            printf("Horário: %02d:00\n", paciente.horario);
            printf("Médico: %s\n", paciente.medico);
            // Questiona a nova data e hora da consulta.
            printf("\nInforme a data da consulta (dia/mes/ano): ");
            scanf("%d/%d/%d", &paciente.dia[0], &paciente.dia[1], &paciente.dia[2]);

            while (validardata(paciente.dia[0], paciente.dia[1]) == 0)
            {
                printf("\n\tInforme uma data válida (dia/mês/ano): ");
                scanf("%d/%d/%d", &paciente.dia[0], &paciente.dia[1], &paciente.dia[2]);
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
        remove("bin/temp.bin");
    }
    else
    {
        // Apaga o arquivos que contem os dados de consultas e renomeia o arquivo auxiliar com o nome do antigo arquivo que armazenava os dados das consultas.
        remove("bin/dados_clientes.bin");
        rename("bin/temp.bin", "bin/dados_clientes.bin");
    }
}
