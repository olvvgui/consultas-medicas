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

struct paciente//Estrutura para guardar as infomrações
{
    int dia[3];
    int horario;
    char nome[61];
    char obs[100];

};

struct paciente paciente; //Inicializando uma estrutura

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

    
    int Medicos,Especialidade;
    char Nome_Medico[50];
   //Pergunta e escaneia a especialidade medica desejada.
    printf("\nSelecione uma especialidade médica:\n1. Nutrólogo.\n2. Cirurgião Geral.\n3. Urologista.\n4. Ginecologista.\n5. Pediatra.\n6. Ortopedista.\n7. Proctologista.\n8. Neurologista\n9. Oftalmologista.\n10. Médico Clínico.\n\n");
    scanf( "%d", &Especialidade);
    while (Especialidade > 10 || Especialidade < 1)
    {
     printf("\nEspecialidade inválida, selecione uma especialidade médica:\n1. Nutrólogo.\n2. Cirurgião Geral.\n3. Urologista.\n4. Ginecologista.\n5. Pediatra.\n6. Ortopedista.\n7. Proctologista.\n8. Neurologista\n9. Oftalmologista.\n10. Médico Clínico.\n\n");
    scanf( "%d", &Especialidade);
    }
   // Testes comparando a especialidade escolhida e o nome do médico.
    if(Especialidade == 1){
     printf("\nNutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n\n");
     scanf("%d",&Medicos);
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nNutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n\n");
     scanf("%d",&Medicos);
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Ricardo Nunes: Nutrólogo.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Adriana Lima: Nutrólogo.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 2){
     printf("\nCirurgiões Gerais disponíveis:\n1. Paula Ribeiro.\n2. Caio Luis.\n\n");
     scanf("%d",&Medicos);
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nCirurgiões Gerais disponíveis:\n1. Paula Ribeiro.\n2. Caio Luis.\n\n");
     scanf("%d",&Medicos);
             
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Paula Ribeiro: Cirurgiã Geral.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Caio Luis: Cirurgião Geral.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 3){
     printf("\nUrologistas disponíveis:\n1. Diego Fonseca.\n2. Paulo Goncalves.\n\n");
     scanf("%d",&Medicos);
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nUrologistas disponíveis:\n1. Diego Fonseca.\n2. Paulo Goncalves.\n\n");
     scanf("%d",&Medicos);
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Diego Fonseca: Urologista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Paulo Goncalves: Urologista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 4){
     printf("\nGinecologistas disponíveis:\n1. Debora Novaes.\n2. Alice Xavier.\n\n");
     scanf("%d",&Medicos); 
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nGinecologistas disponíveis:\n1. Debora Novaes.\n2. Alice Xavier.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Debora Novaes: Ginecologista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Alice Xavier: Ginecologista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 5){
     printf("\nPediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n\n");
     scanf("%d",&Medicos);   
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\\nn");
             printf("Pediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Raiane Silva: Pediatra.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Pedro Carvalho: Pediatra.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 6){
     printf("\nOrtopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n\n");
     scanf("%d",&Medicos);
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nOrtopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n ");
             scanf("%d",&Medicos);
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Cristina Pereira: Ortopedista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Pietro Martins: Ortopedista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 7){
     printf("\nProctologistas disponíveis:\n1. Ruan Pedro.\n2. Vitoria Farias.\n\n");
     scanf("%d",&Medicos);  
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nProctologistas disponíveis:\n1. Ruan Pedro.\n2. Vitoria Farias.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Ruan Pedro: Proctologista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Vitoria Farias: Proctologista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 8){
     printf("\nNeurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n\n");
     scanf("%d",&Medicos); 
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nNeurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Vitor Junior: Neurologista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Francisca Gabrielle: Neurologista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 9){
     printf("\nOftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n\n");
     scanf("%d",&Medicos);
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nOftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Francisco Coelho: Oftalmologista.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Barbara Oliveira: Oftalmologista.\n");
         break;
     default:
         break;
     }
    }
    else if(Especialidade == 10){
     printf("\nMédicos Clínicos disponíveis:\n1. Ana Julia.\n2. Junior Moreira.\n\n");
     scanf("%d",&Medicos); 
     do
     {
         if (Medicos < 1 || Medicos > 2)
         {   
             printf("\nMédico inválido, Selecione Novamente\n\n");
             printf("\nMédicos Clínicos disponíveis:\n1. Ana Julia.\n2. Junior Moreira.\n\n");
     scanf("%d",&Medicos);    
         }}while (Medicos < 1 || Medicos > 2);
     switch (Medicos)
     {
     case 1:
         strcpy(Nome_Medico, "Ana Julia: Médica Clínica.\n");
         break;
     case 2:
         strcpy(Nome_Medico, "Junior Moreira: Médico Clínico.\n");
         break;
     default:
         break;
     }
    }
    
    getchar ( );
     
     //aloca os dados da consulta agendada pelo paciente
     int dia, mes, ano, hora, medicos; //declaracao de variaveis
     int i; // contador do loop
 
     //char confirmacao[3];
 
     //system("clear"); //Limpando o terminal - linux
     //system("cls");//Limpando o terminal - windows
     printf("\nInforme a data da consulta (dia mês ano): "); 
     scanf(" %d %d %d", &dia, &mes, &ano);
     paciente.dia[0] = dia; paciente.dia[1] = mes; paciente.dia[2] = ano;
 
     //Lendo e colocando o dia, o mes e o ano dentro do vetor
     printf("\nHorarios disponiveis:\n\n");
     printf("\n01 - 8:00\n02 - 10:00\n03 - 14:00\n\nR: "); scanf("%d", &hora);
 
     switch (hora) {
         case 01:
             paciente.horario = 8;
 
         case 02:
             paciente.horario = 10; //nao usar break
 
         case 03:
             paciente.horario = 14;
 
     } // aloca o horario escolhido pelo paciente na struct
 
 
 
     printf("\n\nDia: %02d/%02d/%d\nHorario: %d:00\n", paciente.dia[0], paciente.dia[1], paciente.dia[2], paciente.horario, paciente.nome);
     printf("Medico escolhido = %s\n", Nome_Medico);

     printf("\n\tConsulta agendada com sucesso!\n\n");
return 0;  // encerra o programa com sucesso
}
