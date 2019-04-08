#include "CatProdutos.h"
#include "CatClientes.h"

#ifndef VENDAUNICA_H
#define VENDAUNICA_H

//estrutura que e uma linha de venda, mas com os campos separados
typedef struct venda* VendaUnica;

//dada uma linha de venda, divide os seus diversos campos
VendaUnica divideLinhasDeVenda(char* str, CatProdutos catp, CatClientes catc);

//Funcao de teste para verificar a leitura e armazenamento correto em VendaUnica
void printVenda(VendaUnica v);

//gets dos valores da estrutura VendaUnica
char* getCodProdVendas(VendaUnica v);
char* getCodCliVendas(VendaUnica v);
double getprecoUnitVendas(VendaUnica v);
int getQuantidadeVendas(VendaUnica v);
char* getTipoVendas(VendaUnica v);
int getMesVendas(VendaUnica v);
int getFilialVendas(VendaUnica v);

#endif