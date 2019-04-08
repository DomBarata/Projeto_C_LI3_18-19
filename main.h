#include "CatProdutos.h"
#include "CatClientes.h"
#include "Facturacao.h"
#include "Filial.h"

#define NUMFILIAIS 	3				//numero de filiais deste programa
#define BUFFER 		20				//definicao de um buffer para ler produtos e clientes
#define BUFFERVENDAS 	50			//definicao de um buffer para ler as linhas de vendas
#define LINHASPRODUTOS 	200000		//Limite de linhas lidas do ficheiro de Produtos
#define LINHASCLIENTES 	20000		//Limite de linhas lidas do ficheiro de Clientes
#define LINHASVENDAS 	1000000		//Limite de linhas lidas do ficheiro de Vendas

//struct que tem a faturacao e um array de filiais
typedef struct vendasVarias* VendasFactEFil;

#ifndef SGV_H
#define SGV_H

//interface com o utilizador, onde e guardada em memoria toda a informacao dos ficheiros
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

//Funcao que leitura das vendas e as divide pela faturacao e pelas filiais
VendasFactEFil criaVendasDivididas(CatProdutos catp, CatClientes catc, char* fileRead);

//funcao que retira a faturacao da estrutura de dados VendasFactEFil 
Facturacao GeraFact(VendasFactEFil vF);

//funcao que retira uma filial da estrutura de dados VendasFactEFil 
Filial GeraUmaFilial(VendasFactEFil vF, int i);