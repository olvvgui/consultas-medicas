#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contarNumeros (int numero){
    
    int contador;

    if (numero == 0){
        return 1;
    }

    while (numero != 0) {
    numero /= 10;
    contador++;
    }

    return contador;


}

int main ( ){

  char logado;
  printf("\tVocê já tem conta no sistema? (s/n)");
  scanf ("|%d", &logado);

  if (logado == 's') {

      printf ("\n\t\tLOGIN\n");

     char nome [61]; // criando a sting do nome com máximo de 60 caracteres
     char senha1 [61]; // máximo de 60 caracteres 
     char senha2 [61]; // máximo de 60 caracteres 
     int cpf;

     printf ("\tDigite o seu nome e sobrenome: ");
     fgets(nome, sizeof(nome), stdin); /* fgets funcina melhor que o scanf para pegar string (lê espaço). 
     sizeof é pra garantir que o fgtes n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */
    
     printf ("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf
     scanf ("%d", &cpf);

     do {

         printf ("\n\tSeu CPF é inválido! Digite ele novamente: ");
         scanf ("%d", &cpf);

     } while (contarNumeros(cpf) == 11);


     printf ("\n\tDigite a sua senha: ");
     scanf ("%s", &senha1);

     do {
         printf ("\n\tDigite sua senha novamente: ");
         scanf ("%s", &senha2); // verificar senha

         if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
             printf ("\n\tAs senhas são diferentes! Tente novamente.\n");

        } while(strcmp(senha1, senha2) !=0); // loop até as senhas serem iguais

     printf ("\t\nPárabens, você está logado!\n\n");

    }



}