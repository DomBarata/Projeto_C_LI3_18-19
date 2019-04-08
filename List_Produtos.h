#include <glib.h>

#ifndef LIST_PRODUTOS_H
#define LIST_PRODUTOS_H

 //Estrutura de dados que contem um array de Produtos
typedef struct listaProdutos* List_Produtos;

//Funcao que aloca memoria para uma List_Produtos
List_Produtos inicializa_List_Produtos();

//Funcao que dada uma lista e um produto, o insere nessa mesma lista
List_Produtos insereUmProduto(List_Produtos l, Produto p);

//Funcao que insere a filiail num produto existente em determinada lista
List_Produtos setList_Produtos(List_Produtos l, char* prod, int fil);

//Print no ecra de uma lista ordenada e paginada de produtos
void consultarProdutos(List_Produtos l);

//funcao que retorna um array de 3 dimensoes, sendo que a primeira e atriubuida
//a filial em que o produto nao foi vendido, o segudo a posicao onde se encontra
//os codigos de produto.
//Descobre os produtos nao comprados em determinada filial
char*** descobreProdutos(char*** filiaisEmBranco, List_Produtos l);

//array com os codigos de produtos que nunca ninguem comprou nas filiais
char** produtosNuncaComprados(char** codNunca, List_Produtos l);

//Funcao que dada uma lista, verifica se o codigo do produto esta inserido
gboolean produtoExisteNaLista(List_Produtos l, char* codProd);

//funcao que retorna a dimensao de determinada lista
int getDimensaoLista(List_Produtos l);

#endif