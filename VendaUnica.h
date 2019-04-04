#include "CatProdutos.h"
#include "CatClientes.h"

typedef struct venda* VendaUnica;

VendaUnica divideLinhasDeVenda(char* str, CatProdutos catp, CatClientes catc);
void printVenda(VendaUnica v);