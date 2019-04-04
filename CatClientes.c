#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CatClientes.h"


struct catClis
{
	List_Clientes lista[26];
};

CatClientes 
	inicializa_CatClientes()
	{
		int j;
		CatClientes catalogo = malloc(sizeof(struct catClis));

		for(j = 0; j < 26; j++)
			catalogo->lista[j] = inicializa_List_Clientes();
		return catalogo;
	}

CatClientes 
	insereClientes(CatClientes catC, Cliente cli)
	{
		char* codigo = getCodCli(cli);

		catC->lista[codigo[0] - 'A'] = insereUmCliente(catC->lista[codigo[0] - 'A'], cli);

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