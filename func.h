/******************************************************************************

  Projeto: Avaliação 2
  Arquivo: func.h - funções utilizadas no programa
  Nome: Lorena Strobel 
  Data:15/12/2024
*******************************************************************************/
#include "dados.h"
void menuopcoes(int op,lista *cabeca);
lista criar_lista();
lista no(Presente x, lista p);
int validar_data(const char *data); 
void cadastro_presente(lista *cabeca);
void inserir_ordenada(Presente x, lista *L);
void remover_ordenada(Presente x, lista *L);
lista buscar_presentes(Presente x, lista l);
void alterar_presente(Presente x, lista l);
void exibir_presentebusca(lista l);
void listarpresentes_ganhos(Presente x, lista l);
void listarpresentes_naoganhos(lista l);
void liberar_lista(lista cabeca);













