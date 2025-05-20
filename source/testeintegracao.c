#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include "funcoes.c"
#include "funcoes.h"
// Essa função remove o '\n' que o fgets captura do teclado.
// Exemplo: se você digita "joao", o fgets salva "joao\n", o que atrapalha a comparação.
// Essa função localiza o '\n' e troca por '\0', o caractere de fim de string.

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

int main()
{
    char senha1[21]; // máximo de 60 caracteres
    char senha2[21]; // máximo de 60 caracteres
    char cpfDigitado[12];
    char senhaDigitada[61];
    int logado = 0;
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

        limparTerminal();

        printf("\t\nParabens, voce está cadastrado! O que deseja fazer agora?\n\n");

        main();
    }

    // Se o usuario escolher a opcao Cadastrar Agendamento.
    else if (choose == 2)
    {
        login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);

        printf("Bem vindo, Senhor(a) %s", cadastro.nome);

        char *espec[10] = {"Clinica", "Pediatria", "Ginecologia", "Cardiologia", "Dermatologia", "Neurologia", "Ortopedia", "Psiquiatria", "Oftalmologia", "Oncologia"};
        char *medicos[10] = {"Dr. Joao", "Dr. Medina", "Dr. Carlos", "Dr. Socrates", "Dr. Arnaldo", "Dr. Braulio", "Dr. Ulisses", "Dra. Laura", "Dra. Eneida", "Dra. Maria"};

        // Pergunta e escaneia a especialidade medica desejada.

        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                printf("\n\nSelecione o medico: ");

            printf("\n%d. %s - %s", i + 1, medicos[i], espec[i]);
        }
        printf("\nR: ");
        // Testes comparando a especialidade escolhida e o nome do médico.

        int nome_med = 0;
        scanf("%d", &nome_med);

        strcpy(paciente.medico, medicos[nome_med - 1]);
        printf("\nMedico selecionado: %s!", paciente.medico);
        strcpy(paciente.medico, medicos[nome_med - 1]);
        // aloca os dados da consulta agendada pelo paciente
        int dia, mes, ano, hora; // declaracao de variaveis // contador do loop

        // char confirmacao[3];

        // system("clear"); //Limpando o terminal - linux
        // system("cls");//Limpando o terminal - windows
        printf("\n\nInforme a data da consulta (dia mês ano): ");
        scanf(" %d %d %d", &dia, &mes, &ano);
        paciente.dia[0] = dia;
        paciente.dia[1] = mes;
        paciente.dia[2] = ano;

        // Lendo e colocando o dia, o mes e o ano dentro do vetor
        printf("\nHorarios disponiveis:\n\n");
        printf("\n01 - 08:00\n02 - 10:00\n03 - 14:00\n\nR: ");
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
        printf("\nAdicione alguma observacao: \nR: ");
        getchar();
        fgets(paciente.obs, sizeof(paciente.obs), stdin);
        paciente.obs[strcspn(paciente.obs, "\n")] = 0;

        // Salva os dados obtidos no arquivo dados_clientes.bin.
        FILE *salvar_dados = fopen("dados_clientes.bin", "ab");
        fwrite(&paciente, sizeof(struct dados_paciente), 1, salvar_dados);
        fclose(salvar_dados);

        printf("\n\tConsulta agendada com sucesso!\n\n");
    }

    // Se o usuario escolher a opcao Buscar de agendamento.
    else if (choose == 3)
    {
        if (!logado)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado)
        {

            // Funcao para buscar consultas.
            buscar_consulta(cadastro.nome, cpfDigitado);
        }
    }

    // Se o usuario escolher a opcao Cancelamento de consulta.
    else if (choose == 4)
    {
        if (!logado)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado)
        {

            // Funcao para cancelar consulta.
            cancelar_consulta(cpfDigitado);
        }
    }

    // Se o usuario escolher a opcao Reagendamento de consulta.
    else if (choose == 5)
    {
        if (!logado)
        {
            printf("\n\tÉ necessário fazer login primeiro.\n");
            login(cpfDigitado, senhaDigitada, cadastro.nome, cadastro.idade, plog);
        }
        if (logado)
        {

            // Funcao para reagendar consulta.
            reagendar_consulta(cpfDigitado);
        }
    }

    // Se o usuario escolher a opcao Buscar consultas por dia e medico.
    else if (choose == 6)
    {

        int escolha;

        printf("Como deseja buscar as consultas:\n1. Pesquisar por nome do médico.\n2. Pesquisar por consulta marcadas no dia.\nR: ");
        scanf("%d", &escolha);
        getchar(); // Limpar buffer

        if (escolha == 1)
        {

            // Funcao para ver todas as consultas agendadas em um determinado medico.
            ver_consultas_medico();
        }
        else if (escolha == 2)
        {

            // Funcao para ver todas as consultas agendadas em determinado dia.
            ver_consultas_no_dia();
        }
    }

    return 0; // encerra o programa com sucesso
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

    struct dados_paciente paciente;

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
    while (fread(&paciente, sizeof(struct dados_paciente), 1, consultas) == 1)
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

    struct dados_paciente paciente;
    // Escolher o dia.
    printf("\nDigite o dia (dia mes ano):\n");
    printf("R: ");

    scanf("%d %d %d", &diaesc[0], &diaesc[1], &diaesc[2]);

    printf("\nConsultas marcado no dia %02d/%02d/%04d\n", diaesc[0], diaesc[1], diaesc[2]);

    // Le o arquivo ate o fim.
    while (fread(&paciente, sizeof(struct dados_paciente), 1, consultas) == 1)
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
void buscar_consulta(const char *nome, const char *cpf)
{
    // Abre o arquivo com os agendamentos salvos e lê.
    FILE *le_dados = fopen("dados_clientes.bin", "rb");

    if (le_dados == NULL)
    {
        printf("\nNenhuma consulta agendada.\n");
        return;
    }

    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.
    struct dados_paciente paciente;

    printf("\n\n\t\t=== Consultas Agendadas ===\n\n");

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(struct dados_paciente), 1, le_dados) == 1)
    {
        // Remove quebras de linha.
        removerQuebraDeLinha(paciente.nome);
        removerQuebraDeLinha(cadastro.cpf);

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.

        if (strcmp(cadastro.cpf, cpf) == 0)
        {
            printf("\nPaciente CPF: %s", cadastro.cpf);
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
        printf("\n\tNenhuma consulta encontrada para %s (CPF: %s).\n\n", nome, cpf);
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

    struct dados_paciente paciente;
    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(struct dados_paciente), 1, cancelar) == 1)
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
            fwrite(&paciente, sizeof(struct dados_paciente), 1, auxiliar_cancelar);
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

    struct dados_paciente paciente;
    int encontrado = 0; // Variavel para sabe se encontrou alguma consulta.

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(struct dados_paciente), 1, reagendar) == 1)
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
        fwrite(&paciente, sizeof(struct dados_paciente), 1, auxiliar_reagendar);
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
