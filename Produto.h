#include <glib.h>

#ifndef PRODUTO_H
#define PRODUTO_H

//Estrutura que define um produto
typedef struct prod* Produto; 

//Funcao que dado um codigo de produto devolve um produto
Produto criaProduto(char* codProd);

//Funcao que dado um produto retorna o seu codigo
char* getCodProd(Produto p);

//funcao que altera a filial onde o produto esta inserido
Produto setFilialVenda(Produto p, int fil);

//funcao que retorna um array de filiais, com flags TRUE ou FALSE
gboolean* getFilialVenda(Produto p);

//Funcao que verifica semanticamente a validade do produto
gboolean verificaProduto(Produto codigo);

//Funcao que envia para o ecra um dado produto
void printProduto(Produto p);

#endif