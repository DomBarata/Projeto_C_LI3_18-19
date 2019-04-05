#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mainAuxFunc.h"
#include "Produto.h"
#include "Cliente.h"
#include "VendaUnica.h"

#define BUFFER 			20
#define BUFFERVENDAS 	50
#define LINHASPRODUTOS 	200000
#define LINHASCLIENTES 	20000
#define LINHASVENDAS 	1000000

struct vendasVarias
{
	Facturacao fact;
	Filial fil[NUMFILIAIS];
};
CatProdutos 
	criaCatalogoProdutos(CatProdutos catp)
	{
		FILE* fp;
		char str[BUFFER];
		int i = 0;
		Produto p;

		fp = fopen("Files/Produtos.txt", "r");
		if(fp == NULL)	
		{
			perror("I/O error"); 
			catp = NULL;
		}	
		else
		{
			while(fgets(str, BUFFER, fp) && i < LINHASPRODUTOS)
			{
				strtok(str, "\n\r");
				p = criaProduto(str);
				if(verificaProduto(p))
					catp = insereProdutos(catp, p);			
				i++;
			}
			fclose(fp);
		}
		return catp;
	}

CatClientes 
	criaCatalogoClientes(CatClientes catc)
	{
		FILE* fp;
		char str[BUFFER];
		int i = 0;
		Cliente c;

		fp = fopen("Files/Clientes.txt", "r");
		if(fp == NULL)	
		{
			perror("I/O error"); 
			catc = NULL;
		}	
		else
		{
			while(fgets(str, BUFFER, fp) && i < LINHASCLIENTES)
			{
				strtok(str, "\n\r");
				c = criaCliente(str);
				if(verificaCliente(c))
					catc = insereClientes(catc, c);			
				i++;
			}
			fclose(fp);
		}
		return catc;
	}

VendasFactEFil
	criaVendasDivididas(CatProdutos catp, CatClientes catc)
	{
		FILE* fp;
		VendaUnica v;
		char str[BUFFERVENDAS];
		int i = 0;

		VendasFactEFil ven = malloc(sizeof(struct vendasVarias));
		ven->fact = inicializa_Facturacao();
		for (int j = 0; j < NUMFILIAIS; ++j)
		{
			ven->fil[j] = inicializaFilial();
		}			

		fp = fopen("Files/Vendas_1M.txt", "r");
		if(fp == NULL)
		{
			perror("I/O error");
			ven = NULL;
		}
		else
		{
			while(fgets(str, BUFFERVENDAS, fp) && i < LINHASVENDAS)
			{
				v = divideLinhasDeVenda(str, catp, catc);
				if(v)
				{
					ven->fact = insereNovaFacturacao(v, ven->fact);
					ven->fil[getFilialVendas(v)-1] = insereFilial(v, ven->fil[getFilialVendas(v)-1]);
				}
				i++;
			}
			fclose(fp);
		}
		return ven;
	}

Facturacao
	GeraFact(VendasFactEFil vF) {return vF->fact;}

Filial //dentro de um ciclo for lim=3
	GeraUmaFilial(VendasFactEFil vF, int i) {return vF->fil[i];}

SGV 
	CriaSGV(CatProdutos catp, CatClientes catc, Facturacao f, Filial* fil)
	{
		SGV interface = malloc(sizeof(struct sgv));
		interface->cp = catp;
		interface->ccli = catc;
		interface->fact = f;
		interface->filiais[0] = fil[0];
		interface->filiais[1] = fil[1];
		interface->filiais[2] = fil[2];

		return interface;
	}