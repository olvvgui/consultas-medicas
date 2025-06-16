
#### **1. Estruturas de Dados (`funcoes.h`)**

- **`cadastro_save`**: Armazena os dados de registro de um usuário. Contém campos para `nome`, `senha`, `cpf`, `idade` e `email`.
- **`dados_paciente`**: Armazena os detalhes de uma consulta médica agendada. Contém campos para a data (`dia[3]`), `horario`, `nome` do paciente, `obs` (observações) e nome do `medico`.
- **`tempo`**: Uma Struct auxiliar para armazenar a data e a hora atuais do sistema (`dia`, `mes`, `ano`, `hora`).
- **Variáveis Globais**: Paciente e cadastro são utilizadas em diversas funções durante a execução, então podem agir como uma forma de  auxiliar temporário em determinadas partes da execução

#### **2. Funções de Lógica e Utilitários (`funcoes.c`)**

##### **Funções de Interface e Validação:**

- `menu()`: Exibe o menu principal com 6 opções e retorna a escolha numérica selecionada
- `printf_vermelho()` e `printf_verde()`: Imprimem textos no console em vermelho e verde, respectivamente.
- `removerQuebraDeLinha()`: Remove o caractere de nova linha do final de strings.
- `validardata()`: Verifica se uma data fornecida (dia, mês, ano) é válida. A validação compara a data com a data atual para impedir agendamentos no passado e contém lógica específica para o ano de 2025 e para anos futuros, incluindo a verificação de anos bissextos.
- `verificaEmail()`: Verifica se uma string de e-mail termina com um dos domínios pré-aprovados (como `@gmail.com`, `@ufg.br`, etc.).
- `horariosvalidos()`: Gera 4 horários de consulta aleatórios e únicos para uma data específica, garantindo que, para o dia atual, apenas horários futuros sejam mostrados.
- `randomizar()`: É a função que gera os números aleatórios únicos para os horários, garantindo que não vai ter repetição.
- `lembrete()`: Simula o envio de um e-mail de lembrete imprimindo os detalhes da consulta na tela.

##### **Funções de Gerenciamento de Contas e Consultas:**

- `cadastrarpaciente()`: Recebe os dados de um novo usuário e os adiciona ao final do arquivo `source/bin/cadastro.bin`.
- `login()`: Pede um CPF e senha. Em seguida, lê o arquivo `cadastro.bin` para encontrar um CPF correspondente. Se encontrar, compara a senha. Se ambos estiverem corretos, o login é bem-sucedido.
- `buscar_consulta()`: Lê o arquivo `dados_clientes.bin` e exibe os detalhes das consultas cujo CPF corresponde ao do usuário que está logado no sistema.
- `cancelar_consulta()`: Encontra uma consulta baseada no CPF do usuário logado. Para fazer o cancelamento, ele copia todos os outros agendamentos para um arquivo temporário, apaga o arquivo original e renomeia o temporário.
- `reagendar_consulta()`: Encontra a consulta do usuário logado, solicita uma nova data e hora, e reescreve o arquivo de agendamentos com a informação atualizada, usando a mesma técnica de arquivo temporário.
- `ver_consultas_medico()`: Pede que o usuário escolha um médico de uma lista e então varre o arquivo de agendamentos, imprimindo todas as consultas daquele médico.
- `ver_consultas_no_dia()`: Pede que o usuário digite uma data e então varre o arquivo de agendamentos, imprimindo todas as consultas daquela data.

#### **3. Fluxo Principal do Programa (`main.c`)**

- **Inicialização**: O programa começa e já chama a função `menu()`.
- **Controle com `switch`**: A escolha do usuário no menu direciona o programa para um dos blocos `case` do `switch`.
- **`case 1 (Cadastro)`**: Guia o usuário passo a passo no preenchimento do nome, CPF, e-mail e senha, com validações em cada etapa (tamanho do CPF, confirmação de senha, etc.), e então salva o novo cadastro.
- **`case 2 (Agendamento)`**: Primeiramente, verifica se o usuário fez login. Se não, força o login. Uma vez logado, guia o usuário na escolha do médico, da data e de um dos horários válidos gerados pelo sistema. Por fim, salva a consulta.
- **`cases 3, 4, 5 (Busca, Cancelamento, Reagendamento)`**: Todos estes casos também verificam o estado de login e então chamam as funções correspondentes para operar sobre as consultas do usuário logado.
- **`case 6 (Relatórios)`**: Oferece um segundo menu para o usuário escolher se quer ver consultas por médico ou por dia, sem a necessidade de login.
- **Ciclo de Execução**: Ao final da execução de cada uma dessas operações, a função `main` é chamada novamente, fazendo com que o programa exiba o menu principal mais uma vez, permitindo que o usuário realize uma nova ação. O programa só termina se o usuário escolher a opção `0` pra finalizar a exec.