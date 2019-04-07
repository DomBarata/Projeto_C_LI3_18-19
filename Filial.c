#include <glib.h>
#include <gmodule.h>
#include <stdlib.h>
#include <stdio.h>
#include "Filial.h"
#include "VendaUnica.h"

//struct hashtable de key codigo de cliente
struct prodsCli
{
  GHashTable* clis;
  GHashTable* prods;
};
typedef struct prodsCli* ProdsCli;

struct filMes
{
	ProdsCli mes[12];
};

Filial inicializaFilial(){
	Filial fil = malloc(sizeof(struct filMes));

	for(int i=0; i<12; i++){
		fil->mes[i] = malloc(sizeof(struct prodsCli));
		fil->mes[i]->clis = g_hash_table_new(g_str_hash, g_str_equal);
		fil->mes[i]->prods = g_hash_table_new(g_str_hash, g_str_equal);
	}

	return fil;
}

Filial insereFilial(VendaUnica v, Filial fil){
	int* ptrQ = malloc(sizeof(int));
	*ptrQ = getQuantidadeVendas(v);
	int pos = getMesVendas(v)-1;
	ProdsCli value = malloc(sizeof(struct prodsCli));
	value = g_hash_table_lookup(fil->mes[pos]->clis,getCodCliVendas(v));
	int* valorProd;

	if(value==NULL){
		g_hash_table_insert(fil->mes[pos]->prods,getCodProdVendas(v),ptrQ);
		g_hash_table_insert(fil->mes[pos]->clis,getCodCliVendas(v),fil->mes[pos]->prods);
	}
	else{
		valorProd = g_hash_table_lookup(fil->mes[pos]->prods,getCodProdVendas(v));
		if(valorProd==NULL){
			g_hash_table_insert(fil->mes[pos]->prods,getCodProdVendas(v),ptrQ);
		}
		else{
			*valorProd += getQuantidadeVendas(v);
		}
	}
	return fil;
}

int
	prodsClienteMes(Filial fil, int m, char* codCli)
	{
		ProdsCli produtosComprados = malloc(sizeof(struct prodsCli));
		GList* values;
		int soma = 0;

		produtosComprados->prods = g_hash_table_lookup(fil->mes[m]->clis,codCli);

		if(produtosComprados->prods != NULL){
			values = g_hash_table_get_values(produtosComprados->prods);

			while(values)
			{	
				soma += *(int*)values->data;
				values = values->next;
			}
		}
		else{
			printf("ok\n");
		}

		return soma;
	}