#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "../main.h"

void reagendar(usuario *usr)
{
    printf_verde("\n\t\t\t\t\t\t=== Reagendamento de Consulta ===\n");
    if (usr->autenticado != 1)
    {
        printf_vermelho("\n\tÉ necessário fazer login primeiro.\n");
        login(usr);
    }
    if (usr->autenticado == 1)
    {

        // Funcao para reagendar consulta.
        reagendar_consulta(usr->cpf);
    }

    return;
}