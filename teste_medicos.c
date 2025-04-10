#include <stdio.h>
#include <string.h>
//Recebe especialidade médica, nomes dos médicos, e no fim retorna o nome do médico selecionado.
void selecionar(char especialidade[50], char med1[50], char med2[50], char nome_medico[50]) {
    int escolha;
    int medico;
    printf("Escolha um %s:\n",especialidade);
    printf("\n1. %s\n", med1);
    printf("2. %s\n\n\tValor digitado: ", med2);
    scanf("%d", &escolha);
    while (escolha < 1 || escolha > 2) {
        printf("Opção inválida. Digite 1 ou 2.\n");
        printf("Escolha um %s:\n",especialidade);
        printf("1. %s\n", med1);
        printf("2. %s\n", med2);
        scanf("%d", &escolha);
        }
        switch(escolha){
      case 1:
      strcpy(nome_medico, med1);
      break;
      case 2:
      strcpy(nome_medico, med2);
      break;
      }
    }
 int main(){
   int especialidade;
   char nome_medico[50];
  //Pergunta e escaneia a especialidade medica desejada.
   printf("\nSelecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n\n\tValor Digitado: ");
   scanf( "%d", &especialidade);
   while (especialidade > 5 || especialidade < 1)
   {
    printf("\nEspecialidade inválida,selecione uma especialidade médica:\n1. Nutrólogo.\n2. Pediatra.\n3. Ortopedista.\n4. Neurologista.\n5. Oftalmologista.\n\n\tValor Digitado: ");
   scanf( "%d", &especialidade);
   }
  // Testes comparando a especialidade escolhida e o nome do médico.
   if(especialidade == 1){
      selecionar("Nutrólogo","Dr. Renato Nunes","Dra. Amanda Pinheiro",nome_medico);
      printf("Médico(a) selecionado(a): %s",nome_medico);
      }
      else if(especialidade == 2){
      selecionar("Pediatra","Dr. João Silva","Dra. Julia Paes",nome_medico);
      printf("Médico(a) selecionado(a): %s",nome_medico);
      }
     else if(especialidade == 3){
      selecionar("Ortopedista","Dr. Paulo Junior","Dra. Flávia Ribeiro",nome_medico);
      printf("Médico(a) selecionado(a): %s",nome_medico);
      }
     else if(especialidade == 4){
      selecionar("Neurologista","Dr. Pedro Guimaraes","Dra. Carla Barros",nome_medico);
      printf("Médico(a) selecionado(a): %s",nome_medico);
      }
     else if(especialidade == 5){
      selecionar("Oftalmologista","Dr. Thiago Fernandes","Dra. Tatiane Gomes",nome_medico);
      printf("Médico(a) selecionado(a): %s",nome_medico);
      }
      }
