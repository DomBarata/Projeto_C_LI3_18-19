#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Produto.h"
#include "List_Produtos.h"

#define PAGINACAO 25
#define NUMFILIAIS 3

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

List_Produtos
	setList_Produtos(List_Produtos l, char* prod, int fil)
	{
		Produto p;

		p = g_hash_table_lookup(l->produtos, prod);	//devolve o apontador para o produto
		p = setFilialVenda(p, fil);	//mudança do apontador, logo nao precisa de reinserir na hastable

	    return l;
	}

void 
	consultarProdutos(List_Produtos l)
	{
		void** array;
		char** arrayFinal;
		int i = 0, j = 0, pag = 1;
		int arraySize;
		guint* tam = malloc(sizeof(guint));
		
		*tam = g_hash_table_size(l->produtos);	//calcula o numero de chaves na hashable
		arraySize = (int)*tam;

		array = g_hash_table_get_keys_as_array (l->produtos, tam);	
		arrayFinal = (char**)array;

		qsort(arrayFinal, arraySize, sizeof(char*), comp);	//ordenacao do array
		
		while(arrayFinal[i])
		{
			system("clear");
			j = 0;
			while(j < PAGINACAO && arrayFinal[i])
			{
				printf("%s\n", arrayFinal[i]);	
				i++;
				j++;
			}
			printf("Pagina %d de %d\n", pag, (arraySize/ PAGINACAO)+1); getchar();
			pag++;
		}
	}

gboolean
	produtoExisteNaLista(List_Produtos l, char* codProd)
	{return g_hash_table_contains(l->produtos, codProd);}

int 
	getDimensaoLista(List_Produtos l)
	{
		guint dim = g_hash_table_size(l->produtos);
		return dim;
	}

char***
	descobreProdutos(char*** filiaisEmBranco, List_Produtos l)
	{
		char *valueKey;
		GList* valores; 
		gboolean* array;
		int pos = 0;

		//inicializacao a 0 da variavel filiaisEmBranco
		if(!filiaisEmBranco[0])
		{
			for (int i = 0; i < NUMFILIAIS; ++i)
			{
				filiaisEmBranco[i] = malloc(sizeof(char*));
				filiaisEmBranco[i][0] = NULL;	//divivida por filiais
			}
		}

		valores = g_hash_table_get_values(l->produtos);	//lista de valores

		while(valores)
		{
			valueKey = getCodProd((Produto)valores->data);	//buscar a key, replicada nos values desta hashtable
			array = getFilialVenda((Produto)valores->data);	//buscar a filial

			for (int i = 0; i < NUMFILIAIS; ++i)
			{
				if(!array[i])	//se o produto nao foi comprado na filial[i] 
				{ 	
					pos = 0;
					while(filiaisEmBranco[i][pos])	//calcula a posiçao onde vai inserir
						pos++;

					//copia o codigo do produto nao comprado para uma variavel
					filiaisEmBranco[i] = realloc(filiaisEmBranco[i], ((pos+2) * sizeof(char*)));
					filiaisEmBranco[i][pos] = g_strdup(valueKey);
					filiaisEmBranco[i][pos+1] = NULL;
				}
			}
			valores = valores->next;	//posicao a seguir da GList
		}

		return filiaisEmBranco;
	}
char**
	produtosNuncaComprados(char** codNunca, List_Produtos l)
	{
		char *valueKey;
		GList* valores; 
		gboolean* array;
		int pos = 0;

		valores = g_hash_table_get_values(l->produtos);

		while(codNunca[pos])
			pos++;

		while(valores)
		{
			valueKey = getCodProd((Produto)valores->data);
			array = getFilialVenda((Produto)valores->data);

			if((array[0] == FALSE) && (array[1] == FALSE) && (array[2] == FALSE))	//se nao foi comprado em nenhuma filial
			{
				codNunca = realloc(codNunca, sizeof(char*) * (pos+2));
				codNunca[pos] = g_strdup(valueKey);	
				codNunca[pos+1] = NULL;	
				pos++;		
			}
			valores = valores->next;
		}
		return codNunca;
	}


static int 
	comp(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}