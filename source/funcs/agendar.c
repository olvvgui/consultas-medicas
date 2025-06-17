#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc usadas futuramente)
#include <time.h>
#include "../main.h"

void agendar(usuario *usr)
{
    printf_verde("\n\t\t\t\t\t\t===Agendamento ===\n");
    if (usr->autenticado != 1)
    {
        printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
        login(usr);
    }

    if (usr->autenticado == 1)
    {
        dados_paciente paciente;
        strcpy(paciente.cpf, usr->cpf);
        strcpy(paciente.nome, usr->nome); // Salva o nome do usuário logado

        char *espec[10] = {"Clinica", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia",
                           "Neurologia", "Ortopedia", "Psiquiatria", "Oftalmologia", "Oncologia"};
                           
        char *medicos[10] = {"Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates",
                             "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};

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
        do
        {
            if (nome_med < 1 || nome_med > 10)
            {
                printf_vermelho("\n\tSelecione um médico válido (1-10): ");
            }
            else
            {
                printf("\n\tSelecione o médico: ");
            }
            scanf("%d", &nome_med);
        } while (nome_med < 1 || nome_med > 10);

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("\n\tMédico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, hora; // declaracao de variaveis

        tempo data;
        tempoagora(&data); // coletando o tempo de agora

        printf_vermelho("\n\tNão abrimos em domingos e feriados\n");
        printf("\n\tInforme a data da consulta (dia/mês, exemplo: %d/%d): ", data.dia, data.mes);
        scanf("%d/%d", &dia, &mes);

        while (validardata(dia, mes) == 0)
        {
            printf_vermelho("\n\tInforme uma data válida de consulta (dia/mês, exemplo: %d/%d): ");
            scanf("%d/%d", &dia, &mes);
        }

        paciente.dia[0] = dia;
        paciente.dia[1] = mes; // Lendo e colocando o dia, o mes e o ano dentro do vetor
        paciente.dia[2] = 2025;

        printf("\n\tHórarios disponíveis: ");

        int vet[4] = {0};
        int valido = 0;

       short check = horariosvalidos(dia, vet);

       if (check == 1){
        return;
       }

        while (!valido)
        {
            printf("\n\rDigite o horário disponível que deseja agendar: ");
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

        paciente.horario = hora; // Salva o horário escolhido

        printf("\n\tAdicione alguma observação: \nR: ");
        getchar();
        fgets(paciente.obs, sizeof(paciente.obs), stdin);
        paciente.obs[strcspn(paciente.obs, "\n")] = 0;

        paciente.status = 1; // define o status como agendado

        // Salva os dados obtidos no arquivo dados_clientes.bin.
        FILE *salvar_dados = fopen("bin/dados_clientes.bin", "ab");
        if (salvar_dados != NULL)
        {
            fwrite(&paciente, sizeof(dados_paciente), 1, salvar_dados);
            fclose(salvar_dados);
        }
        else
        {
            printf("Erro ao abrir o arquivo para salvar os dados.\n");
        }

        printf_verde("\n\t\t\t\t\t\tConsulta agendada com sucesso! O que deseja fazer agora?\n\n");
        return;
    }
}