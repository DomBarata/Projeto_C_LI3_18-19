#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VendaUnica.h"


static gboolean verifica(char** campos, CatProdutos catp, CatClientes catc);

struct venda
{
	char* codProd;
	char* codCli;
	double precoUnit;
	int quantidade;
	char* tipo;
	int mes;
	int filial;
};

VendaUnica 
	divideLinhasDeVenda(char* str, CatProdutos catp, CatClientes catc)
	{
		VendaUnica v = malloc(sizeof(struct venda));
		char* campos[7];
		char* strAux;
		long int i = 0;
//		int len = strlen(str);
//		char linha[len+1];
//		strcpy(linha, str);

		strAux = strtok(str, " ");
		while(!(strAux == NULL))
		{
			campos[i] = g_strdup(strAux);
			strAux = strtok(NULL, " ");
			i++;	
		}

		if (verifica(campos, catp, catc))
		{
			v->codProd = g_strdup(campos[0]);
			v->codCli = g_strdup(campos[4]);
			v->precoUnit = atof(campos[1]);
			v->quantidade = atoi(campos[2]);
			v->tipo = campos[3];
			v->mes = atoi(campos[5]);
			v->filial = atoi(campos[6]);
		}
		else
			v = NULL;
	
		return v;
	}

static gboolean 
	verifica(char** campos, CatProdutos catp, CatClientes catc)
	{
		int check = 1;
		float preco = atof(campos[1]);
		int quant = atoi(campos[2]);
		char *c = campos[3];
		int mes = atoi(campos[5]);
		int filial = atoi(campos[6]);

		if(!(preco >= 0 && preco <= 999.99))
			check = 0;
		if(!(quant >= 1 && quant <=200))
			check = 0;
		if(!(strcmp("N", c) || strcmp(c,"P")))
			check = 0;
		if(!(mes >= 1 && mes <=12))
			check = 0;
		if(!(filial >= 1 && filial <=3))
			check = 0;
		if(!produtoExisteNoCatalogo(catp, campos[0]))
			check = 0;
		if(!clienteExisteNoCatalogo(catc, campos[4]))
			check = 0;

		return check;
	}

void 
	printVenda(VendaUnica v)
	{
		printf("%s\n", v->codProd);
		printf("%s\n", v->codCli);
		printf("%f\n", v->precoUnit);
		printf("%d\n", v->quantidade);
		printf("%s\n", v->tipo);
		printf("%d\n", v->mes);
		printf("%d\n", v->filial);
	}

char*
	getCodProdVendas(VendaUnica v)	{return v->codProd;}

char*
	getCodCliVendas(VendaUnica v)	{return v->codCli;}

double
	getprecoUnitVendas(VendaUnica v)	{return v->precoUnit;}

int
	getQuantidadeVendas(VendaUnica v)	{return v->quantidade;}

char*
	getTipoVendas(VendaUnica v)	{return v->tipo;}

int
	getMesVendas(VendaUnica v)	{return v->mes;}

int
	getFilialVendas(VendaUnica v)	{return v->filial;}
