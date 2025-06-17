#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../consultas.h"
#include "sys/stat.h"

void lembrete(char *email, char *cpf, int *n)
{
    if (*n == 0)
    {

        FILE *arq = fopen("bin/dados_paciente.bin", "rb");
        if (arq == NULL)
            return;

        dados_paciente paciente;
        int contador = 0;

        while (fread(&paciente, sizeof(dados_paciente), 1, arq) == 1)
        {
            if (strcmp(paciente.cpf, cpf) == 0 && paciente.status == 1)
            {
                contador++;
                (*n)++;
                printf("\a"); // beep
                printf_vermelho("\n\t====LEMBRETE====\n");
                printf("Para: %s\n\n", email);
                printf("Consulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
                       paciente.dia[0], paciente.dia[1], paciente.dia[2], paciente.horario, paciente.medico);
            }
        }
        fclose(arq);
        if (contador == 0)
            return;
    }
    else 
    return; //já recebeu o lembretes
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

    char *medicos[10] = {
        "Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses",
        "Dra. Laura", "Dra. Eneida", "Dra. Maria"};
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
    printf("\nDigite a data (dia/mes):\n");
    printf("R: ");
    scanf("%d/%d", &diaesc[0], &diaesc[1]);

    while (validardata(diaesc[0], diaesc[1]) == 0)
    {
        printf_vermelho("\n\t Digite uma data válida! Abrimos apenas em dias úteis");
        scanf("%d/%d", &diaesc[0], &diaesc[1]);
    }

    diaesc[2] = 2025;

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

        if (strcmp(paciente.cpf, cpf) == 0 && paciente.status == 1)
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

void cancelar_consulta(const char *cpf)
{
    FILE *arquivo = fopen("bin/dados_clientes.bin", "rb+");
    if (!arquivo)
    {
        printf_vermelho("\nErro ao abrir o arquivo.\n");
        return;
    }

    dados_paciente paciente;
    long posicoes[100]; // guarda posições do arquivo / conta os bytes da struct
    int opcoes = 0;

    // Mostrar todas as consultas ativas
    printf("\nConsultas ativas encontradas:\n");
    while (fread(&paciente, sizeof(dados_paciente), 1, arquivo) == 1)
    {
        removerQuebraDeLinha(paciente.cpf);
        if (strcmp(paciente.cpf, cpf) == 0 && paciente.status == 1)
        {
            posicoes[opcoes] = ftell(arquivo) - sizeof(dados_paciente); // joga pro inicio da struct
            printf("\n[%d] Data: %02d/%02d/%d | Horário: %02d:00 | Médico: %s\n",
                   opcoes + 1, paciente.dia[0], paciente.dia[1], paciente.dia[2],
                   paciente.horario, paciente.medico);
            opcoes++;
        }
    }

    if (opcoes == 0)
    {
        printf_vermelho("\nNenhuma consulta ativa encontrada para este CPF.\n");
        fclose(arquivo);
        return;
    }

    int escolha;
    printf_verde("\n\tDigite o número da consulta que deseja CANCELAR: ");
    scanf("%d", &escolha);
    getchar(); // Limpa buffer

    if (escolha < 1 || escolha > opcoes)
    {
        printf_vermelho("\nEscolha inválida.\n");
        fclose(arquivo);
        return;
    }

    fseek(arquivo, posicoes[escolha - 1], SEEK_SET);
    fread(&paciente, sizeof(dados_paciente), 1, arquivo);

    paciente.status = 0;
    fseek(arquivo, -sizeof(dados_paciente), SEEK_CUR);
    fwrite(&paciente, sizeof(dados_paciente), 1, arquivo);

    printf_verde("\nConsulta cancelada com sucesso!\n");

    fclose(arquivo);
}

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf)
{
    FILE *arquivo = fopen("bin/dados_clientes.bin", "rb+");
    if (!arquivo)
    {
        printf_vermelho("\nErro ao abrir o arquivo.\n");
        return;
    }

    dados_paciente paciente;
    long posicoes[100];
    int opcoes = 0;

    printf("\nConsultas ativas encontradas:\n");
    while (fread(&paciente, sizeof(dados_paciente), 1, arquivo) == 1)
    {
        removerQuebraDeLinha(paciente.cpf);
        if (strcmp(paciente.cpf, cpf) == 0 && paciente.status == 1)
        {
            posicoes[opcoes] = ftell(arquivo) - sizeof(dados_paciente); // ftell retorna o local do ponteiro
            printf("\n[%d] Data: %02d/%02d/%d | Horário: %02d:00 | Médico: %s\n",
                   opcoes + 1, paciente.dia[0], paciente.dia[1], paciente.dia[2],
                   paciente.horario, paciente.medico);
            opcoes++;
        }
    }

    if (opcoes == 0)
    {
        printf_vermelho("\nNenhuma consulta ativa encontrada para este CPF.\n");
        fclose(arquivo);
        return;
    }

    int escolha;
    printf_verde("\nDigite o número da consulta que deseja REAGENDAR: ");
    scanf("%d", &escolha);
    getchar(); // Limpa buffer

    if (escolha < 1 || escolha > opcoes)
    {
        printf_vermelho("\nEscolha inválida.\n");
        fclose(arquivo);
        return;
    }

    fseek(arquivo, posicoes[escolha - 1], SEEK_SET);
    fread(&paciente, sizeof(dados_paciente), 1, arquivo);

    paciente.dia[2] = 2025;

    printf("\nInforme a nova data da consulta (dia/mes): ");
    scanf("%d/%d", &paciente.dia[0], &paciente.dia[1]);

    while (!validardata(paciente.dia[0], paciente.dia[1]))
    {
        printf_vermelho("\n\tInforme uma data válida (dia/mês): ");
        scanf("%d/%d/%d", &paciente.dia[0], &paciente.dia[1]);
    }

    fseek(arquivo, -sizeof(dados_paciente), SEEK_CUR);
    fwrite(&paciente, sizeof(dados_paciente), 1, arquivo);

    printf_verde("\nConsulta reagendada com sucesso!\n");

    fclose(arquivo);
}

void atualizar_consultas()
{
    printf("\n\tdigite a senha para continuar: ");
    char senha[9] = "19283746"; // senha
    char digitada[9];
    scanf("%s", digitada);
    if (strcmp(senha, digitada) == 0)
    {
        FILE *arquivo = fopen("bin/dados_clientes.bin", "rb+");
        if (!arquivo)
        {
            printf_vermelho("\nErro ao abrir o arquivo.\n");
            return;
        }

        dados_paciente paciente;
        tempo data;
        tempoagora(&data);

        int status = 0;

        while (fread(&paciente, sizeof(dados_paciente), 1, arquivo) == 1)
        {
            if (paciente.status == 1)
            {
                int dia = paciente.dia[0];
                int mes = paciente.dia[1];
                int ano = paciente.dia[2];

                // verifica se a data já passou
                if ((ano < data.ano) ||
                    (ano == data.ano && mes < data.mes) ||
                    (ano == data.ano && mes == data.mes && dia < data.dia))
                {
                    paciente.status = 0;
                    fseek(arquivo, -sizeof(dados_paciente), SEEK_CUR);
                    fwrite(&paciente, sizeof(dados_paciente), 1, arquivo); // joga no arquivo
                    status++;
                }
            }
        }

        fclose(arquivo);

        if (status > 0)
            printf("\n\t%d consultas vencidas foram marcadas como inativas.\n", status);
        else
            printf_vermelho("\n\tNenhuma consulta vencida encontrada.\n");

        return;
    }

    else
        return;
}
