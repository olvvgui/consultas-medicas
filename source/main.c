#include <stdio.h>
#include "main.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

// login conta admin
// cpf = 12345678901
// senha = 12345678
// email = amd@ufg.br

int main()
{
    
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(65001); // diretivas de compilação somente para windows (resolve problema de caracteres especiais)
    SetConsoleCP(65001);
#endif

    int choose = menu();
    usuario usr;

    do
    {
        switch (choose)
        {
        case 1:
            cadastrar(&usr);
            choose = menu();
            break;

        case 2:
            agendar(&usr);
            choose = menu();
            break;

        case 3:
            buscar(&usr);
            choose = menu();
            break;

        case 4:
            cancelar(&usr);
            choose = menu();
            break;

        case 5:
            reagendar(&usr);
            choose = menu();
            break;

        case 6:
            medOudia(&usr);
            choose = menu();
            break;
        }

        case 192: // limpar cadastros ultrapassdos
        atualizar_consultas();
        choose = menu();
        break;

    } while (choose != 0);
    return 0; // encerra o programa com sucesso
}
