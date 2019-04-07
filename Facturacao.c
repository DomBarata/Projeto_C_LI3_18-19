#include <stdlib.h>
#include <stdio.h>
#include "Facturacao.h"

#define NUMFILIAIS 3

struct numeros
{
	int qtd[NUMFILIAIS];
	double precoTotal[NUMFILIAIS];
};
typedef struct numeros* Numeros;

struct cp
{
	GHashTable* info;
};
typedef struct cp* Fact_Info;

struct promocao
{
	Fact_Info ePromo[2];//0 - Venda N | 1 - Venda P
};
typedef struct promocao* Promo;

struct fact
{
	Promo mes[12];
};

static Fact_Info insereInfo(VendaUnica v, Fact_Info f);

Facturacao
	inicializa_Facturacao()
	{
		Facturacao f = malloc(sizeof(struct fact));

		for (int i = 0; i < 12; ++i)
		{
			f->mes[i] = malloc(sizeof(struct promocao));
			f->mes[i]->ePromo[FALSE] = malloc(sizeof(struct cp));
			f->mes[i]->ePromo[FALSE]->info = g_hash_table_new(g_str_hash, g_str_equal);
			f->mes[i]->ePromo[TRUE] = malloc(sizeof(struct cp));
			f->mes[i]->ePromo[TRUE]->info = g_hash_table_new(g_str_hash, g_str_equal);
		}
		return f;
	}

Facturacao
	insereNovaFacturacao(VendaUnica v, Facturacao f)
	{
		if(strcmp(getTipoVendas(v), "N") == 0)
			f->mes[getMesVendas(v)-1]->ePromo[FALSE] = insereInfo(v, f->mes[getMesVendas(v)-1]->ePromo[FALSE]);
		else
			f->mes[getMesVendas(v)-1]->ePromo[TRUE] = insereInfo(v, f->mes[getMesVendas(v)-1]->ePromo[TRUE]);

		return f;
	}

static Fact_Info
	insereInfo(VendaUnica v, Fact_Info f)
	{
		Numeros n;
		char* key;
		key = getCodProdVendas(v);
		n = g_hash_table_lookup(f->info, key);//segfault here
		if(!n)
		{
			n = malloc(sizeof(struct numeros));
			for (int i = 0; i < NUMFILIAIS; ++i)
			{
				n->qtd[i] = 0;
				n->precoTotal[i] = 0;
			}

			n->qtd[getFilialVendas(v)-1] = getQuantidadeVendas(v);
			n->precoTotal[getFilialVendas(v)-1] = getprecoUnitVendas(v) * getQuantidadeVendas(v);
			
			g_hash_table_insert(f->info, key, n);
		}
		else
		{
			n->qtd[getFilialVendas(v)-1] += getQuantidadeVendas(v);
			n->precoTotal[getFilialVendas(v)-1] += getprecoUnitVendas(v) * getQuantidadeVendas(v);
		}
		return f;
	}

int**
	getNumeroVendas(Facturacao f, int m, char* cod)
	{
		Numeros informacao[2];
		int** soma = malloc(sizeof(int*) * 2);
		soma[FALSE] = malloc(sizeof(int) * NUMFILIAIS);
		soma[TRUE] = malloc(sizeof(int) * NUMFILIAIS);

		for (int i = 0; i < NUMFILIAIS; ++i)
		{
			soma[FALSE][i] = 0;
			soma[TRUE][i] = 0;
		}

		informacao[FALSE] =  g_hash_table_lookup(f->mes[m-1]->ePromo[FALSE]->info, cod);
		informacao[TRUE] =  g_hash_table_lookup(f->mes[m-1]->ePromo[TRUE]->info, cod);

		for (int i = 0; i < NUMFILIAIS; ++i)
		{
			if(informacao[FALSE])
				soma[FALSE][i] = informacao[FALSE]->qtd[i];
			if(informacao[TRUE])
			soma[TRUE][i] = informacao[TRUE]->qtd[i];
		}
		
		return soma;
	}

double**
	getTotalFacturado(Facturacao f, int m, char* cod)
	{
		Numeros informacao[2];
		double** soma = malloc(sizeof(double*) * 2);
		soma[FALSE] = malloc(sizeof(double) * NUMFILIAIS);
		soma[TRUE] = malloc(sizeof(double) * NUMFILIAIS);

		for (int i = 0; i < NUMFILIAIS; ++i)
		{
			soma[FALSE][i] = 0;
			soma[TRUE][i] = 0;
		}

		informacao[FALSE] =  g_hash_table_lookup(f->mes[m-1]->ePromo[FALSE]->info, cod);
		informacao[TRUE] =  g_hash_table_lookup(f->mes[m-1]->ePromo[TRUE]->info, cod);

		for (int i = 0; i < NUMFILIAIS; ++i)
		{
			if(informacao[FALSE])
				soma[FALSE][i] = informacao[FALSE]->precoTotal[i];
			if(informacao[TRUE])
				soma[TRUE][i] = informacao[TRUE]->precoTotal[i];
		}

		return soma;
	}

