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

Facturacao
	criaFacturacao(Facturacao fact, CatProdutos catp, CatClientes catc)
	{
		FILE* fp;
		VendaUnica v;
		char str[BUFFERVENDAS];
		int i = 0;

		fp = fopen("Files/Vendas_1M.txt", "r");
		if(fp == NULL)
		{
			perror("I/O error");
			fact = NULL;
		}
		else
		{
			while(fgets(str, BUFFERVENDAS, fp) && i < LINHASVENDAS)
			{
				v = divideLinhasDeVenda(str, catp, catc);
				printVenda(v);
				if(v)
					fact = insereNovaFacturacao(v, fact);
				i++;
			}
			fclose(fp);
		}
		return fact;
	}
