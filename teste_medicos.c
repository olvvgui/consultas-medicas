#include <stdio.h>
int main(){
  int Medicos;
  printf("Escolha o médico responsável de acordo com o número:\n1. Paulo Roberto     /  Nutrólogo.\n2. José Moura        /  Cirurgião Geral.\n3. Rodrigo Coentrão  /  Urologista.\n4. Paula Pereira     /  Ginecologista.\n5. Fernanda Silva    /  Pediatra.\n6. Flavia Nunes      /  Ortopedista.\n7. Fabricio Mendes   /  Proctologista.\n8. Bruna Fernandes   /  Neurologista.\n9. Bruno Silva       /  Oftalmologista.\n10. Alex Jonas       /  Médico Clínico.\n");
  
  scanf( "%d", &Medicos );
  switch ( Medicos )
  {
      case 1 :
      printf("O médico escolhido foi Paulo Roberto  /  Nutrólogo\n");
      break;
      case 2 :
      printf("O médico escolhido foi José Moura  /  Cirurgião Geral\n");
      break;
      case 3 :
      printf("O médico escolhido foi Rodrigo Carvalho  /  Urologista\n");
      break;
      case 4 :
      printf("O médico escolhido foi Paula Pereira  /  Ginecologista\n");
      break;
      case 5 :
      printf("O médico escolhido foi Fernanda Silva  /  Pediatra\n");
      break;
      case 6 :
      printf("O médico escolhido foi Flavia Nunes  /  Ortopedista\n");
      break;
      case 7 :
      printf("O médico escolhido foi Fabricio Mendes  /  Proctologista\n");
      break;
      case 8 :
      printf("O médico escolhido foi Bruna Fernandes  /  Neurologista\n");
      break;
      case 9 :
      printf("O médico escolhido foi Bruno Silva  /  Oftalmologist\n");
      break;
      case 10 :
      printf("O médico escolhido foi Alex Jonas  /  Médico Clínico\n");
      break;
  }
  
  return 0;

  }
