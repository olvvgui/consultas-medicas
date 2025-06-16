#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "../main.h"

void cadastrar(usuario* usr)
{
    cadastro_save cadastro;

    char senha1[21]; // máximo de 60 caracteres
    char senha2[21]; // máximo de 60 caracteres

    printf_verde("\n\t\t=== SIGN IN ===\n");

    getchar(); // limpa o buffer pra iniciar

    printf("\n\tDigite o seu nome e sobrenome: ");
    fgets(cadastro.nome, sizeof(cadastro.nome), stdin);
    removerQuebraDeLinha(cadastro.nome);

    /* fgets funcina melhor que o scanf para pegar string (lê espaço).
    sizeof é pra garantir que o fgts n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */

    do
    {
        printf("\n\tDigite o seu cpf no formato"); // digitar cpf
        printf_vermelho(" (00000000000): ");
        scanf("%s", cadastro.cpf);
        removerQuebraDeLinha(cadastro.cpf);


        // loop que lê o cpf vê se ele é igual ou diferente de 11 ou se ele já foi cadastrado

        if (verificaCPF(cadastro.cpf) == 1)
        {
            printf_vermelho("\n\tEste CPF já está cadastrado no sistema!");
        }

        if (strlen(cadastro.cpf) != 11)
        {
            printf_vermelho("\n\tSeu CPF é inválido!\n");
        }
    }
    while (strlen(cadastro.cpf) != 11 || verificaCPF(cadastro.cpf) == 1);


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

        if (strcmp(senha1, senha2) != 0)
            printf_vermelho("\n\tAs senhas são diferentes!");
    }
    while (strcmp(senha1, senha2) != 0); // loop até as senhas serem iguais e maiores que 8 caracteres
    removerQuebraDeLinha(senha2);

    strcpy(cadastro.senha, senha2);

    printf("\n\tDigite a sua idade: ");

    scanf("%s", cadastro.idade);

    removerQuebraDeLinha(cadastro.idade);

    cadastrarpaciente(cadastro, usr);

    printf_verde("\n\tParabens, você está cadastrado! O que deseja fazer agora?\n\n");
    return;
}
