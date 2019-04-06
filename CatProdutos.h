#include <glib.h>
#include "Produto.h"
#include "List_Produtos.h"

#ifndef CATPRODUTOS_H
#define CATPRODUTOS_H

typedef struct catProds* CatProdutos; //Estrutura que define um array
									  //de 26 List_Clientes

//Funcao que aloca memoria para a estrutura de dados
CatProdutos inicializa_CatProdutos();

//Funcao que dado um catalogo e um produto, o insere nesse mesmo catalogo
CatProdutos insereProdutos(CatProdutos catPro, Produto prod);

CatProdutos setCatProdutos(CatProdutos catP, char* prod, int fil);

//Funcao que dado um catalogo e uma letra, retorna uma lista de
//produtos comecados por essa mesma letra
List_Produtos listaPorLetraProdutos(CatProdutos catp, char letra);

//funcao que verifica que o produto esta inserido no catalogo
gboolean produtoExisteNoCatalogo(CatProdutos catp, char* cod);

#endif