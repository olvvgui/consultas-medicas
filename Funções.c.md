
#### **1. Utilitários e Interface**

- `void removerQuebraDeLinha(char *str)`
    
    - **Objetivo:** Limpar strings lidas do input do usuário, removendo o caractere de nova linha (`\n`) que o fgets costuma deixar.
    - **Funcionamento:** Utiliza `strcspn(str, "\n")` para encontrar o índice da primeira ocorrência de `\n`. Em seguida, substitui esse caractere pelo nulo (`\0`), finalizando a string naquele ponto.
- `int menu()`
    
    - **Objetivo:** Apresentar o menu principal ao usuário e receber sua escolha.
    - **Funcionamento:** Imprime as opções disponíveis, lê um número inteiro com `scanf`, e valida se a escolha está dentro do intervalo permitido (0 a 6). Retorna a escolha do usuário. Usa as funções `printf_verde` e `printf_vermelho` para melhorar a interface com as cores.
- `void selecionar(...)`
    
    - **Objetivo:** É uma função para apresentar duas opções ao usuário e armazenar a escolha.
    - **Funcionamento:** Recebe strings para o tipo de seleção (ex: médico e clínica medica) e para as duas opções. Pede ao usuário que digite 1 ou 2 e, usando um `switch`, copia a string da opção escolhida para a variável de destino (`nome_medico`).
- `void printf_vermelho(const char *text)` e `void printf_verde(const char *text)`
    - **Objetivo:** Melhorar a experiência do usuário exibindo textos do console em cores diferentes (vermelho para erros, verde para sucesso/informações).
    - **Funcionamento:** Utilizam códigos de escape ANSI \0331;31m define a cor para vermelho mais vivo, e `\033[0m` reseta a formatação para o padrão.

#### **2. Gerenciamento de Contas (Cadastro e Login)**

- `void cadastrarpaciente(cadastro_save cad, int *logado)`
    
    - **Objetivo:** Salvar os dados de um novo paciente no arquivo de cadastros.
    - **Funcionamento:** Abre o arquivo `source/bin/cadastro.bin` em modo de adição binária (ab). Isso faz com que novos cadastros sejam adicionados ao final do arquivo, sem apagar os que já existem. Utiliza `fwrite` para escrever a estrutura `cadastro_save` inteira no arquivo.
- `void login(...)`
    
    - **Objetivo:** Autenticar um usuário com base no CPF e senha.
    - **Funcionamento:**
        1. Pede o CPF ao usuário.
        2. Abre `source/bin/cadastro.bin` para leitura (`rb`).
        3. Lê o arquivo registro por registro dentro de um `while (fread(...) == 1)`.
        4. Compara o CPF digitado com o `cadastro.cpf` de cada registro.
        5. Se encontra um CPF correspondente, pede a senha.
        6. Se a senha também corresponde, o login é bem-sucedido. A flag `*logado` é alterada para `1`, e os dados do usuário (`nome`, `idade`) são copiados para as variáveis de saída passadas por parâmetro.
        7. Se o CPF ou a senha estiverem incorretos, exibe mensagens de erro relacionado ou a cpf errado ou senha errada.

#### **3. Gerenciamento de Consultas**

- `buscar_consulta(const char *nome, const char *cpf)`
    
    - **Objetivo:** Exibir todas as consultas agendadas para um determinado CPF.
    - **Funcionamento:** Abre `source/bin/dados_clientes.bin` e lê cada registro de consulta.
- `void cancelar(usuario *usr)`
    // A função mudou depois do ultimo commit, entao tive que atualizar aqui tambem já que a logica mudou
    - **Objetivo:** Remover um agendamento do arquivo de consultas.
    - **Funcionamento:**
        1.utilizando rb+, ela nao cria mais nenhum temp(arquivo temporario), 
        2- depois, ela mostra uma lista de consultas relacionadas ao cpf do user, com o usuario escolhendo qual deve cancelar
        3- Usando do fseek, ela vai mover o cursor do arquivo até a consulta que o usuario deseja eliminar,marcando como inativo. Depois levando o cursor de volta pro inicio e o fwrite para sobrescrever aquele registro no arquivo

- `reagendar_consulta(const char *cpf)`
    //outra parte do commit aqui olha
    - **Objetivo:** Alterar a data e/ou hora de uma consulta existente.
    - **Funcionamento:** (basicamente igual a cancelar consultas)
        1. Ela lista as consultas baseadas no cpf da pessoa, mostrando somente aquelas que pertencem ao cpf
        2. Ela usa também o fseek para pular até a consulta onde a pessoa quer reagendar, sobrescrevendo o arquivo ( no caso os campos de data e hora)
        3. Utiliza também o fwrite para isso.
           
#### **4. Funções de Visualização (Relatórios)**

- `ver_consultas_medico()` e `ver_consultas_no_dia()`
    - **Objetivo:** Listar todas as consultas filtrando por médico ou por data.
    - **Funcionamento:** Pede ao usuário o critério de busca (nome do médico ou a data). Em seguida, leem o arquivo `dados_clientes.bin` registro a registro e imprimem na tela apenas aqueles que correspondem ao filtro escolhido pelo usuário.

#### **5. Validação e Geração de Dados**

- `tempoagora(tempo *data)`
    
    - **Objetivo:** Obter a data e hora atuais do sistema operacional.
    - **Funcionamento:** Usa as funções da biblioteca `<time.h>`.Com ela, obtém o tempo em segundos desde 01/01/1970, e `localtime()` converte esse valor para uma estrutura `tm` com os campos de data e hora locais, que são então armazenados na struct `data` passada por ponteiro.
- `validardata(int dia, int mes, int ano)`
    
    - **Objetivo:** Verificar se uma data é válida e se não está no passado.
    - **Funcionamento:** A função verifica se o ano, mês e dia são posteriores ou iguais à data atual. Também valida regras do calendário, como a quantidade de dias em cada mês e anos bissextos.
- `horariosvalidos(int dia, int *vet)`
    
    - **Objetivo:** Gerar e exibir uma lista de horários disponíveis para agendamento.
    - **Funcionamento:** Determina o intervalo de horas possíveis (se a data for hoje só permite agendar futuramente). Em seguida, chama a função `randomizar` para preencher um vetor com 4 horários únicos e aleatórios dentro desse intervalo.
      ex: Se o agendamento for feito as 11 horas da manhã, o agendamento só poder ser feito posteriormente esse horário, ainda seguindo o limite de até 17:00 para agendamento.
- `randomizar(...)` e `compare(...)`
    
    - **Objetivo:**  Gerar uma lista de números inteiros aleatórios e únicos, em ordem crescente.
    - **Funcionamento**: **(Função randomizar)**: Ela cria um margem ou pool(se preferir) com todos os números possíveis no intervalo, sorteia um item desse pool, o move para o vetor de resultado, e o remove do pool pra que não tenha outro sorteio. Depois, usa a função `qsort` da biblioteca padrão (usando a função compare) para ordenar os horários antes de exibi-los.
- `int verificaEmail(char *email)`
    
    - **Objetivo:** Fazer uma validação simples de e-mail, verificando se ele termina com um dos domínios reconhecidos. (tais como @gmail.com, @outlook.com, @discente.ufg.br, @ufg.br, @hotmail.com)
    - **Funcionamento:** Compara o final da string de e-mail com uma lista pré-definida de domínios. A forma como usa aritmética de ponteiros (`email + tamanhoemail - tamanhodom`)
