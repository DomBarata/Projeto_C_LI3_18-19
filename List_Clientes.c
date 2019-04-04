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
		int *val = malloc(sizeof(int));
		*val = 1;
 		g_hash_table_insert(l->clientes, getCodCli(c), val);

	    return l;
	}

void 
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

gboolean
	clienteExisteNaLista(List_Clientes l, char* codCli)	
	{return g_hash_table_contains(l->clientes, codCli);}

static int 
	comp(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}