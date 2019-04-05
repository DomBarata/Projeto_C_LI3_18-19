#include "CatProdutos.h"
#include "CatClientes.h"
#include "Facturacao.h"
#include "Filial.h"
#define NUMFILIAIS 3


typedef struct vendasVarias* VendasFactEFil;

struct sgv
{
	CatProdutos cp;
	CatClientes ccli;
	Facturacao fact;
	Filial filiais[NUMFILIAIS];
};
typedef struct sgv* SGV;

//Funcao que cria o catalogo de Produtos, ja validado semanticamente
CatProdutos criaCatalogoProdutos(CatProdutos catp);

//Funcao que cria o catalogo de Clientes, ja validado semanticamente
CatClientes criaCatalogoClientes(CatClientes catc);

VendasFactEFil criaVendasDivididas(CatProdutos catp, CatClientes catc);


Facturacao GeraFact(VendasFactEFil vF);

Filial GeraUmaFilial(VendasFactEFil vF, int i);

SGV CriaSGV(CatProdutos catp, CatClientes catc, Facturacao f, Filial* fil);
