	x
### **Estruturas de Dados (`struct`)**

1. `dados_paciente`: Esta estrutura armazena informações sobre uma única consulta médica.
    
    - `dia[3]`: Um vetor de inteiros para armazenar a data ( dia, mês e ano).
    - `horario`: Um número inteiro para o horário da consulta.
    - `nome[61]`: Um vetor de caracteres para o nome do paciente.
    - `obs[100]`: Um vetor de caracteres para quaisquer observações ou anotações.
    - `medico[100]`: Um vetor de caracteres para o nome do médico.
2. `cadastro_save`: Esta estrutura armazena os dados de cadastro de uma conta de usuário/paciente.
    - `nome[61]`: O nome completo do usuário.
    - `senha[21]`: A senha do usuário.
    - `cpf[12]`: O CPF do usuário. O tamanho 12 permite 11 dígitos mais o caractere nulo (`\0`) que finaliza a string.
    - `idade[4]`: A idade do usuário, armazenada como texto (string).
    - `email[61]`: O endereço de e-mail do usuário.
3. `tempo`: Uma estrutura para lidar com os componentes de data e hora de forma separada.
    
    - `dia`, `mes`, `ano`: Inteiros para dia, mês e ano.
    - `hora`: Inteiro para a hora.


---

#### **Gerenciamento de Usuário e Conta**

- `menu()`: Exibe um menu de opções para o usuário e retorna a sua escolha.
- `cadastrarpaciente()`: Realiza a criação de uma nova conta de paciente.
- `login()`: Gerencia o processo de login do usuário.
- `verificaEmail()`: Valida se um endereço de e-mail possui um domínio válido.

#### **Gerenciamento de Consultas**

- `selecionar()`: Uma função usada para escolher um médico.
- `horariosvalidos()`: Mostra os horários de consulta disponíveis para uma determinada data.
- `lembrete()`: Simula o envio de um lembrete de consulta para o e-mail do paciente.
- `buscar_consulta()`: Busca por uma consulta já existente.
- `reagendar_consulta()`: Realiza o reagendamento de uma consulta.
- `cancelar_consulta()`: Realiza o cancelamento de uma consulta.
- `ver_consultas_medico()`: Lista todas as consultas agendadas para um determinado médico.
- `ver_consultas_no_dia()`: Lista todas as consultas agendadas para um determinado dia.

#### **Data e Hora**

- `tempoagora()`: Obtém a data e a hora atuais do sistema.
- `validardata()`: Verifica se uma determinada data (dia, mês, ano) é válida.

#### **Funções Utilitárias**

- `removerQuebraDeLinha()`: Remove o caractere de quebra de linha (`\n`) do final de uma string.
- `compare()`: Uma função de comparação, necessária para a função `qsort` do C, para ordenar números os inteiros.
- `randomizar()`: Preenche um vetor com números aleatórios únicos dentro de um intervalo específico.
- `printf_vermelho()`: Imprime um texto no console na cor vermelha.
- `printf_verde()`: Imprime um texto no console na cor verde.

---

