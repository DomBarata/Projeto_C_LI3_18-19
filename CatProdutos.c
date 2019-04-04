#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CatProdutos.h"


struct catProds
{
	List_Produtos lista[26];
};

CatProdutos 
	inicializa_CatProdutos()
	{
		int j;
		CatProdutos catalogo = malloc(sizeof(struct catProds));

		for(j = 0; j < 26; j++)
			catalogo->lista[j] = inicializa_List_Produtos();
		return catalogo;
	}

CatProdutos 
	insereProdutos(CatProdutos catPro, Produto prod)
	{
		char* codigo = getCodProd(prod);

		catPro->lista[codigo[0] - 'A'] = insereUmProduto(catPro->lista[codigo[0] - 'A'], prod);

	    return catPro;
	}

List_Produtos 
	listaPorLetraProdutos(CatProdutos catp, char letra)
	{
		void *seg = NULL;
		if (letra >= 'A' && letra <= 'Z')
			seg = catp->lista[letra - 'A'];
	
		return seg;
	}	

gboolean
	produtoExisteNoCatalogo(CatProdutos catp, char* cod)
	{
		List_Produtos l = listaPorLetraProdutos(catp, cod[0]);

		return produtoExisteNaLista(l, cod);
	}