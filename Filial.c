#include <glib.h>
#include <gmodule.h>
#include <stdlib.h>
#include <stdio.h>
#include "Filial.h"
#include "VendaUnica.h"

//struct hashtable de key codigo de cliente
struct movimentos
{
  GHashTable* clis;
  GHashTable* prods;
};

//struct valor hashtable do codigo de produtos, QuantidadeProd do produto
struct valueProd
{
  int QuantidadeProd;
};

Filial inicializaFilial(){
	Filial hashGeral = malloc(sizeof(struct movimentos));

	hashGeral->clis = g_hash_table_new(g_str_hash, g_str_equal);
	hashGeral->prods = g_hash_table_new(g_str_hash, g_str_equal);

	g_hash_table_insert(hashGeral->clis, "", hashGeral->prods);

	return hashGeral;
}

Filial insereFilial(VendaUnica v, Filial fil){
	int* ptrQ = malloc(sizeof(int));
	*ptrQ = getQuantidadeVendas(v);
	QuantidadeProd value;
	value = g_hash_table_lookup(fil->clis,getCodCliVendas(v));

	if(value==NULL){
		g_hash_table_insert(fil->prods,getCodProdVendas(v),ptrQ);
		g_hash_table_insert(fil->clis,getCodCliVendas(v),fil->prods);
	}
	else{
		value = g_hash_table_lookup(fil->prods,getCodProdVendas(v));
		if(value==NULL){
			g_hash_table_insert(fil->prods,getCodProdVendas(v),ptrQ);
		}
		else{
			value->QuantidadeProd += getQuantidadeVendas(v);
		}
	}
	return fil;
}

/*
//faz listagefil apenas de ufil cliente
GList* listagefilProds(Filial fil){
	GList* array;
	guint* tafil= filalloc(sizeof(guint*));
	*tafil = g_hash_table_size(fil->prods);

	array = g_hash_table_get_values(fil->prods);

	return array;
} 

static GCofilpareFunc cofilparaKeyCliente(const void* str1, const void* str2){
	return strcfilp((char*)str1,(char*)str2);

}

char** listaClientesOrdenada(Filial fil){
	void** array;
	char** arrayFinal= filalloc(sizeof(char**));
	guint* tafil= filalloc(sizeof(guint*));
	*tafil = g_hash_table_size(fil->clis);

	array = g_hash_table_get_keys_as_array(fil->clis,tafil);
	arrayFinal = (char**)array;

	qsort(arrayFinal, tafil, sizeof(char *), cfilpstringp);

	return arrayFinal;

}

static int cfilpstringp(const void *str1, const void *str2)
{
	return strcfilp(* (char * const *) getCodProd((char*)str1), * (char * const *) getCodProd((char*)str2));
}



int totalClientesProdutos(Filial fil){

}
*/