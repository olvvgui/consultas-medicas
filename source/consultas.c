#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "bibliotecas/funcoes.c"
#include "bibliotecas/funcoes.h"

int main()
{

    char senha1[21]; // máximo de 60 caracteres
    char senha2[21]; // máximo de 60 caracteres
    char cpfDigitado[12];
    char senhaDigitada[61];
    int logado;
    int *plog;
    plog = &logado;

    int choose = menu();

    // Se o usuario escolher a opcao Cadastramento de conta.
    if (choose == 1)
    {
        printf("\n\t\t=== SIGN IN ===\n");

        getchar(); // limpa o buffer pra iniciar

        printf("\n\tDigite o seu nome e sobrenome: ");
        fgets(cadastro.nome, sizeof(cadastro.nome), stdin);
        removerQuebraDeLinha(cadastro.nome);

        /* fgets funcina melhor que o scanf para pegar string (lê espaço).
        sizeof é pra garantir que o fgts n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */

        printf("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf                                             // limpa o buffer pra iniciar
        scanf("%s", cadastro.cpf);
        removerQuebraDeLinha(cadastro.cpf);

        while (strlen(cadastro.cpf) != 11)
        { // loop que lê o cpf vê se ele é igual ou diferente de 11

            printf("\n\tSeu CPF é inválido! Digite ele novamente: ");
            scanf("%s", cadastro.cpf);
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

        removerQuebraDeLinha(senha2);
        strcpy(cadastro.senha, senha2);

        printf("\n\tDigite a sua idade: ");

        scanf("%s", cadastro.idade);

        removerQuebraDeLinha(cadastro.idade);

        cadastrarpaciente(plog, cadastro);

        printf("\n\tParabens, voce está cadastrado! O que deseja fazer agora?\n\n");

        main();
    }

    // Se o usuario escolher a opcao Cadastrar Agendamento.
    else if (choose == 2)
    {
        if (logado != 1)
        {
            printf("%d", logado);
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        printf("\n\tBem vindo, Senhor(a) %s", cadastro.nome);

        char *espec[10] = {"Clinica", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia", "Neurologia", "Ortopedia", "Psiquiatria", "Oftalmologia", "Oncologia"};
        char *medicos[10] = {"Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};

        // Pergunta e escaneia a especialidade medica desejada.

        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                printf("\n\n\tSelecione o medico: ");

            printf("\n%d. %s - %s", i + 1, medicos[i], espec[i]);
        }
        printf("\n\tR: ");
        // Testes comparando a especialidade escolhida e o nome do médico.

        int nome_med = 0;
        scanf("%d", &nome_med);

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("\n\tMedico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, ano, hora; // declaracao de variaveis // contador do loop

        tempo data;
        tempoagora (&data); // coletando o tempo de agora

        printf("\n\tInforme a data da consulta (ex: %d/%d/%d): ", data.dia, data.mes, data.ano);
        scanf(" %d %d %d", &dia, &mes, &ano);

        while (validardata(dia, mes, ano) == 0)
        {
            printf("\n\tInforme uma data válida de consulta (dia mês ano): ");
            scanf(" %d %d %d", &dia, &mes, &ano);
        }

        paciente.dia[0] = dia;
        paciente.dia[1] = mes; // Lendo e colocando o dia, o mes e o ano dentro do vetor
        paciente.dia[2] = ano;

        int rd[4]; // vetor para armazenar valores aleatório dos horários

        randomizar(rd, 4, 6, 17); // vetor, tamanho do vetor, minimo valor atribuido, max valor atribuido

        printf("\nDigite o horário que for melhor para você!\nHorarios disponiveis:\n\n");

        for (int i = 0; i < 4; i++)
        {
            if (rd[i] == rd[i + 1])
                continue;

            else
                printf("\n\t%d: %d:00\n", (i + 1), rd[i]);
        }

        scanf("%d", &hora);

        while (hora > 4 || hora < 1)
        {
            printf("\n\t Horário inválido! Digite novamente: ");
            scanf("%d", &hora);
        }

        switch (hora)
        {
        case 01:
            paciente.horario = rd[0];
            break;

        case 02:
            paciente.horario = rd[1];
            break;

        case 03:
            paciente.horario = rd[2];
            break;

        case 04:
            paciente.horario = rd[3];
            break;
        }

        // aloca o horario escolhido pelo paciente na struct
        // Pergunta se deseja adicionar alguma observacao e salva o que foi digitado.
        printf("\n\tAdicione alguma observacao: \nR: ");
        getchar();
        fgets(paciente.obs, sizeof(paciente.obs), stdin);
        paciente.obs[strcspn(paciente.obs, "\n")] = 0;

        // Salva os dados obtidos no arquivo dados_clientes.bin.
        FILE *salvar_dados = fopen("dados_clientes.bin", "ab");
        fwrite(&paciente, sizeof(struct dados_paciente), 1, salvar_dados);
        fclose(salvar_dados);

        printf("\n\tConsulta agendada com sucesso! O que deseja fazer agora?\n\n");

        main();
    }

    // Se o usuario escolher a opcao Buscar de agendamento.
    else if (choose == 3)
    {
        if (logado != 1)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {
            // Funcao para buscar consultas.
            buscar_consulta(cadastro.nome, cpfDigitado);
            main();
        }
    }

    // Se o usuario escolher a opcao Cancelamento de consulta.
    else if (choose == 4)
    {
        if (logado != 1)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {

            // Funcao para cancelar consulta.
            cancelar_consulta(cpfDigitado);
            main();
        }
    }

    // Se o usuario escolher a opcao Reagendamento de consulta.
    else if (choose == 5)
    {
        if (logado != 1)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {

            // Funcao para reagendar consulta.
            reagendar_consulta(cpfDigitado);
            main();
        }
    }

    // Se o usuario escolher a opcao Buscar consultas por dia e medico.
    else if (choose == 6)
    {

        int escolha;

        printf("\n\tComo deseja buscar as consultas:\n1. Pesquisar por nome do médico.\n2. Pesquisar por consulta marcadas no dia.\nR: ");
        scanf("%d", &escolha);
        getchar(); // Limpar buffer

        if (escolha == 1)
        {

            // Funcao para ver todas as consultas agendadas em um determinado medico.
            ver_consultas_medico();
            main();
        }
        else if (escolha == 2)
        {

            // Funcao para ver todas as consultas agendadas em determinado dia.
            ver_consultas_no_dia();
            main();
        }
    }

    return 0; // encerra o programa com sucesso
}
