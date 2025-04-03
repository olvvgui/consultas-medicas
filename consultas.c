#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contarNumeros (int numero){ /*A função contarNumeros calcula e retorna a quantidade de dígitos de um número inteiro. 
    Ela trata o caso especial de 0 e utiliza um loop para dividir o número por 10 até que ele se torne 0,
    contando os dígitos no processo.*/
    
    int contador; // contador de dígitos

    if (numero == 0){ // se o número for 0, retorna 1
        return 1;
    }

    while (numero != 0) { 
    numero /= 10;
    contador++;
    } // enquanto o número não for 0, divide por 10 e incrementa o contador

    return contador; // retorna o número de dígitos


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