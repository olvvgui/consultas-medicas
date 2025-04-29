
#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include "funcoes.h"
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


int main()
{

    printf("\t=== Consultas Medicas ===\n");
    char logado;
    printf("\tVoce ja tem conta no sistema? (s/n): ");
    scanf(" %c", &logado);

    char nome[61];   // criando a string do nome com máximo de 60 caracteres
    char senha1[61]; // máximo de 60 caracteres
    char senha2[61]; // máximo de 60 caracteres
    char cpf[12];    // máximo de 11 caracteres

    if (logado == 'n')
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
        fgets(nome, sizeof(nome), stdin); /* fgets funcina melhor que o scanf para pegar string (lê espaço).
        sizeof é pra garantir que o fgts n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */
        nome[strcspn(nome, "\n")] = 0;    // remove o \n da string
        strcpy(paciente.nome,nome);

        printf("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf
        getchar();                                                 // limpa o buffer pra iniciar
        fgets(cpf, sizeof(cpf), stdin);

        while (strlen(cpf) != 11)
        { // loop que lê o cpf vê se ele é igual ou diferente de 11

            printf("\n\tSeu CPF é inválido! Digite ele novamente: ");
            scanf("%s", &cpf);
        }

        printf("\n\tDigite a sua senha: ");
        scanf("%s", &senha1);

        do
        {
            printf("\n\tDigite sua senha novamente: ");
            scanf("%s", &senha2); // verificar senha

            if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
                printf("\n\tAs senhas são diferentes! Tente novamente.\n");

        } while (strcmp(senha1, senha2) != 0); // loop até as senhas serem iguais

        removerQuebraDeLinha(cpf);
        removerQuebraDeLinha(nome);
        removerQuebraDeLinha(senha2);

        fprintf(arquivo, "%s;%s;%s;\n", cpf, nome, senha2); // escreve no arquivo
        fclose(arquivo);                                    // fecha o arquivo

        printf("\t\nParabens, voce está logado!\n\n");
    }

    FILE *arquivo = fopen("cadastro.txt", "r"); //abre o arquivo no modo leitura
    if (arquivo == NULL) //se o arquivo nao existir?
    {
        printf("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
        return 1; // encerra o programa com erro
    }

    // Variáveis para armazenar o que o usuário vai digitar
    char cpfDigitado[12];
    char senhaDigitada[61];

    // Linha lida do arquivo e controle do login
    char linha[200];
    int loginRealizado = 0;

    printf("\n\t\t=== LOGIN ===");

    // Limpeza mais robusta do buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Limpa todo o buffer

    // Entrada do nome de usuário
    printf("\n\tDigite o seu CPF: ");
    getchar();                                      // Limpa o buffer de entrada antes de usar fgets
    fgets(cpfDigitado, sizeof(cpfDigitado), stdin); // lê com segurança
    removerQuebraDeLinha(cpfDigitado);              // remove \n

    // Entrada da senha
    printf("\n\tSenha: ");
    fgets(senhaDigitada, sizeof(senhaDigitada), stdin); // lê com segurança
    removerQuebraDeLinha(senhaDigitada);                // remove \n

    // Abre o arquivo de usuários para leitura

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo))
    {

        removerQuebraDeLinha(linha); // remove \n da linha lida

        // Usa strtok para separar a string em partes: cpf, nome e senha
        // strtok divide a string onde encontra ';'
        char *cpf = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *senha2 = strtok(NULL, ";");

        // Verifica se ambas partes foram lidas com sucesso
        if (cpf != NULL && senha2 != NULL && nome != NULL)
        {

            // Compara os dados digitados com os do arquivo
            // strcmp retorna 0 se as strings forem iguais

            if (strcmp(cpfDigitado, cpf) == 0 &&
                strcmp(senhaDigitada, senha2) == 0)
            {
                loginRealizado = 1; // marca como sucesso
                printf("\n\tLogin bem-sucedido! Bem-vindo, %s.\n", nome);
                break; // para a leitura do arquivo
            }
        }
    }

    fclose(arquivo); // fecha o arquivo

    // Verifica se o login foi realizado com sucesso
    if (!loginRealizado)
    {
        printf("\n\tUsuário ou senha incorretos.");
    }
    
    int especialidade;
    char nome_medico[50];
    // Pergunta e escaneia a especialidade medica desejada.
    printf("\nSelecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n\n\tValor Digitado: ");
    scanf("%d", &especialidade);
    while (especialidade > 5 || especialidade < 1)
    {
        printf("\nEspecialidade inválida, selecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n");

        printf("\nDigite o número da especialidade desejada: ");
            scanf("%d", &especialidade);
    }
    // Testes comparando a especialidade escolhida e o nome do médico.
    if (especialidade == 1)
    {
        selecionar("Nutrólogo", "Dr. Renato Nunes", "Dra. Amanda Pinheiro", nome_medico);
        printf("Médico(a) selecionado(a): %s", nome_medico);
    }
    else if (especialidade == 2)
    {
        selecionar("Pediatra", "Dr. João Silva", "Dra. Julia Paes", nome_medico);
        printf("Médico(a) selecionado(a): %s", nome_medico);
    }
    else if (especialidade == 3)
    {
        selecionar("Ortopedista", "Dr. Paulo Junior", "Dra. Flávia Ribeiro", nome_medico);
        printf("Médico(a) selecionado(a): %s", nome_medico);
    }
    else if (especialidade == 4)
    {
        selecionar("Neurologista", "Dr. Pedro Guimaraes", "Dra. Carla Barros", nome_medico);
        printf("Médico(a) selecionado(a): %s", nome_medico);
    }
    else if (especialidade == 5)
    {
        selecionar("Oftalmologista", "Dr. Thiago Fernandes", "Dra. Tatiane Gomes", nome_medico);
        printf("Médico(a) selecionado(a): %s", nome_medico);
    }
    strcpy(paciente.medico,nome_medico);
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
    FILE *salvar_dados = fopen("dados_clientes.bin","ab");
    fwrite(&paciente,sizeof(struct dados_paciente),1,salvar_dados);
    fclose(salvar_dados);

    printf("\n\tConsulta agendada com sucesso!\n\n");

    // Funcao para ler todos os dados adicionados.
    ler_dados_agendamento();
    
    return 0; // encerra o programa com sucesso
    
}
 // Funcao temporaria para ler todos os dados salvos no arquivo.
void ler_dados_agendamento(){
    // Funcao que le todos os dados contidos no arquivo dados_clientes.bin.
    FILE *ler_dados_agendados = fopen("dados_clientes.bin","rb");
    while (fread(&paciente,sizeof(struct dados_paciente), 1, ler_dados_agendados) == 1){
         printf("Dia: %02d/%02d/%d\n",paciente.dia[0], paciente.dia[1], paciente.dia[2]);
         printf("Horario: %02d:00\n",paciente.horario);
         printf("Medico: %s\n",paciente.medico);
         printf("Observacao: %s\n",paciente.obs);

    }
fclose(ler_dados_agendados);
}
