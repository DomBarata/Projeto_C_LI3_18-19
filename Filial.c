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

char**
	cClienteQueCompraramOProduto(Filial f, CatClientes catc, char* codProd, gboolean promo)
	{
		AuxProds estrutura;
		List_Clientes l;
		char** clientesQueCompraram = malloc(sizeof(char*));
		clientesQueCompraram[0] = NULL;
		char** arrayClientes[26];
		int i = 0, j = 0, k = 0, dim = 0;

		for (i = 0; i < 26; ++i)
		{
			l = listaPorLetraClientes(catc, i + 'A');
			arrayClientes[i] = listaToArray(l);
		}

		i = 0;
		while(arrayClientes[i])
		{
			j = 0;
			while(arrayClientes[i][j])
			{
				k = 0;
				while(k <12)
				{
					if(g_hash_table_contains(f->mes[k]->clis, arrayClientes[i][j]))
					{
						estrutura = g_hash_table_lookup(f->mes[k]->clis, arrayClientes[i][j]);
						if(g_hash_table_contains(estrutura->prods[promo], codProd))
						{
							clientesQueCompraram[dim] = g_strdup(arrayClientes[i][j]);
							clientesQueCompraram = realloc(clientesQueCompraram, (sizeof(char*)*(dim+2)));
							clientesQueCompraram[dim+1] = NULL;
							dim++;
						}
					}
					k++;
				}
				j++;
			}
			i++;
		}
		return clientesQueCompraram;
	}

char**
	getProdutos(Filial f, char* cod)
	{
		AuxProds estrutura;
		int k = 0, dim = 0, j = 0, p = 0;
		char** produtos = malloc(sizeof(char*));
		char** keys;
		guint* tam = malloc(sizeof(guint));
		produtos[0] = NULL;

		while(k < 12)
		{
			if(g_hash_table_contains(f->mes[k]->clis, cod))
			{
				estrutura = g_hash_table_lookup(f->mes[k]->clis, cod);
				p = 0;
				while(p < 2)
				{
					*tam = g_hash_table_size(estrutura->prods[p]);

					keys = (char**)g_hash_table_get_keys_as_array(estrutura->prods[p], tam);
					j = 0;
					while(keys[j])
					{
						produtos[dim] = g_strdup(keys[j]);
						produtos = realloc(produtos, (sizeof(char*)*(dim+2)));
						produtos[dim+1] = NULL;
						dim++;

						j++;
					}
					p++;
				}
			}
			k++;
		}
	return produtos;
	}

int*
	getQuantidades(Filial f, char* cod)
	{
		AuxProds estrutura;
		Values v;
		int k = 0, dim = 0, j = 0, p = 0;
		int* quantidades = malloc(sizeof(int));
		char** keys;
		guint* tam = malloc(sizeof(guint));
		quantidades[0] = 0;

		while(k < 12)	//12 meses
		{
			if(g_hash_table_contains(f->mes[k]->clis, cod))	//se a HashTable clientes tiver aquele codigo
			{
				estrutura = g_hash_table_lookup(f->mes[k]->clis, cod);	//HashTable Produtos
				p = 0;
				while(p < 2)	//promo e nao promo
				{
					*tam = g_hash_table_size(estrutura->prods[p]);

					keys =(char**) g_hash_table_get_keys_as_array(estrutura->prods[p], tam);
					j = 0;
					while(keys[j])
					{
						v = g_hash_table_lookup(estrutura->prods[p], keys[j]);
						quantidades[dim] = v->quantidade;
						quantidades = realloc(quantidades, (sizeof(int)*(dim+2)));
						quantidades[dim+1] = 0;
						dim++;

						j++;
					}
					p++;
				}
			}
			k++;
		}
	return quantidades;
	}