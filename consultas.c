#include <stdio.h>
#include <string.h>

int main ( ){

    printf ("\t\tLOGIN\n");

    char nome [61]; // criando a sting do nome com máximo de 60 caracteres
    char senha1 [61]; // máximo de 60 caracteres 
    char senha2 [61]; // máximo de 60 caracteres 
    int cpf;

    printf ("\tDigite o seu nome e sobrenome: ");
    fgets(nome, sizeof(nome), stdin); /* fgets funcina melhor que o scanf para pegar string (lê espaço). 
    sizeof é pra garantir que o fgtes n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */
    
    printf ("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf
    scanf ("%d", &cpf);

    printf ("\n\tDigite a sua senha: ");
    scanf ("%s", &senha1);

    do {
        printf ("\n\tDigite sua senha novamente: ");
        scanf ("%s", &senha2); // verificar senha

        if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
           printf ("\t\nAs senhas são diferentes! Tente novamente.\n");

    } while(strcmp(senha1, senha2) !=0); // loop até as senhas serem iguais

    printf ("\t\nPárabens, você está logado!\n\n");


}