#include <locale.h>
#include <stdio.h>      // para printf, fgets, fopen, etc
#include <string.h>     // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h>     // para funções gerais (como exit, malloc, etc se usadas futuramente)

// Essa função remove o '\n' que o fgets captura do teclado.
// Exemplo: se você digita "joao", o fgets salva "joao\n", o que atrapalha a comparação.
// Essa função localiza o '\n' e troca por '\0', o caractere de fim de string.
void removerQuebraDeLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


int main ( ){

  printf ("\t=== Consultas Médicas ===\n");
  char logado;
  printf("\tVocê já tem conta no sistema? (s/n): ");
  scanf(" %c", &logado);


  char nome [61]; // criando a sting do nome com máximo de 60 caracteres
  char senha1 [61]; // máximo de 60 caracteres 
  char senha2 [61]; // máximo de 60 caracteres 
  char cpf [12]; // máximo de 11 caracteres

  if (logado == 'n') {

      FILE *arquivo; 
        arquivo = fopen ("cadastro.txt", "a"); // abrindo (criando) o arquivo em modo append (adicionar)

        if (arquivo == NULL) {
            return 1; // fecha o programa se o arquivo não abrir
        }

      printf ("\n\t\t=== SING IN ===\n");


     getchar(); // limpa o buffer pra iniciar

     printf ("\n\tDigite o seu nome e sobrenome: ");
     fgets(nome, sizeof(nome), stdin); /* fgets funcina melhor que o scanf para pegar string (lê espaço). 
     sizeof é pra garantir que o fgtes n ultrapasse 60 caracteres. e o stdin define o fluxo de entrada padrão */
     nome [strcspn(nome, "\n")] = 0;// remove o \n da string

     printf ("\n\tDigite o seu cpf no formato (00000000000): "); // digitar cpf
     getchar(); // limpa o buffer pra iniciar
     fgets(cpf, sizeof(cpf), stdin);

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

        removerQuebraDeLinha(cpf);
        removerQuebraDeLinha (nome);
        removerQuebraDeLinha(senha2);

        fprintf (arquivo, "%s;%s;%s;\n", cpf, nome, senha2); // escreve no arquivo
        fclose (arquivo); // fecha o arquivo

     printf ("\t\nPárabens, você está logado!\n\n");

    }

    FILE *arquivo = fopen("cadastro.txt", "r");
    if (arquivo == NULL) {
        printf("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
        return 1;  // encerra o programa com erro
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
    while ((c = getchar()) != '\n' && c != EOF); // Limpa todo o buffer

    // Entrada do nome de usuário
    printf("\n\tDigite o seu CPF: ");
    getchar(); // Limpa o buffer de entrada antes de usar fgets
    fgets(cpfDigitado, sizeof(cpfDigitado), stdin);  // lê com segurança
    removerQuebraDeLinha(cpfDigitado);                    // remove \n

    // Entrada da senha
    printf("\n\tSenha: ");
    fgets(senhaDigitada, sizeof(senhaDigitada), stdin);       // lê com segurança
    removerQuebraDeLinha(senhaDigitada);                      // remove \n

    // Abre o arquivo de usuários para leitura
   

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {

        removerQuebraDeLinha(linha);  // remove \n da linha lida

        // Usa strtok para separar a string em partes: cpf, nome e senha
        // strtok divide a string onde encontra ';'
        char *cpf = strtok(linha, ";");     
        char *nome = strtok(NULL, ";");
        char *senha2 = strtok(NULL, ";");      

        // Verifica se ambas partes foram lidas com sucesso
        if (cpf != NULL && senha2 != NULL && nome != NULL) {

            // Compara os dados digitados com os do arquivo
            // strcmp retorna 0 se as strings forem iguais
            if (strcmp(cpfDigitado, cpf) == 0 &&
                strcmp(senhaDigitada, senha2) == 0) {
                loginRealizado = 1;  // marca como sucesso
                printf("\n\tLogin bem-sucedido! Bem-vindo, %s.", nome);
                break;               // para a leitura do arquivo
            }
        }
    }

    fclose(arquivo);  // fecha o arquivo

    // Verifica se o login foi realizado com sucesso
    if (!loginRealizado) {
        printf("\n\tUsuário ou senha incorretos.");
    }

    return 0;  // encerra o programa com sucesso
    
}
