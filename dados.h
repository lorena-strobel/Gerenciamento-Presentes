/******************************************************************************

  Projeto: Avaliação 2
  Arquivo: dados.h - dados do presente e manipulação para criar uma lista encadeada
  Nome: Lorena Strobel 
  Data:15/12/2024
*******************************************************************************/
typedef struct casamento {
    char nome_presente[50];
    char local[50];
    float valor;
    char nome_convidado[50];
    char data[11];
} Presente;

struct elemento {
    Presente presente; // dados do nó
    struct elemento *prox; // ponteiro para o próximo nó
};
typedef struct elemento *lista; // ponteiro do tipo struct elemento

