#include <stdio.h>
#include <string.h>
 int main(){
   int Medicos,Especialidade;
   char Nome_Medico[50];
   printf("Selecione uma especialidade médica:\n1. Nutrólogo.\n2. Cirurgião Geral.\n3. Urologista.\n4. Ginecologista.\n5. Pediatra.\n6. Ortopedista.\n7. Proctologista.\n8. Neurologista\n9. Oftalmologista.\n10. Médico Clínico.\n");
   scanf( "%d", &Especialidade);
   while (Especialidade > 10 || Especialidade < 1)
   {
    printf("Especialidade inválida, selecione uma especialidade médica:\n1. Nutrólogo.\n2. Cirurgião Geral.\n3. Urologista.\n4. Ginecologista.\n5. Pediatra.\n6. Ortopedista.\n7. Proctologista.\n8. Neurologista\n9. Oftalmologista.\n10. Médico Clínico.\n");
   scanf( "%d", &Especialidade);
   }
   if(Especialidade == 1){
    printf("Nutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {
            printf("Médico inválido, Selecione Novamente\n");
            printf("Nutrólogos disponíveis:\n1. Ricardo Nunes.\n2. Adriana Lima.\n ");
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
    printf("Cirurgiões Gerais disponíveis:\n1. Paula Ribeiro.\n2. Caio Luis.\n ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Cirurgiões Gerais disponíveis:\n1. Paula Ribeiro.\n2. Caio Luis.\n ");
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
    printf("Urologistas disponíveis:\n1. Diego Fonseca.\n2. Paulo Goncalves.\n ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Urologistas disponíveis:\n1. Diego Fonseca.\n2. Paulo Goncalves.\n ");
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
    printf("Ginecologistas disponíveis:\n1. Debora Novaes.\n2. Alice Xavier.\n ");
    scanf("%d",&Medicos); 
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Ginecologistas disponíveis:\n1. Debora Novaes.\n2. Alice Xavier.\n ");
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
    printf("Pediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n ");
    scanf("%d",&Medicos);   
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Pediatras disponíveis:\n1. Raiane Silva.\n2. Pedro Carvalho.\n ");
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
    printf("Ortopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Ortopedistas disponíveis:\n1. Cristina Pereira.\n2. Pietro Martins.\n ");
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
    printf("Proctologistas disponíveis:\n1. Ruan Pedro.\n2. Vitoria Farias.\n ");
    scanf("%d",&Medicos);  
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Proctologistas disponíveis:\n1. Ruan Pedro.\n2. Vitoria Farias.\n ");
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
    printf("Neurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n ");
    scanf("%d",&Medicos); 
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Neurologistas disponíveis:\n1. Vitor Junior.\n2. Francisca Gabrielle.\n ");
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
    printf("Oftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n ");
    scanf("%d",&Medicos);
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Oftalmologistas disponíveis:\n1. Francisco Coelho.\n2. Barbara Oliveira.\n ");
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
    printf("Médicos Clínicos disponíveis:\n1. Ana Julia.\n2. Junior Moreira.\n ");
    scanf("%d",&Medicos); 
    do
    {
        if (Medicos < 1 || Medicos > 2)
        {   
            printf("Médico inválido, Selecione Novamente\n");
            printf("Médicos Clínicos disponíveis:\n1. Ana Julia.\n2. Junior Moreira.\n ");
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
   printf(" Medico escolhido = %s", Nome_Medico);
   return 0; 
}
