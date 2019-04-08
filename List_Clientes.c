#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Cliente.h"
#include "List_Clientes.h"

struct listaClientes
{
	GHashTable* clientes;
};

static int comp(const void* p1, const void* p2);

List_Clientes 
	inicializa_List_Clientes()
	{
		List_Clientes l = malloc(sizeof(struct listaClientes));
		l->clientes = g_hash_table_new(g_str_hash, g_str_equal);

		return l;
	}

List_Clientes 
	insereUmCliente(List_Clientes l, Cliente c)
	{
		g_hash_table_insert(l->clientes, getCodCli(c), c);

	    return l;
	}

List_Clientes 
	setList_Clientes(List_Clientes l, char* cli, int fil)
	{
		Cliente c;

		c = g_hash_table_lookup(l->clientes, cli);	//retorna o apontador
		c = setFilialCompra(c, fil);				//apontador e modificado, logo nao necessita insert

	    return l;
	}

void //funcao usada apenas em testes
	consultarClientes(List_Clientes l)
	{
		void** array;
		char** arrayFinal;
		int i = 0;
		int arraySize;
		
		guint* tam = malloc(sizeof(guint));
		*tam = g_hash_table_size(l->clientes);

		arraySize = (int)*tam;

		array = g_hash_table_get_keys_as_array (l->clientes, tam);
		arrayFinal = (char**)array;

		qsort(arrayFinal, arraySize, sizeof(char*), comp);
	
		while(arrayFinal[i])
		{
			printf("%s\n", arrayFinal[i]);	
			i++;
		}
}

char**
	listaToArray(List_Clientes l)
	{
		guint* tam = malloc(sizeof(guint));
		*tam = g_hash_table_size(l->clientes);

		return (char**)g_hash_table_get_keys_as_array(l->clientes, tam);
	}

gboolean
	clienteExisteNaLista(List_Clientes l, char* codCli)	
	{return g_hash_table_contains(l->clientes, codCli);}

char**
	produtosCompradosPorTodos(char** codSempre, List_Clientes l)
	{
		char *valueKey;
		GList* valores; 
		gboolean* array;
		int pos = 0;

		valores = g_hash_table_get_values(l->clientes);

		while(codSempre[pos])
			pos++;

		while(valores)
		{
			valueKey = getCodCli((Cliente)valores->data);
			array = getFilialCompra((Cliente)valores->data);

			if((array[0] == TRUE) && (array[1] == TRUE) && (array[2] == TRUE))
			{
				codSempre = realloc(codSempre, sizeof(char*) * (pos+2));
				codSempre[pos] = g_strdup(valueKey);	
				codSempre[pos+1] = NULL;	
				pos++;		
			}
			valores = valores->next;
		}
		return codSempre;
	}

static int 
	comp(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}