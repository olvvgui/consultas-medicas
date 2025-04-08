#include <stdio.h>
#include <string.h>
 int main(){
   int Medicos,Especialidade;
   char Nome_Medico[50];
  //Pergunta e escaneia a especialidade medica desejada.
   printf("\nSelecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n\n\tValor Digitado: ");
   scanf( "%d", &Especialidade);
   while (Especialidade > 5 || Especialidade < 1)
   {
    printf("\nEspecialidade inválida,selecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n\n\tValor Digitado: ");
   scanf( "%d", &Especialidade);
   }
  // Testes comparando a especialidade escolhida e o nome do médico.
   if(Especialidade == 1){
    printf("\nNutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n\n\tValor Digitado: ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {
            printf("\nMédico inválido, Selecione Novamente\n\n");
            printf("\nNutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n\n\tValor Digitado: ");
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
    printf("\nPediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n\n\tValor Digitado: ");
    scanf("%d",&Medicos);   
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Pediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n\n\tValor Digitado: ");
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
   else if(Especialidade == 3){
    printf("\nOrtopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n\n\tValor Digitado: ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("\nOrtopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n\n\tValor Digitado: ");
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
   else if(Especialidade == 4){
    printf("Neurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n\n\tValor Digitado: ");
    scanf("%d",&Medicos); 
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente");
            printf("\nNeurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n\n\tValor Digitado: ");
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
   else if(Especialidade == 5){
    printf("\nOftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n\n");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente");
            printf("\nOftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n\n\tValor Digitado: ");
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
   printf("Medico disponível selecionado: %s", Nome_Medico);
   }
