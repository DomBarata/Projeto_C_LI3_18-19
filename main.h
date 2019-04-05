#include "CatProdutos.h"
#include "CatClientes.h"
#include "Facturacao.h"
#include "Filial.h"

#define NUMFILIAIS 	3
#define BUFFER 		20
#define BUFFERVENDAS 	50
#define LINHASPRODUTOS 	200000
#define LINHASCLIENTES 	20000
#define LINHASVENDAS 	1000000

typedef struct vendasVarias* VendasFactEFil;

#ifndef SGV_H
#define SGV_H

struct sgv
{
	CatProdutos cp;
	CatClientes ccli;
	Facturacao fact;
	Filial filiais[NUMFILIAIS];
};
typedef struct sgv* SGV;

#endif

SGV inicializaSGV();

//Funcao que cria o catalogo de Produtos, ja validado semanticamente
CatProdutos criaCatalogoProdutos(CatProdutos catp, char* fileRead);

//Funcao que cria o catalogo de Clientes, ja validado semanticamente
CatClientes criaCatalogoClientes(CatClientes cat, char* fileRead);

VendasFactEFil criaVendasDivididas(CatProdutos catp, CatClientes catc, char* fileRead);


Facturacao GeraFact(VendasFactEFil vF);

Filial GeraUmaFilial(VendasFactEFil vF, int i);