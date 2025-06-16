
#include <locale.h>
#include <stdio.h>  // para printf, fgets, fopen, etc
#include <string.h> // para manipulação de strings: strcmp, strtok, etc
#include <stdlib.h> // para funções gerais (como exit, malloc, etc se usadas futuramente)
#include <time.h>
#include "../main.h"

//buscar por medico ou por dia
void medOudia(usuario *usr)
{
    printf_verde("\n\t\t=== Buscar Consultas ===\n");

    int escolha;

    printf("\n\tComo deseja buscar as consultas:\n1. Pesquisar por nome do médico.\n2. Pesquisar por consulta marcadas no dia.\nR: ");
    scanf("%d", &escolha);
    getchar(); // Limpar buffer

    if (escolha == 1)
    {

        // Funcao para ver todas as consultas agendadas em um determinado medico.
        ver_consultas_medico();
    }
    else if (escolha == 2)
    {

        // Funcao para ver todas as consultas agendadas em determinado dia.
        ver_consultas_no_dia();
        
    }
    return;
}