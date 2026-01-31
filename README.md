# Gerenciamento-Presentes
Programa em C utilizando lista encadeada 
O sistema realiza o gerenciamento de presentes de casamento utilizando
uma lista simplesmente encadeada com nó cabeça, permitindo cadastro,
remoção, busca, alteração e listagem de presentes.

## Funcionalidades
- Cadastrar presentes
- Remover presentes
- Buscar presentes pelo nome
- Alterar dados do presente
- Listar presentes recebidos até uma data
- Listar presentes não recebidos

## Estrutura do Projeto
- main.c   → Programa principal
- menu.c   → Implementação do menu e funcionalidades
- menu.h   → Protótipo da função menu
- func.h   → Protótipos das funções do sistema
- dados.h  → Estruturas de dados e definição da lista encadeada

## Como compilar e executar

### Pré-requisitos
- GCC instalado
- Terminal (Git Bash, CMD ou Linux)

### Compilação
No diretório do projeto, execute:

```bash
gcc main.c menu.c -o casamento

execução
Git Bash (Windows)

Após a compilação, execute:

./casamento

Windows (CMD ou PowerShell)
casamento.exe

Linux
./casamento