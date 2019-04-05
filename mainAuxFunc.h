#include "CatProdutos.h"
#include "CatClientes.h"
#include "Facturacao.h"

//Funcao que cria o catalogo de Produtos, ja validado semanticamente
CatProdutos criaCatalogoProdutos(CatProdutos catp);

//Funcao que cria o catalogo de Clientes, ja validado semanticamente
CatClientes criaCatalogoClientes(CatClientes catc);

Facturacao criaFacturacao(Facturacao fact, CatProdutos catp, CatClientes catc);