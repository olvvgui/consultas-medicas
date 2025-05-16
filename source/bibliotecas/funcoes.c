#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

int menu()
{
    int escolha = 0;
    printf("\tEscolha o que deseja fazer:");
    printf("\n\t0.Sair do programa.");
    printf("\n\t1.Cadastramento de conta.");
    printf("\n\t2.Agendamento de consulta.");
    printf("\n\t3.Busca de agendamento.");
    printf("\n\t4.Cancelamento de consulta.");
    printf("\n\t5.Reagendamento de consulta.\n\n");
    scanf("%d", &escolha);

    if (escolha == 0)
    {
        return 0;
    }

    if (escolha < 0 || escolha > 5)
    {

        printf("Erro. Escolha uma opção válida.\n");
        menu();
    }

    return escolha;
}

void login(char cpfDigitado[12], char senhaDigitada[21], char nomeLogin[61], char idadeLogin[4], int *logado)
{
    printf("\n\t\t=== LOGIN ===");

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
            printf("\n\tFechando...");
            exit(0);
            break;

        }

        FILE *lercadastro = fopen("bin/cadastro.bin", "rb");
        if (lercadastro == NULL)
        {
            printf("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
            exit (1);
        }

        while (fread(&cadastro, sizeof(struct cadastro_save), 1, lercadastro) == 1)
        {

            if (strcmp(cpfDigitado, cadastro.cpf) == 0) // busca o cpf
            {
                loginRealizado = 1;
                break;
            }
        }

        
        while (1){
        if (loginRealizado == 1){ // Entrada da senha

             printf("\n\tSenha: ");
             getchar();
             scanf("%20s", senhaDigitada);
             removerQuebraDeLinha(senhaDigitada);

             // Compara os dados digitados com os do arquivo. Strcmp retorna 0 se as strings forem iguais

             removerQuebraDeLinha (cadastro.senha);
             if (strcmp(senhaDigitada, cadastro.senha) == 0){
                 printf("\n\tLogin bem-sucedido! Bem-vindo, %s.", cadastro.nome);
                 *logado = 1;
                 strcpy(nomeLogin, cadastro.nome);
                 strcpy(idadeLogin, cadastro.idade);
                 fclose(lercadastro);
                 return;
            }

            else
            {
                 printf("\n\tSenha incorreta! Tente novamente.");
            }
        }
        
    }
        

     if (loginRealizado != 1){
         printf("\n\tCPF incorreto! Tente novamente.");
        }
    
    }
}
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50])
{
    int escolha;
    printf("Escolha um %s:\n", selecao); //variavel de mesmo valor
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

void removerQuebraDeLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void verificaData(int dta[3]) {
    while(dta[0]>31 || dta[1]>12 || dta[2]<2025){
        printf("Data invalida. Tente novamente: (dia,mes,ano)\n"); scanf("%d %d %d",&dta[0],&dta[1],&dta[2]);
    }
}

void verificaHorario(int *escolha){
        while(*escolha != 1 && *escolha != 2 && *escolha != 3){
            printf("Horario invalido. Tente novamente: ");  scanf("%d", &*escolha);
        }
    }

void lembrete(int *dia,int hora,char *nome) {
    for(int i = 0;  i<3;  i++){//Mostra a mensagem 3 vezes
        sleep(10);//Tempo decorrido até aparecer a mensagem
        printf("LEMBRETE\nConsulta dia %02d/%02d/%d as %d:00\nMedico: %s\nAtt. Hospital\n",
            dia[0],dia[1],dia[2],hora,nome);
        //system("pause");//presisonar qualquer tecla para fechar a mensagem
        //system("cls");//limpar a tela
    }
}


