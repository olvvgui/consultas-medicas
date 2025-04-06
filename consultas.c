#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main ( ){

  printf ("\t===Consultas Médicas===\n");
  char logado;
  printf("\tVocê já tem conta no sistema? (s/n): ");
  scanf(" %c", &logado);

  if (logado == 'n') {

      FILE *arquivo; 
        arquivo = fopen ("cadastro.txt", "a"); // abrindo (criando) o arquivo em modo append (adicionar)

        if (arquivo == NULL) {
            return 1; // fecha o programa se o arquivo não abrir
        }

      printf ("\n\t\tLOGIN\n");

     char nome [61]; // criando a sting do nome com máximo de 60 caracteres
     char senha1 [61]; // máximo de 60 caracteres 
     char senha2 [61]; // máximo de 60 caracteres 
     char cpf [12]; // máximo de 11 caracteres

     getchar(); // limpa o buffer pra iniciar

     printf ("\n\tDigite o seu nome e sobrenome: ");
     fgets(nome, sizeof(nome), stdin); /* fgets funcina melhor que o scanf para pegar string (lê espaço). 
     sizeof é pra garantir que o fgtes n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */
     nome [strcspn(nome, "\n")] = 0;// remove o \n da string

     printf ("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf
     scanf ("%s", &cpf);

     while (strlen(cpf) != 11) { // loop que lê o cpf vê se ele é igual ou diferente de 11

           printf ("\n\tSeu CPF é inválido! Digite ele novamente: ");
              scanf ("%s", &cpf);

     }


     printf ("\n\tDigite a sua senha: ");
     scanf ("%s", &senha1);

     do {
         printf ("\n\tDigite sua senha novamente: ");
         scanf ("%s", &senha2); // verificar senha

         if (strcmp(senha1, senha2) != 0) // o terminal imprime essa frase quando as senhas são diferentes
             printf ("\n\tAs senhas são diferentes! Tente novamente.\n");

        } while(strcmp(senha1, senha2) !=0); // loop até as senhas serem iguais

        fprintf (arquivo, "\nNome: %s\nCPF: %s\nSenha: %s\n", nome, cpf, senha2); // escreve no arquivo
        fclose (arquivo); // fecha o arquivo

     printf ("\t\nPárabens, você está logado!\n\n");

    }

}
