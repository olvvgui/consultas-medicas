#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../paciente.h"

void cadastrarpaciente(cadastro_save cad, usuario *usr)
{
    if (usr->autenticado == 1)
    {

        return;
    }
    cadastro_save cadastro;
    FILE *arquivo;
    arquivo = fopen("source/bin/cadastro.bin", "ab"); // abrindo (criando) o arquivo em modo append (adicionar)

    if (arquivo == NULL)
    {
        printf("\nNao foi possivel abrir o arquivo.");
        return; // fecha o programa se o arquivo não abrir
    }

    fwrite(&cad, sizeof(cadastro_save), 1, arquivo); // escreve no arquivo
    fclose(arquivo);                                 // fecha o arquivo

    usr->autenticado = 0;
    strcpy(usr->nome, cad.nome);
    strcpy(usr->idade, cad.idade);
    strcpy(usr->cpf, cad.cpf);
}
void login(usuario *usr)
{
    if (usr->autenticado == 1)
    {

        printf("Login já realizado!");

        return;
    }

    char cpfDigitado[12];
    char senhaDigitada[21];
    char nomeLogin[61];
    char idadeLogin[4];
    int cpfAchado = 0;
    cadastro_save cadastro;

    printf_verde("\n\t\t=== LOGIN ===\n");

    while (1)
    {

        printf("\n\tDigite o seu CPF (ou digite 'sair' para fechar o programa): ");
        scanf("%s", cpfDigitado);
        removerQuebraDeLinha(cpfDigitado);

        if (strcmp(cpfDigitado, "sair") == 0)
        {
            printf_verde("\n\tFechando...");
            exit(0);
            break;
        }

        FILE *lercadastro = fopen("source/bin/cadastro.bin", "rb");
        if (lercadastro == NULL)
        {
            printf_vermelho("\n\tErro: não foi possível abrir o arquivo de usuários.\n");
            exit(1);
        }

        while (fread(&cadastro, sizeof(cadastro_save), 1, lercadastro) == 1)
        {

            if (strcmp(cpfDigitado, cadastro.cpf) == 0) // busca o cpf
            {
                cpfAchado = 1;
                break;
            }
        }

        while (1)
        {
            if (cpfAchado == 1)
            { // Entrada da senha

                printf("\n\tSenha: ");
                getchar();
                scanf("%20s", senhaDigitada);
                removerQuebraDeLinha(senhaDigitada);

                // Compara os dados digitados com os do arquivo. Strcmp retorna 0 se as strings forem iguais

                removerQuebraDeLinha(cadastro.senha);
                if (strcmp(senhaDigitada, cadastro.senha) == 0)
                {
                    printf_verde("\n\tLogin bem-sucedido!");
                    printf("\n\tBem vindo! %s.", cadastro.nome);

                    usr->autenticado = 1;

                    strcpy(usr->nome, cadastro.nome);

                    strcpy(usr->idade, cadastro.idade);

                    strcpy(usr->cpf, cpfDigitado);

                    fclose(lercadastro);
                    return;
                }

                else
                {
                    printf_vermelho("\n\tSenha incorreta! Tente novamente.");
                }
            }
        }

        if (cpfAchado != 1)
        {
            printf_vermelho("\n\tCPF incorreto! Tente novamente.");
        }
    }
}

int verificaEmail(char *email)
{
    char *dominios[] = {"@gmail.com", "@hotmail.com", "@outlook.com",
                        "@discente.ufg.br", "@ufg.br"};

    size_t tamanhoemail = strlen(email); // verifica o tamanho da string passada
    // size_t é melhor para lidar com tamanho de arrays e strings

    int numerodominios = sizeof(dominios) / sizeof(dominios[0]); // calcula o numero de dominios (para caso se adicione mais)

    for (int i = 0; i < numerodominios; i++)
    {
        size_t tamanhodom = strlen(dominios[i]); // calcula o tamanho do dominio atual

        if (tamanhoemail >= tamanhodom && strcmp(email + tamanhoemail - tamanhodom, dominios[i]) == 0) // verifica o tamanho do email com o dominio, se for menor, nao verifica e retorna 0
                                                                                                       // "email + tamanhoemail - tamanhodom" retira elementos da string até onde supostamente comecaria o dominio "@" e compara com o dominio

            return 1; // encontrou domínio
    }

    return 0; // encontrou nada
}

int verificaCPF(char *cpf)
{
    FILE *lercadastro = fopen("source/bin/cadastro.bin", "rb");
    if (lercadastro == NULL)
    {
        return 0; // arquivo não existe ou está vazio
    }

    cadastro_save cadastro;

    while (fread(&cadastro, sizeof(cadastro_save), 1, lercadastro) == 1)
    {
        if (strcmp(cpf, cadastro.cpf) == 0) // busca o cpf
        {
            fclose(lercadastro);
            return 1; // cpf já cadastrado
        }
    }

    fclose(lercadastro);
    return 0; // cpf não foi cadastrado ainda
}