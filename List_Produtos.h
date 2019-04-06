#include <glib.h>

#ifndef LIST_PRODUTOS_H
#define LIST_PRODUTOS_H

typedef struct listaProdutos* List_Produtos; //Estrutura de dados que contem
											 //um array de Produtos

//Funcao que aloca memoria para uma List_Produtos
List_Produtos inicializa_List_Produtos();

//Funcao que dada uma lista e um produto, o insere nessa mesma lista
List_Produtos insereUmProduto(List_Produtos l, Produto p);


List_Produtos setList_Produtos(List_Produtos l, char* prod, int fil);
//Print no ecra de uma lista ORDENADA de produtos
void consultarProdutos(List_Produtos l);

//Funcao que dada uma lista, verifica se o codigo do produto esta inserido
gboolean produtoExisteNaLista(List_Produtos l, char* codProd);

int dimensaoLista(List_Produtos l);

#endif