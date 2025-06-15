#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif
#include "bibliotecas/funcoes.h"

// login conta admin
// cpf = 12345678901
// senha = 12345678
// email = adm@ufg.br

int main()
{

#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(65001); //diretivas de compilação somente para windows (resolve problema de caracteres especiais)
    SetConsoleCP(65001);
#endif



    char senha1[21]; // máximo de 60 caracteres
    char senha2[21]; // máximo de 60 caracteres
    char cpfDigitado[12];
    char senhaDigitada[61];
    int logado = 0;
    int *plog;
    plog = &logado;

    int choose = menu();

    switch (choose)
    {
    // se o usuario escolher a opcao Cadastramento de conta.

    case 1:
        
        printf_verde("\n\t\t\t\t\t\t=== SIGN IN ===\n");

        getchar(); // limpa o buffer pra iniciar

        printf("\n\tDigite o seu nome e sobrenome: ");
        fgets(cadastro.nome, sizeof(cadastro.nome), stdin);
        removerQuebraDeLinha(cadastro.nome);

        /* fgets funcina melhor que o scanf para pegar string (lê espaço).
        sizeof é pra garantir que o fgts n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */

        printf("\n\tDigite o seu cpf no formato"); // digitar cpf
        printf_vermelho(" (00000000000): ");

        scanf("%s", cadastro.cpf);
        removerQuebraDeLinha(cadastro.cpf);

        while (strlen(cadastro.cpf) != 11)
        { // loop que lê o cpf vê se ele é igual ou diferente de 11

            printf_vermelho("\n\tSeu CPF é inválido! Digite ele novamente: ");
            scanf("%s", cadastro.cpf);
        }

        printf("\n\tDigite o seu email para contato: ");
        scanf("%s", cadastro.email);

        while (verificaEmail(cadastro.email) == 0)
        {
            printf_vermelho("\n\tDigite um email válido: ");
            scanf("%s", cadastro.email);
        }

        removerQuebraDeLinha(cadastro.email);

        printf("\n\tDigite sua senha");
        printf_vermelho(" (mínimo 8 caracteres & máximo 20 caracteres)");
        printf(": ");

        scanf("%s", senha1);

        while (strlen(senha1) < 8 || strlen(senha1) > 20) // senha >= 8 caracteres
        {
            if (strlen(senha1) > 20)
                printf_vermelho("\n\tSenha maior que 20 caracteres!");

            else
                printf_vermelho("\n\tSenha menor que 8 caracteres!");

            printf("\n\tDigite sua senha novamente (mínino: 8 caracteres): ");
            scanf("%s", senha1);
        }

        do
        {
            printf("\n\tConfirme a sua senha: ");
            scanf("%s", senha2); // verificar senha

            if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
                printf_vermelho("\n\tAs senhas são diferentes!");

        } while (strcmp(senha1, senha2) != 0); // loop até as senhas serem iguais e maiores que 8 caracteres
        removerQuebraDeLinha(senha2);
        strcpy(cadastro.senha, senha2);

        printf("\n\tDigite a sua idade: ");

        scanf("%s", cadastro.idade);

        removerQuebraDeLinha(cadastro.idade);

        cadastrarpaciente(plog, cadastro);

        printf_verde("\n\tParabens, você está cadastrado! O que deseja fazer agora?\n");

        main();

        break;
    // Se o usuario escolher a opção Cadastrar Agendamento.



      case 2:

        printf_verde("\n\t\t\t\t\t\t\t\t===Agendamento ===\n");
        if (logado != 1)
        {
            printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }

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

        // segfault quando nome_med > 10;

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("\n\tMédico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, ano, hora; // declaracao de variaveis

        tempo data;
        tempoagora(&data); // coletando o tempo de agora

        printf("\n\tInforme a data da consulta (ex: %d/%d/%d): ", data.dia, data.mes, data.ano);
        scanf("%d/%d/%d", &dia, &mes, &ano);

        while (validardata(dia, mes, ano) == 0)
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

        main();
        break;



    // Se o usuario escolher a opcao Buscar de agendamento.
      case 3:
    
        printf_verde("\n\t\t\t\t\t\t=== Buscar Agendamento ===\n");
        if (logado != 1)
        {
            printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {
            // Funcao para buscar consultas.
            buscar_consulta(cadastro.nome, cpfDigitado);
            main();

        } 
    break;



    // se o usuario escolher a opcao Cancelamento de consulta.
    case 4: 
    
        printf_verde("\n\t\t\t\t\t\t=== Cancelamento de Consulta ===\n");
        if (logado != 1)
        {
            printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {

            // Funcao para cancelar consulta.
            cancelar_consulta(cpfDigitado);
            main();
        }
        break;
    


    // Se o usuario escolher a opcao Reagendamento de consulta.
    case 5:
    
        printf_verde("\n\t\t\t\t\t\t=== Reagendamento de Consulta ===\n");
        if (logado != 1)
        {
            printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado == 1)
        {

            // Funcao para reagendar consulta.
            reagendar_consulta(cpfDigitado);
            main();
        }
        break;



    // Se o usuario escolher a opcao Buscar consultas por dia e medico.
    case 6:
    
        printf_verde("\n\t\t\t\t\t\t=== Buscar Consultas ===\n");

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
        break;
    }

    return 0; // encerra o programa com sucesso
}
