#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Facturacao.h"

struct cp
{
	GHashTable* info;
};
typedef struct cp* Fact_Info;

struct numeros
{
	int qtd;
	double preco;
};
typedef struct numeros* Numeros;

struct promocao
{
	Fact_Info ePromo[2];//0 - Venda N | 1 - Venda P
};
typedef struct promocao* Promo;

struct fact
{
	Promo mes[12];
};

static double getPrecoTotal(Numeros n);
static void getValorFaturado(gpointer key, gpointer value, gpointer userdata);
static Fact_Info insereInfo(VendaUnica v, Fact_Info f);

Facturacao
	inicializa_Facturacao()
	{
		Facturacao f = malloc(sizeof(struct fact));

		for (int i = 0; i < 12; ++i)
		{
			f->mes[i] = malloc(sizeof(struct promocao));
			f->mes[i]->ePromo[0] = malloc(sizeof(struct cp));
			f->mes[i]->ePromo[0]->info = g_hash_table_new(g_str_hash, g_str_equal);
			f->mes[i]->ePromo[1] = malloc(sizeof(struct cp));
			f->mes[i]->ePromo[1]->info = g_hash_table_new(g_str_hash, g_str_equal);
		}
		return f;
	}

Facturacao
	insereNovaFacturacao(VendaUnica v, Facturacao f)
	{
		int pos = getMesVendas(v)-1;

		if(strcmp(getTipoVendas(v), "N") == 0)
			f->mes[pos]->ePromo[0] = insereInfo(v, f->mes[pos]->ePromo[0]);
		else
			f->mes[pos]->ePromo[1] = insereInfo(v, f->mes[pos]->ePromo[1]);

		return f;
	}

static Fact_Info
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

int
	getTamanhoListaFactMes(Facturacao f, int m)
	{
		int total = 0;
		int* tamN = malloc(sizeof(int));
		int* tamP = malloc(sizeof(int));

		*tamN = g_hash_table_size(f->mes[m]->ePromo[0]->info);
		*tamP = g_hash_table_size(f->mes[m]->ePromo[1]->info);

		total = *tamN+*tamP;

		return total;
	}

double
	totalFaturadoMes(Facturacao f, int m)
	{
		void *t;
		double* total;
		tam = g_hash_table_size(f->mes[m]->ePromo[0]->info);
		for(int i=0;i<tam;i++){

			getValorFaturado(g_hash_table_lookup(f->mes[m]->ePromo[0]->info))
		}
		total = (double*)t;

		return *total;
	}

static void 
	getValorFaturado(Numeros n)
	{
		return total = n->preco * n->qtd;
	}


char**
	getKeysFact(Facturacao fact)
	{
		void** array = malloc(sizeof(void**));
		char** arrayFact = malloc(sizeof(char**));
		guint* tam = malloc(sizeof(guint));
		int count = 0;

		for(int i=0; i<12; i++){
			for(int j=0; j<2; j++){
				*tam = g_hash_table_size(fact->mes[i]->ePromo[j]->info);

				array = g_hash_table_get_keys_as_array(fact->mes[i]->ePromo[j]->info,tam);
				count++;
			}
		}
		arrayFact = (char**)array;

		return arrayFact;
	}





