#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Fact_Info.h"

typedef struct numeros* Numeros;

struct cp
{
	GHashTable* info;
};

struct numeros
{
	int qtd;
	double preco;
};

Fact_Info
	inicializa_Fact_Info()
	{
		Fact_Info f = malloc(sizeof(struct cp));
		f->info = g_hash_table_new(g_str_hash, g_str_equal);

		return f;
	}

Fact_Info
	insereInfo(VendaUnica v, Fact_Info f)
	{
		Numeros n;
		char* key;
		key = getCodProdVendas(v);
		n = g_hash_table_lookup(f->info, key);//segfault here
		if(n == NULL)
		{
			n = malloc(sizeof(struct numeros));
			n->qtd = getQuantidadeVendas(v);
			n->preco = getprecoUnitVendas(v);


			g_hash_table_insert(f->info, key, n);
		}
		else
		{
			n->qtd += getQuantidadeVendas(v);
			n->preco += getprecoUnitVendas(v);
		}
		return f;
	}