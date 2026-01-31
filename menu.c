/******************************************************************************

  Projeto: Avaliação 2
  Arquivo: menu.c - espelho do menu.h
  Nome: Lorena Strobel 
  Data:15/12/2024
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "func.h"
#include "menu.h"
lista criar_lista() // essa lista se trata de uma lista com cabeça para facilitar a manipulação dos dados ao longo das funções
{
    lista cabeca=(lista)malloc(sizeof(struct elemento));
    if(cabeca!=NULL)
    {
        cabeca->prox=NULL; // inicializa a lista como vazia
        return cabeca; // retorna o ponteiro
    }
    else
    {
        printf("Erro ao alocar memórias, tente novamente\n");
        exit(1); // encerra o programa se der erro na alocação
    }
}
lista novo_no(Presente x, lista p) // cria um novo nó para os dados
{
    lista n=(lista)malloc(sizeof(struct elemento)); // memória para o novo nó
    if(n==NULL)
    {
        printf("Erro ao alocar memória para o o novo nó, tente novamente\n");
        exit(1); // sai do programa em caso de erro
    }
    n->presente=x; // copia os dados para presente
    n->prox=p; // conectando ao próximo nó da lista
    return n; // retornando o nó criado
}
int validar_data(const char *data) 
{
    if(strlen(data)!=10 || data[2]!='/' || data[5]!='/') 
    {
        return 0; // Formato inválido
    }
    // Extrair dia, mês e ano
    int dia=atoi(&data[0]);
    int mes=atoi(&data[3]);
    int ano=atoi(&data[6]);
    if(dia<1 || dia> 31 || mes<1 || mes>12 || ano<1) 
    {
        return 0; // valores inválidos
    }
    // verificar os dias máximos de cada mês
    int dias_no_mes[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if((ano%4==0 && ano%100!=0) || (ano%400 ==0)) // ajustar para anos bissextos
    {
        dias_no_mes[1]=29; // fevereiro tem 29 dias
    }
    if(dia>dias_no_mes[mes-1]) 
    {
        return 0; // dia inválido para o mês
    }
    if(ano<2024) 
    {
        return 0; // ano anterior a 2024 não é aceito
    }
    return 1; // data válida
}
void menu()
{
    lista cabeca=criar_lista(); // inicializando a lista
    int op;
    do {
    printf("                                                  \n");
    printf("--- GERENCIAMENTO DOS PRESENTES DO CASAMENTO ---\n");
    printf("Digite qual acao realizar\n");
    printf("1- Inserir presentes\n");
    printf("2- Retirar presente\n");
    printf("3- Buscar presente\n");
    printf("4- Alterar presente (local/valor)\n");
    printf("5- Listar presentes ganhos ate determinada data\n");
    printf("6- Listar presentes nao ganhos\n");
    printf("7- Sair do programa\n");
    scanf("%d",&op);
    menuopcoes(op,&cabeca);
    } while(op!=7);
}
void menuopcoes(int op,lista *cabeca)
{
    Presente x;
    switch(op)
    {
        case 1:
            cadastro_presente(cabeca);
            break;
        case 2:
            if(*cabeca==NULL || (*cabeca)->prox==NULL)
            {
                printf("Nenhum presente cadastrado ainda para remocao\n");
                printf("                                                  \n");
            }
            else
            { 
                printf("Digite o nome do presente a ser removido\n");
                scanf(" %[^\n]",x.nome_presente);
                remover_ordenada(x,cabeca);
            }
            break;
        case 3:
         if(*cabeca==NULL || (*cabeca)->prox==NULL)
            {
                printf("Nenhum presente cadastrado, cadastre primeiro para realizar a busca\n");
                printf("                                                  \n");
            }
            else
            {
                printf("Digite o nome do presente para busca:\n");
                scanf(" %[^\n]",x.nome_presente);
                lista pesquisa=buscar_presentes(x,*cabeca);
                if(pesquisa!=NULL)
                {
                    exibir_presentebusca(pesquisa);
                }
                else
                {
                    printf("Presente %s nao encontrado\n",x.nome_presente);
                    printf("                                                  \n");
                }
            }
            break;
        case 4:
            if(*cabeca==NULL || (*cabeca)->prox==NULL)
            {
                printf("Nenhum presente cadastrado, cadastre primeiro\n");
                printf("                                                  \n");
            }
            else
            {
                printf("Digite o nome do presente a ser alterado\n");
                scanf(" %[^\n]",x.nome_presente);
                alterar_presente(x,*cabeca);
            }
            break;
        case 5:
            if(*cabeca==NULL || (*cabeca)->prox==NULL)
            {
                printf("Nenhum presente cadastrado ainda, cadastre primeiro\n");
                printf("                                                  \n");
            }
            else
            {
                printf("Digite a data para procurar os presentes ganhos ate essa data:\n");
                scanf(" %[^\n]",x.data);
                if(!validar_data(x.data)) 
                {
                    printf("Data inválida! Tente novamente no formato correto.\n");
                    strcpy(x.data, ""); // Resetar a data para evitar valores inválidos
                    return;
                }
                printf("Exibindo os presentes ganhos ate a data %s:\n",x.data);
                listarpresentes_ganhos(x,*cabeca);
                printf("                                                  \n");
            }
            break;
        case 6:
            if(*cabeca==NULL || (*cabeca)->prox==NULL)
            {
                printf("Nenhum presente cadastrado, cadastre primeiro\n");
                printf("                                                  \n");
            }
            else
            {
                listarpresentes_naoganhos(*cabeca);
            }
            break;
        case 7:
            printf("Encerrando o programa\n");
            liberar_lista(*cabeca);
            break;
        default:
            printf("Opcao invalida, digite novamente com números entre 1 e 7\n");
    }
}
void cadastro_presente(lista *cabeca)
{
    Presente novopresente={"", "", 0.0, "", ""}; // variável do tipo Presente para inserir novo presente
    printf("Digite os dados do presente\n");
    printf("Nome do presente:\n");
    scanf(" %[^\n]",novopresente.nome_presente); // formato para entrada de strings para permitir entradas como "conjunto de facas"
    printf("Local:\n");
    scanf(" %[^\n]",novopresente.local);
    printf("Valor:\n");
    scanf("%f",&novopresente.valor);
    printf("Nome do convidado:\n");
    scanf(" %[^\n]",novopresente.nome_convidado);
    strcpy(novopresente.data, "");  // copia para o campo data vazio
    printf("Presente cadastrado com sucesso\n");
    printf("Cadastre a data em 'alterar presente' quando receber o presente\n");
    inserir_ordenada(novopresente,cabeca);  // inserindo o novo presente ordenadamente
}
void inserir_ordenada(Presente x, lista *L) // inserindo novo nó na lista
{
   while(*L!=NULL && strcmp((*L)->presente.nome_presente,x.nome_presente)<0)
   {
      L=&(*L)->prox; // retorna o endereço do ponteiro para o próximo nó
   }
    *L=novo_no(x,*L); // inserindo ordenadamente
}
void remover_ordenada(Presente x, lista *L) 
{
   while(*L!=NULL && strcmp((*L)->presente.nome_presente,x.nome_presente)<0) 
   {
        L=&(*L)->prox; // retorna o endereço do ponteiro para o próximo nó
   }
   if(*L==NULL || strcmp((*L)->presente.nome_presente,x.nome_presente)>0)
   {
        printf("Presente %s não encontrado\n",x.nome_presente);
        return;
   }
   printf("Presente %s removido da lista\n",x.nome_presente);
   printf("----------------------------------------------\n");
   lista n=*L; // remover o nó
   *L=n->prox; // atualizando o ponteiro para o próximo nó
   free(n); // libera memória
}
lista buscar_presentes(Presente x, lista l) // buscar presente
{
    while(l!=NULL && strcmp(l->presente.nome_presente,x.nome_presente)<0)
    {
        l=l->prox; // avança para o próximo nó
    }
    if(l!=NULL && strcmp(l->presente.nome_presente,x.nome_presente)==0)
    {
        return l; // nó do presente encontrado
    }
    else
    {
        return NULL; // não encontrado
    }
}
void alterar_presente(Presente x, lista l) // alterar os dados de valor,local e data do presente
{
    int op;
    while(l!=NULL && strcmp(l->presente.nome_presente,x.nome_presente)<0)
    {
        l=l->prox; // avançando para os próximos nós
    }
    if(l!=NULL && strcmp(l->presente.nome_presente,x.nome_presente)==0) // quando o nó for encontrado
    {
        printf("----------------------------------------------\n");
        printf("Presente encontrado, digite qual acao realizar\n");
        printf("1- Editar local de compra do presente\n");
        printf("2- Editar valor do presente\n");
        printf("3- Alterar local e valor do presente\n");
        printf("4- Adicionar data de recebimento do presente\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                printf("----------------------------------------------\n");
                printf("Digite o novo local onde encontrar o presente:\n");
                scanf(" %[^\n]",l->presente.local);
                printf("Dados do presente %s alterados\n",x.nome_presente);
                break;
            case 2:
                printf("----------------------------------------------\n");
                printf("Digite o novo valor do presente:\n");
                scanf("%f",&l->presente.valor);
                printf("Dados do presente %s alterados\n",x.nome_presente);
                break;
            case 3:
                printf("----------------------------------------------\n");
                printf("Digite o novo local onde encontrar o presente:\n");
                scanf(" %[^\n]",l->presente.local);
                printf("Digite o novo valor do presente:\n");
                scanf("%f",&l->presente.valor);
                printf("Dados do presente %s alterados\n",x.nome_presente);
                break;
            case 4:
                printf("----------------------------------------------\n");
                printf("Digite a data de recebimento do presente no formato DD/MM/YYYY\n");
                scanf(" %[^\n]",l->presente.data);
                if(!validar_data(l->presente.data)) 
                    {
                        printf("Data invalida! Tente novamente no formato correto.\n");
                        strcpy(l->presente.data, ""); // Resetar a data para evitar valores inválidos
                        return;
                    }
                printf("Dados do presente %s alterados\n",x.nome_presente);
                break;
            default:
                printf("Opcao invalida\n");
        }
    }
    else
    {
        printf("Presente %s nao encontrado\n",x.nome_presente);
    }
}
void exibir_presentebusca(lista l) // funçaõ para exbir o presente pesquisado
{
    if(l!=NULL)
    {
        printf("----------------------------------------------\n");
        printf("Presente encontrado\n");
        printf("Nome: %s\n",l->presente.nome_presente);
        printf("Local: %s\n",l->presente.local);
        printf("Valor: R$ %.2f\n",l->presente.valor);
        printf("Nome do convidado: %s\n",l->presente.nome_convidado);
        printf("Data: %s\n",l->presente.data);
        printf("----------------------------------------------\n");
    }
}  
void listarpresentes_ganhos(Presente x, lista l)
{
    int encontrados=0;
    while(l!=NULL)
    {
        if(strcmp(l->presente.data,"")!=0 && strcmp(l->presente.data,x.data)<=0) // verifica até a data solicitada e verifica  para evitar dados sem data 
        {  
            printf("----------------------------------------------\n");
            printf("Nome: %s\n",l->presente.nome_presente);
            printf("Local: %s\n",l->presente.local);
            printf("Valor: R$ %.2f\n",l->presente.valor);
            printf("Nome do convidado: %s\n",l->presente.nome_convidado);
            printf("Data: %s\n",l->presente.data);
            printf("----------------------------------------------\n");
            encontrados++;
        }
        l=l->prox; // avança para o próximo nó 
    }
    if(encontrados==0)
    {
        printf("Nenhum presente ganho até a data %s\n",x.data);
    }
}
void listarpresentes_naoganhos(lista l) // exibindo os dados quando presente.data estiver vazio
{
    int encontrados=0;
    while(l!=NULL)
    {
        if(strcmp(l->presente.data,"")==0 && strcmp(l->presente.nome_presente,"")!= 0 && strcmp(l->presente.local,"")!=0) // 
        {
            printf("Exibindo os presentes nao ganhos (com data de recebimento nao cadastrada\n");
            printf("----------------------------------------------\n");
            printf("Nome: %s\n",l->presente.nome_presente);
            printf("Local: %s\n",l->presente.local);
            printf("Valor: %.2f\n",l->presente.valor);
            printf("Nome do convidado: %s\n",l->presente.nome_convidado);
            printf("Data: %s\n",l->presente.data);
            printf("----------------------------------------------\n");
            encontrados++;
        }
       l=l->prox; // avança para o próximo nó
    }
    if(encontrados==0) // se todos os presentes já foram ganhos
    {
        printf("Todos os presentes cadastrados na lista já foram entregues/comprados\n");
    }
}  
void liberar_lista(lista cabeca) // função para destruir a lista
{
    if(cabeca!=NULL)
    {
        lista Elem; // Elem é um ponteiro pois lista foi definida como um ponteiro para struct elemento
        while(cabeca!=NULL)
        {
            Elem=cabeca; // armazena o nó atual
            cabeca=cabeca->prox; // percorre os próximos nós da lista
            free(Elem); // libera/detroi a lista 
        }
    }
}