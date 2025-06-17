#include <stdio.h>
#include "../menu.h"


int menu()
{
    int escolha = 0;
    printf_verde("\n\tEscolha o que deseja fazer:");
    printf("\n\t0.Sair do programa.");
    printf("\n\t1.Cadastramento de conta.");
    printf("\n\t2.Agendamento de consulta.");
    printf("\n\t3.Busca de agendamento.");
    printf("\n\t4.Cancelamento de consulta.");
    printf("\n\t5.Reagendamento de consulta.");
    printf("\n\t6.Buscar consultas por dia e medico.\n");
    printf("\n\tR: ");
    scanf("%d", &escolha);

    if (escolha == 0)
    {
        printf_verde("\n\tFinalizando programa...");
        return 0;
    }

    if (escolha != 192 && escolha < 0 || escolha > 6)
    {

        printf_vermelho("\nErro. Escolha uma opção válida.\n");
    }

    return escolha;
}

