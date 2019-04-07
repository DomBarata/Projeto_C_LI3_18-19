#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CatClientes.h"


struct catClis
{
	List_Clientes lista[26];
	int clientesLidos;
};

CatClientes 
	inicializa_CatClientes()
	{
		int j;
		CatClientes catalogo = malloc(sizeof(struct catClis));

		for(j = 0; j < 26; j++)
			catalogo->lista[j] = inicializa_List_Clientes();
		catalogo->clientesLidos = 0;
		return catalogo;
	}

CatClientes 
	insereClientes(CatClientes catC, Cliente cli)
	{
		char* codigo = getCodCli(cli);

		catC->lista[codigo[0] - 'A'] = insereUmCliente(catC->lista[codigo[0] - 'A'], cli);
		catC->clientesLidos++;

	    return catC;
	}

CatClientes 
	setCatClientes(CatClientes catC, char* cli, int fil)
	{
		catC->lista[cli[0] - 'A'] = setList_Clientes(catC->lista[cli[0] - 'A'], cli, fil);

	    return catC;
	}

List_Clientes 
	listaPorLetraClientes(CatClientes catc, char letra)
	{
		void *seg = NULL;
		if (letra >= 'A' && letra <= 'Z')
			seg = catc->lista[letra - 'A'];
	
		return seg;
	}	

gboolean
	clienteExisteNoCatalogo(CatClientes catc, char* cod)
	{
		List_Clientes l = listaPorLetraClientes(catc, cod[0]);

		return clienteExisteNaLista(l, cod);
	}

char**
	codigosSempreCompras(CatClientes catc)
	{
		int i;
		char** codSempre = malloc(sizeof(char*));
		codSempre[0] = NULL;

		for(i = 0; i < 26; i++)
			codSempre = produtosCompradosPorTodos(codSempre, catc->lista[i]);

		return codSempre;
	}

int
	getClientesLidos(CatClientes catc)
	{return catc->clientesLidos;}