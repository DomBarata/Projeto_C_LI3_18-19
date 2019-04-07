#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Filial.h"
#include "VendaUnica.h"

struct values
{
	int quantidade;
	int nVendas;
};
typedef struct values* Values;

struct aux
{
	GHashTable* prods[2];
};
typedef struct aux* AuxProds;

struct clientesFil
{
	GHashTable* clis;
};
typedef struct clientesFil* ClientesFilial;

struct filMes
{
	ClientesFilial mes[12];
};


Filial
	inicializaFilial()
	{
		Filial f= malloc(sizeof(struct filMes));;
		for (int i = 0; i < 12; ++i)
		{
			f->mes[i] = malloc(sizeof(struct clientesFil));
			f->mes[i]->clis = g_hash_table_new(g_str_hash, g_str_equal);
		}
		return f;
	}

Filial 
	insereFilial(VendaUnica v, Filial f)
	{
		AuxProds hashAux, ajuda = malloc(sizeof(struct aux));
		Values valAux, val = malloc(sizeof(struct values));
		gboolean promo;
		if (strcmp(getTipoVendas(v), "N") == 0)
			promo = FALSE;
		else
			promo = TRUE;

		val->quantidade = getQuantidadeVendas(v);
		val->nVendas = 1;

		hashAux = g_hash_table_lookup(f->mes[getMesVendas(v)-1]->clis, getCodCliVendas(v));

		if(hashAux)
		{
			valAux = g_hash_table_lookup(hashAux->prods[promo], getCodProdVendas(v));
			if (valAux)
			{
				valAux->quantidade += getQuantidadeVendas(v);
				valAux->nVendas++;
			}
			else
			{
				g_hash_table_insert(hashAux->prods[promo], getCodProdVendas(v), val);
			}
		}
		else
		{
			
			ajuda->prods[0] = g_hash_table_new(g_str_hash, g_str_equal);
			ajuda->prods[1] = g_hash_table_new(g_str_hash, g_str_equal);

			g_hash_table_insert(ajuda->prods[promo], getCodProdVendas(v), val);
			g_hash_table_insert(f->mes[getMesVendas(v)-1]->clis, getCodCliVendas(v), ajuda);
		}
		return f;
	}

int
	quantidadeClienteMes(Filial fil, int m, char* codCli)
	{
		AuxProds hashAux;
		GList* listaN = NULL, *listaP = NULL;
		Values valN, valP, emBranco = malloc(sizeof(struct values));
		int soma = 0;

		emBranco->quantidade = 0;
		emBranco->nVendas = 0;

		hashAux = g_hash_table_lookup(fil->mes[m]->clis, codCli);
	
		if(hashAux)
		{
			listaN = g_hash_table_get_values(hashAux->prods[0]);
			listaP = g_hash_table_get_values(hashAux->prods[1]);
		}

		while(listaN || listaP)
		{	
			if(listaN)
				valN = (Values) listaN->data; 
			else
				valN = emBranco;
			if(listaP)
				valP = (Values) listaP->data; 
			else
				valP = emBranco;
			
			soma += valN->quantidade + valP->quantidade;

			if(listaN)
				listaN = listaN->next;
			if(listaP)
				listaP = listaP->next;
		}
		return soma;
	}