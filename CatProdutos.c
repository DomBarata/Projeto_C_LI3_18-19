#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CatProdutos.h"

#define NUMFILIAIS 3

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

CatProdutos 
	setCatProdutos(CatProdutos catP, char* prod, int fil)
	{
		catP->lista[prod[0] - 'A'] = setList_Produtos(catP->lista[prod[0] - 'A'], prod, fil);

	    return catP;
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

char***
	listaProdutosNaoComprados(CatProdutos catp)
	{
		int i;
		char*** filiaisEmBranco = (char***)malloc(sizeof(char**) * NUMFILIAIS);
		
		for (i = 0; i < NUMFILIAIS; ++i)
		{
			filiaisEmBranco[i] = NULL;
		}


		for(i = 0; i < 26; i++)
			filiaisEmBranco = descobreProdutos(filiaisEmBranco, catp->lista[i]);

		return filiaisEmBranco;
	}

char**
	codigosNenhumaFilial(CatProdutos catp)
	{
		int i;
		char** codNunca = malloc(sizeof(char*));
		codNunca[0] = NULL;

		for(i = 0; i < 26; i++)
			codNunca = produtosNuncaComprados(codNunca, catp->lista[i]);

		return codNunca;
	}