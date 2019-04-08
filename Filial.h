#include "VendaUnica.h"

#ifndef FILIAL_H
#define FILIAL_H

//Estrura que define uma filial
typedef struct filMes* Filial;

Filial inicializaFilial();

//Insere uma venda em determinada filial
Filial insereFilial(VendaUnica v, Filial fil);

//dado um cliente e um mes, saber a quantidade de produtos que ele comprou em determinada filial
int	quantidadeClienteMes(Filial fil, int m, char* codCli);

//dado um produto, e um tipo de venda(FALSE - Normal && TRUE - Promocao), saber os clientes que
//compraram esse mesmo produto
char** cClienteQueCompraramOProduto(Filial f, CatClientes catc, char* codProd, gboolean promo);

//dado um codigo de cliente e uma filial, retorna os codigos de produtos como um array
char** getProdutos(Filial f, char* cod);

//dado um codigo de cliente e uma filial, retorna as quantidades como um array ordenado da mesma maneira da funcao anterior
int* getQuantidades(Filial f, char* cod);

#endif