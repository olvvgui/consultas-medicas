#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include "bibliotecas/funcoes.c"
#include "bibliotecas/funcoes.h"

int main() {
    int logado = 0; // Estado de login (0 = não logado)
    int escolha;

    do {
        escolha = menu();
        switch (escolha) {

            case 1: cadastrar_conta(&logado); break;

            case 2: agendar_consulta(&logado); break;

            case 3: buscar_consulta(&logado); break;
                // ... demais casos
            case 0: printf("Saindo...\n"); break;

            default: printf("Opção inválida!\n");
        }

    } while (escolha != 0);

    return 0;
}
