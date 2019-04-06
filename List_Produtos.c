#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Produto.h"
#include "List_Produtos.h"

#define PAGINACAO 25

struct listaProdutos
{
	GHashTable* produtos;
	int tam;
};

static int comp(const void* p1, const void* p2);

List_Produtos 
	inicializa_List_Produtos()
	{
		List_Produtos l = malloc(sizeof(struct listaProdutos));
		l->produtos = g_hash_table_new(g_str_hash, g_str_equal);
		l->tam = 0;
		return l;
	}

List_Produtos 
	insereUmProduto(List_Produtos l, Produto p)
	{
 		g_hash_table_insert(l->produtos, getCodProd(p), p);
 		l->tam ++;

	    return l;
	}

List_Produtos
	setList_Produtos(List_Produtos l, char* prod, int fil)
	{
		Produto p;

		p = g_hash_table_lookup(l->produtos, prod);
		p = setFilialVenda(p, fil);

	    return l;
	}

void 
	consultarProdutos(List_Produtos l)
	{
		void** array;
		char** arrayFinal;
		int i = 0, pag = 1;
		int arraySize;
		guint* tam = malloc(sizeof(guint));
		
		*tam = g_hash_table_size(l->produtos);
		arraySize = (int)*tam;

		array = g_hash_table_get_keys_as_array (l->produtos, tam);
		arrayFinal = (char**)array;

		qsort(arrayFinal, arraySize, sizeof(char*), comp);
		
		while(arrayFinal[i])
		{
			system("clear");
			printf("Pagina %d de %d\n", pag, (l->tam / PAGINACAO)+1);
			for(int j = 0; j < PAGINACAO && arrayFinal[i]; j++)
			{
				printf("%s\n", arrayFinal[i]);	
				i++;
			}
			pag++;
			printf("Prima ENTER para passar a pagina seguinte"); getchar();
		}
	}

gboolean
	produtoExisteNaLista(List_Produtos l, char* codProd)
	{return g_hash_table_contains(l->produtos, codProd);}

int 
	dimensaoLista(List_Produtos l)
	{return l->tam;}

static int 
	comp(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}