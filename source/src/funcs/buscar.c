#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "../main.h"

void buscar(usuario *usr)
{

    printf_verde("\n\t\t\t\t\t\t=== Buscar Agendamento ===\n");

    if (usr->autenticado != 1)
    {
        printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
        login(usr);
    }
    if (usr->autenticado == 1)
    {
        // Funcao para buscar consultas.
        buscar_consulta(usr->nome, usr->cpf);
    }
    return;
}