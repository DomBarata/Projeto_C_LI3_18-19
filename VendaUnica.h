#include "CatProdutos.h"
#include "CatClientes.h"

typedef struct venda* VendaUnica;

VendaUnica divideLinhasDeVenda(char* str, CatProdutos catp, CatClientes catc);
void printVenda(VendaUnica v);

char* getCodProdVendas(VendaUnica v);

char* getCodCliVendas(VendaUnica v);

double getprecoUnitVendas(VendaUnica v);

int getQuantidadeVendas(VendaUnica v);

char* getTipoVendas(VendaUnica v);

int getMesVendas(VendaUnica v);

int getFilialVendas(VendaUnica v);