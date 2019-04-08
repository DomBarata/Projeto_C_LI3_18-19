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

//Funcao que altera a filial de um determinado produto em catalogo
CatProdutos setCatProdutos(CatProdutos catP, char* prod, int fil);

//funcao que retorna um array de codigos de produtos nao comprados por ninguem
char*** listaProdutosNaoComprados(CatProdutos catp);

//funcao que retorna os codigos os codigos dos produtos nao comprados
//por filial (primeiro indice)
char** codigosNenhumaFilial(CatProdutos catp);

//Funcao que dado um catalogo e uma letra, retorna uma lista de
//produtos comecados por essa mesma letra
List_Produtos listaPorLetraProdutos(CatProdutos catp, char letra);

//funcao que verifica que o produto esta inserido no catalogo
gboolean produtoExisteNoCatalogo(CatProdutos catp, char* cod);

//funcao que retorna o num de produtos que foram inseridos no catalogo
int	getProdutosLidos(CatProdutos catp);

#endif