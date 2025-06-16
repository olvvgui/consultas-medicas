#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "../main.h"

void agendar(usuario *usr)
{
      printf_verde("\n\t\t\t\t\t\t=== Buscar Agendamento ===\n");
    if (usr->autenticado != 1)
    {
        printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
        login(usr);
    }

    if (usr->autenticado == 1)
    {
        dados_paciente paciente;
        char *espec[10] = {"Clinica", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia", "Neurologia", "Ortopedia", "Psiquiatria", "Oftalmologia", "Oncologia"};
        char *medicos[10] = {"Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};

        // Pergunta e escaneia a especialidade medica desejada.

        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                printf("\n\n\tSelecione o médico: ");

            printf("\n\t%d. %s - %s", i + 1, medicos[i], espec[i]);
        }
        printf("\n\tR: ");
        // Testes comparando a especialidade escolhida e o nome do médico.

        int nome_med = 0;
        scanf("%d", &nome_med);

        // segfault quando nome_med > 10

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("\n\tMédico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, ano, hora; // declaracao de variaveis

        tempo data;
        tempoagora(&data); // coletando o tempo de agora

        printf("\n\tInforme a data da consulta (ex: %d/%d/%d): ", data.dia, data.mes, data.ano);
        scanf("%d/%d/%d", &dia, &mes, &ano);

        while (validardata(dia, mes) == 0)
        {
            printf_vermelho("\n\tInforme uma data válida de consulta (dia/mês/ano): ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
        }

        paciente.dia[0] = dia;
        paciente.dia[1] = mes; // Lendo e colocando o dia, o mes e o ano dentro do vetor
        paciente.dia[2] = ano;

        printf("\n\tHórarios disponíveis: ");

        int vet[4] = {0};
        int valido = 0;

        horariosvalidos(dia, vet);

        while (!valido)
        {
            printf("Digite o horário disponível que deseja agendar: ");
            scanf("%d", &hora);

            // verifica se o horário digitado está entre os horários disponíveis
            for (int i = 0; i < 4; i++)
            {
                // ignora posições zeradas (quando não há 4 horários)
                if (vet[i] != 0 && hora == vet[i])
                {
                    valido = 1; // achou um horário válido, pode sair do while
                    break;
                }
            }

            if (!valido)
                printf_vermelho("\n\tHorário inválido, digite novamente um dos horários disponíveis!\n");
        }

        // aloca o horario escolhido pelo paciente na struct
        // Pergunta se deseja adicionar alguma observacao e salva o que foi digitado.
        printf("\n\tAdicione alguma observacao: \nR: ");
        getchar();
        fgets(paciente.obs, sizeof(paciente.obs), stdin);
        paciente.obs[strcspn(paciente.obs, "\n")] = 0;

        // Salva os dados obtidos no arquivo dados_clientes.bin.
        FILE *salvar_dados = fopen("source/bin/dados_clientes.bin", "ab");
        fwrite(&paciente, sizeof(dados_paciente), 1, salvar_dados);
        fclose(salvar_dados);

        printf_verde("\n\t\t\t\t\t\tConsulta agendada com sucesso! O que deseja fazer agora?\n\n");
        return;
    }
}