#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Produto.h"
#include "List_Produtos.h"
#include "CatProdutos.h"
#include "mainAuxFunc.h"
#include "Cliente.h"
#include "List_Clientes.h"
#include "CatClientes.h"
#include "VendaUnica.h"


int //Segmento de Teste
	main(int argc, char const *argv[])
	{

		CatProdutos lojaProds;
		CatClientes lojaClientes;
		VendasFactEFil vendas;
//		VendaUnica v;
//		List_Produtos lP;
//		List_Clientes lC;

		lojaProds = inicializa_CatProdutos();
		lojaProds = criaCatalogoProdutos(lojaProds);	
	 	if(lojaProds == NULL) exit(1);

	 	lojaClientes = inicializa_CatClientes();
	 	lojaClientes = criaCatalogoClientes(lojaClientes);
		if(lojaClientes == NULL) exit(1);	


		vendas = criaVendasDivididas(lojaProds, lojaClientes);
		if(vendas == NULL) exit(1);
/*
	 	lP = listaPorLetraProdutos(lojaProds, 'A');
	 	if(lP == NULL) exit(1);
	 	consultarProdutos(lP);
	 	
	 	lC = listaPorLetraClientes(lojaClientes, 'Z');
	 	if(lC == NULL) exit(1);
	 	consultarClientes(lC);

	 	produtoExisteNoCatalogo(lojaProds, "AF1159")?printf("AF1159 existe\n"):printf("AF1159 não existe\n");
		clienteExisteNoCatalogo(lojaClientes, "W3883")?printf("W3883 existe\n"):printf("W3883 não existe\n");
*/	 	



	 	return 0;
	}