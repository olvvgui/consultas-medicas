#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void removerQuebraDeLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int menu()
{
    int escolha = 0;
    printf_verde("\n\tEscolha o que deseja fazer:");
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
        printf_verde("\n\tFinalizando programa...");
        return 0;
    }

    if (escolha < 0 || escolha > 6)
    {

        printf_vermelho("\nErro. Escolha uma opção válida.\n");
    }

    return escolha;
}

void cadastrarpaciente(int *pointer, cadastro_save cad)
{
    FILE *arquivo;
    arquivo = fopen("bin/cadastro.bin", "ab"); // abrindo (criando) o arquivo em modo append (adicionar)

    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.");
        return; // fecha o programa se o arquivo não abrir
    }

    fwrite(&cad, sizeof(cadastro_save), 1, arquivo); // escreve no arquivo
    fclose(arquivo);                                 // fecha o arquivo

    *pointer = 1;
}

void login(char cpfDigitado[12], char senhaDigitada[21], char nomeLogin[61], char idadeLogin[4], int *logado)
{
    printf_verde("\n\t\t\t\t\t\t\t\t\t=== LOGIN ===\n");

    while (1)
    {

        char nome[61];   // criando a string do nome com máximo de 60 caracteres
        char senha2[21]; // máximo de 20 caracteres
        char cpf[12];    // máximo de 11 caracteres
        char idade[4];
        int loginRealizado = 0;

        printf("\n\tDigite o seu CPF (ou digite 'sair' para fechar o programa): ");
        scanf("%s", cpfDigitado);
        removerQuebraDeLinha(cpfDigitado);

        if (strcmp(cpfDigitado, "sair") == 0)
        { 
            printf_verde("\n\tFechando...");
            exit(0);
            break;
        }

        FILE *lercadastro = fopen("bin/cadastro.bin", "rb");
        if (lercadastro == NULL)
        {
            printf_vermelho("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
            exit(1);
        }

        while (fread(&cadastro, sizeof(cadastro_save), 1, lercadastro) == 1)
        {

            if (strcmp(cpfDigitado, cadastro.cpf) == 0) // busca o cpf
            {
                loginRealizado = 1;
                break;
            }
        }

        while (1)
        {
            if (loginRealizado == 1)
            { // Entrada da senha

                printf("\n\tSenha: ");
                getchar();
                scanf("%20s", senhaDigitada);
                removerQuebraDeLinha(senhaDigitada);

                // Compara os dados digitados com os do arquivo. Strcmp retorna 0 se as strings forem iguais

                removerQuebraDeLinha(cadastro.senha);
                if (strcmp(senhaDigitada, cadastro.senha) == 0)
                {
                    printf_verde("\n\tLogin bem-sucedido!");
                    printf("\n\tBem vindo! %s.", cadastro.nome);
                    *logado = 1;
                    strcpy(nomeLogin, cadastro.nome);
                    strcpy(idadeLogin, cadastro.idade);
                    fclose(lercadastro);
                    return;
                }

                else
                {
                    printf_vermelho("\n\tSenha incorreta! Tente novamente.");
                }
            }
        }

        if (loginRealizado != 1)
        {
            printf_vermelho("\n\tCPF incorreto! Tente novamente.");
        }
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
        printf_vermelho("Opção inválida. Digite 1 ou 2.\n");
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

void tempoagora(tempo *data) // função para coletar o tempo de agora e armazenar na struct.
{                            // serve para impedir o usuário de digitar uma data anterior da data de hoje

    time_t agora;    // variável do tipo time para armazenar o tempo atual em segundos desde 1970
    struct tm *info; // ponteiro para a struct da função que armazena data e hora

    time(&agora); // obtem os segundos desde 1970 e armazena na varável agora

    info = localtime(&agora); // converte os segundos para o tempo local do computador

    // armazena na struct a data em que o ponteiro *info aponta
    data->dia = info->tm_mday;        //  dia do mês (1-31)
    data->mes = info->tm_mon + 1;     // meses de (0-11) + 1 =  (1-12)
    data->ano = info->tm_year + 1900; // anos desde 1900 + 1900
    data->hora = info->tm_hour;       // hora de agora
}

int validardata(int dia, int mes, int ano)
{

    tempo data;
    tempoagora(&data);
    if (ano < data.ano || mes < 1 || mes > 12 || dia < 1) // retorna erro se a data for menor ou maior que os limites (mes 13, mes -1, dia -1, ano menor que o ano de agora)
        return 0;                                         // data invalida

    if (ano == data.ano && mes < data.mes) // no ano de agora, retorna erro se o mês for menor que o mês de agora e se o dia for anterior ao de hoje
        return 0;

    if (ano == 2025 && mes == data.mes && dia < data.dia)
        return 0;

    if (ano == 2025) // se for esse ano, só pode datas de hoje para frente
    {
        switch (mes) // break é redundante nesse switch (mes)
        {
        case 6:
        case 9:
        case 11: // casos para meses de 30 dias

            if (dia <= 30)
                return 1;

            else
                return 0;

        default: // padrão para meses de 31 dias
            if (dia <= 31)
                return 1;

            else
                return 0;
        }
    }

    if (ano > 2025)
    { // se for anos superiores, pode qualquer data dentro dos limites

        int bissexto = 0;

        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
        {
            bissexto += 1; // 1 se o ano é bissexto, 0 se nao
        }
        switch (mes)
        {
        case 02: // mesmas regras que os cases de cima, só pode datas dentro dos limites
            if (bissexto == 1 && (dia <= 29))
                return 1;

            else if (bissexto == 0 && (dia <= 28))
                return 1;

            else
                return 0;
            break;
        case 4:
        case 6:
        case 9:
        case 11:

            if (dia <= 30)
                return 1;

            else
                return 0;

        default:
            if (dia <= 31)
                return 1;

            else
                return 0;
        }
    }
    return 0;
}

void horariosvalidos(int dia, int *vet)
{
    int rd[4] = {0};

    tempo data;
    tempoagora(&data);

    int min_hora, max_hora;
    min_hora = 6;
    max_hora = 17; // só pode marcar até 17h (17h-18h)

    if (dia == data.dia)
    {
        // se for pra hoje, só pode horários depois da hora atual
        // ex: agora é 13h, só pode marcar a partir das 14h
        min_hora = data.hora + 1;

        if (min_hora > max_hora)
        {
            printf_vermelho("\nNão há horários disponíveis para hoje!\n");
            return;
        }

        // preenche o vetor rd com horários únicos, dentro do intervalo correto
        randomizar(rd, 4, min_hora, max_hora);

        int disponiveis = 0;
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
            if (rd[i] != 0)
            {
                vet[i] = rd[i];
                printf("\n%d", rd[i]);
                disponiveis++;
            }
        }

        if (disponiveis == 0)
        {
            printf_vermelho("\nNão há horários disponíveis para hoje!\n");
            return;
        }
    }
    else
    {
        // para outras datas, pode de 6 até 17
        randomizar(rd, 4, min_hora, max_hora);

        int disponiveis = 0;
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
            if (rd[i] != 0)
            {
                vet[i] = rd[i];
                printf("%d ", rd[i]);
                disponiveis++;
            }
        }
        if (disponiveis == 0)
        {
            printf_vermelho("\nNão há horários disponíveis!\n");
            return;
        }
    }
}

void lembrete(int *dia, int hora, char *nome)
{
    printf("\a"); // beep
    sleep(2);     // Tempo decorrido até aparecer a mensagem
    printf("LEMBRETE\nConsulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
           dia[0], dia[1], dia[2], hora, nome); // adicionar email
    
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

   while(nome_med > 10 || nome_med < 1)
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
    // Abre o arquivo com os agendamentos salvos e lê.
    FILE *le_dados = fopen("bin/dados_clientes.bin", "rb");

    if (le_dados == NULL)
    {
        printf_vermelho("\nNenhuma consulta agendada.\n");
        return;
    }

    int encontrado = 0; // Variavel para saber se encontrou alguma consulta.
    dados_paciente paciente;

    printf_verde("\n\n\t\t=== Consultas Agendadas ===\n\n");

    // Lê o arquivo até não encontrar mais dados.
    while (fread(&paciente, sizeof(dados_paciente), 1, le_dados) == 1)
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
        printf_vermelho("\n\tNenhuma consulta encontrada para");
        printf (" %s (CPF: %s).\n\n", nome, cpf);
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
        printf_vermelho("\nConsulta não encontrada.\n");
        return;
    }

    // Abre um arquivo para auxiliar no cancelamento de consultas.
    FILE *auxiliar_cancelar = fopen("auxiliar.bin", "wb");
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

        removerQuebraDeLinha(cadastro.cpf); // Remove quebras de linha.

        // Compara o cpf do paciente com o cpf dos cadastros e imprime a consulta agendada se os dados estiverem corretos.
        if (strcmp(cadastro.cpf, cpf) == 0)
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
        remove("auxiliar.bin");
    }
    else
    {

        // Apaga o arquivos que contem os dados de consultas e renomeia o arquivo auxiliar com o nome do antigo arquivo que armazenava os dados das consultas.
        remove("bin/dados_clientes.bin");
        rename("auxiliar.bin", "bin/dados_clientes.bin");
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
    FILE *auxiliar_reagendar = fopen("temp.bin", "wb");
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
            printf("\nInforme a data da consulta (dia/mes/ano): ");
            scanf("%d/%d/%d", &paciente.dia[0], &paciente.dia[1], &paciente.dia[2]);

          while (validardata( paciente.dia[0], paciente.dia[1], paciente.dia[2]) == 0)
        {
            printf("\n\tInforme uma data válida (dia/mês/ano): ");
            scanf("%d/%d/%d",  &paciente.dia[0], &paciente.dia[1], &paciente.dia[2]);
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
        remove("bin/dados_clientes.bin");
        rename("temp.bin", "bin/dados_clientes.bin");
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // ajustando o qsort para comparar o vetor
}

// essa função preenche o vetor rd com valores aleatórios únicos, no intervalo [min, max]
// não deixa repetir horários, diferente da antiga randomizar
void randomizar(int *rd, int tam, int min, int max)
{
    int total = max - min + 1; // total de opções

    if (total < tam) // se houver menos opções do que posições, zera tudo
    {
        for (int i = 0; i < tam; i++)
            rd[i] = 0;
        return;
    }

    int pool[32]; // no máximo 32 opções
    // pool de piscina, no caso, piscina de inteiros pseudo-aleatórios com um limite definido
    for (int i = 0; i < total; i++)
        pool[i] = min + i; // preenche a pool com todos valores possíveis

    srand(time(NULL));
    for (int i = 0; i < tam; i++)
    {
        int r = rand() % (total - i); // sorteia um índice dentro do ainda disponível
        rd[i] = pool[r];              // pega o valor sorteado
        // remove o valor já usado da pool (troca com o último disponível)
        int temp = pool[r];            // guarda temporariamente o valor sorteado
        pool[r] = pool[total - i - 1]; // coloca o último disponível no lugar do sorteado
        pool[total - i - 1] = temp;    // e coloca o sorteado no fim do pool (fora do próximo sorteio)
    }

    qsort(rd, tam, sizeof(int), compare); // ordena os horários para exibir em ordem
}

void printf_vermelho(const char *text)
{
    printf("\033[1;31m%s\033[0m", text);
    // "\033[" ativa a sequencia ANSI (formastação espciacial d textos pro terminal)
    // "1;31m", "1" = negrito,  "31m" = vermelho
    // "\033[0m" reseta o texto pro normal do terminal
}

void printf_verde(const char *text)
{
    printf("\033[1;32m%s\033[0m", text);
}

int verificaEmail(char *email)
{
    char *dominios[] = {"@gmail.com", "@hotmail.com", "@outlook.com",
                        "@discente.ufg.br", "@ufg.br"};

    size_t tamanhoemail = strlen(email); // verifica o tamanho da string passada
    // size_t é melhor para lidar com tamanho de arrays e strings

    int numerodominios = sizeof(dominios) / sizeof(dominios[0]); // calcula o numero de dominios (para caso se adicione mais)

    for (int i = 0; i < numerodominios; i++)
    {
        size_t tamanhodom = strlen(dominios[i]); // calcula o tamanho do dominio atual

        if (tamanhoemail >= tamanhodom && strcmp(email + tamanhoemail - tamanhodom, dominios[i]) == 0) // verifica o tamanho do email com o dominio, se for menor, nao verifica e retorna 0
                                                                                                       // "email + tamanhoemail - tamanhodom" retira elementos da string até onde supostamente comecaria o dominio "@" e compara com o dominio

            return 1; // encontrou domínio
    }

    return 0; // encontrou nada
}
