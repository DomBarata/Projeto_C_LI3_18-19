#include <glib.h>

#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct prod* Produto; //Estrutura que define um produto

//Funcao que dado um codigo de produto devolve um produto
Produto criaProduto(char* codProd);

//Funcao que dado um produto retorna o seu codigo
char* getCodProd(Produto p);

Produto setFilialVenda(Produto p, int fil);

gboolean* getFilialVenda(Produto p);
//Funcao que verifica semanticamente a validade do produto
gboolean verificaProduto(Produto codigo);

//Funcao que imprime o codigo do produto
void printProduto(Produto p);

#endif