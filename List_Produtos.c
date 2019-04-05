#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Produto.h"
#include "List_Produtos.h"

struct listaProdutos
{
	GHashTable* produtos;
};

static int comp(const void* p1, const void* p2);

List_Produtos 
	inicializa_List_Produtos()
	{
		List_Produtos l = malloc(sizeof(struct listaProdutos));
		l->produtos = g_hash_table_new(g_str_hash, g_str_equal);

		return l;
	}

List_Produtos 
	insereUmProduto(List_Produtos l, Produto p)
	{
		g_hash_table_insert(l->produtos, getCodProd(p), p);

	    return l;
	}

void 
	consultarProdutos(List_Produtos l)
	{
		void** array;
		char** arrayFinal;
		int i = 0;
		int arraySize;
		guint* tam = malloc(sizeof(guint));
		
		*tam = g_hash_table_size(l->produtos);
		arraySize = (int)*tam;

		array = g_hash_table_get_keys_as_array (l->produtos, tam);
		arrayFinal = (char**)array;

		qsort(arrayFinal, arraySize, sizeof(char*), comp);
		
		while(arrayFinal[i])
		{
			printf("%s\n", (char*)arrayFinal[i]);	
			i++;
		}
	}

gboolean
	produtoExisteNaLista(List_Produtos l, char* codProd)
	{return g_hash_table_contains(l->produtos, codProd);}

static int 
	comp(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}
