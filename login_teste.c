#include <stdio.h>      // para printf, fgets, fopen, etc
#include <string.h>     // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h>     // para funções gerais (como exit, malloc, etc se usadas futuramente)

// Essa função remove o '\n' que o fgets captura do teclado.
// Exemplo: se você digita "joao", o fgets salva "joao\n", o que atrapalha a comparação.
// Essa função localiza o '\n' e troca por '\0', o caractere de fim de string.
void removerQuebraDeLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    // Variáveis para armazenar o que o usuário vai digitar
    char usuarioDigitado[50];
    char senhaDigitada[50];

    // Linha lida do arquivo e controle do login
    char linha[100];
    int loginRealizado = 0;

    printf("=== LOGIN ===\n");

    // Entrada do nome de usuário
    printf("Usuário: ");
    fgets(usuarioDigitado, sizeof(usuarioDigitado), stdin);  // lê com segurança
    removerQuebraDeLinha(usuarioDigitado);                    // remove \n

    // Entrada da senha
    printf("Senha: ");
    fgets(senhaDigitada, sizeof(senhaDigitada), stdin);       // lê com segurança
    removerQuebraDeLinha(senhaDigitada);                      // remove \n

    // Abre o arquivo de usuários para leitura
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: não foi possível abrir o arquivo de usuários.\n");
        return 1;  // encerra o programa com erro
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        char usuarioArquivo[50], senhaArquivo[50];

        removerQuebraDeLinha(linha);  // remove \n da linha lida

        // Usa strtok para separar a string em partes: usuário e senha
        // strtok divide a string onde encontra ':'
        char *usuario = strtok(linha, ":");     // primeira parte
        char *senha = strtok(NULL, ":");        // segunda parte

        // Verifica se ambas partes foram lidas com sucesso
        if (usuario != NULL && senha != NULL) {
            strcpy(usuarioArquivo, usuario);  // copia o nome
            strcpy(senhaArquivo, senha);      // copia a senha

            // Compara os dados digitados com os do arquivo
            // strcmp retorna 0 se as strings forem iguais
            if (strcmp(usuarioDigitado, usuarioArquivo) == 0 &&
                strcmp(senhaDigitada, senhaArquivo) == 0) {
                loginRealizado = 1;  // marca como sucesso
                break;               // para a leitura do arquivo
            }
        }
    }

    fclose(arquivo);  // fecha o arquivo

    // Verifica se o login foi realizado com sucesso
    if (loginRealizado) {
        printf("Login bem-sucedido! Bem-vindo, %s.\n", usuarioDigitado);
    } else {
        printf("Usuário ou senha incorretos.\n");
    }

    return 0;  // encerra o programa com sucesso
}
