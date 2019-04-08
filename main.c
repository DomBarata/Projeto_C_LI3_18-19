/*
 *Auhors: Tiago Barata e Melânia Pereira
 *Projeto no ambito da UC LI3
 *Last Edit: 08/04/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "main.h"
#include "Queries.h"

struct vendasVarias
{
	Facturacao fact;
	Filial fil[NUMFILIAIS];
};

int 
	main()
	{
		SGV gestao = inicializaSGV();

		runQueries(gestao);

	 	return 0;
	}

CatProdutos 
	criaCatalogoProdutos(CatProdutos catp, char* fileRead)
	{
		FILE* fp;
		char str[BUFFER];
		int linhasLidas = 0;
		Produto p;

		if(fileRead == NULL)	//caso nao sejam passados argumentos, assume-se o ficheiro
			fileRead = g_strdup("Files/Produtos.txt");

		fp = fopen(fileRead, "r");
		if(fp == NULL)	//caso nao exista o ficheiro o programa termina com um erro
		{
			perror("File de produtos inexistente"); 
			catp = NULL;
			exit(1);
		}	
		else
		{
			while(fgets(str, BUFFER, fp) && linhasLidas < LINHASPRODUTOS)
			{
				strtok(str, "\n\r");
				p = criaProduto(str);

				if(verificaProduto(p))	//apenas insere se a linha estiver bem construida
					catp = insereProdutos(catp, p);	

				linhasLidas++;
			}
			fclose(fp);
			printf("Do ficheiro \"%s\" foram lidas %d linhas, sendo %d validas\n", fileRead, linhasLidas, getProdutosLidos(catp));

		}
		return catp;
	}

CatClientes 
	criaCatalogoClientes(CatClientes catc, char* fileRead)
	{
		FILE* fp;
		char str[BUFFER];
		int linhasLidas = 0;
		Cliente c;

		if(fileRead == NULL)
			fileRead = g_strdup("Files/Clientes.txt");

		fp = fopen(fileRead, "r");
		if(fp == NULL)	
		{
			perror("File de clientes inexistente"); 
			catc = NULL;
			exit(1);
		}	
		else
		{
			while(fgets(str, BUFFER, fp) && linhasLidas < LINHASCLIENTES)
			{
				strtok(str, "\n\r");
				c = criaCliente(str);
				if(verificaCliente(c))
					catc = insereClientes(catc, c);			
				linhasLidas++;
			}
			fclose(fp);
			printf("Do ficheiro \"%s\" foram lidas %d linhas, sendo %d validas\n", fileRead, linhasLidas, getClientesLidos(catc));
		}
		return catc;
	}

VendasFactEFil
	criaVendasDivididas(CatProdutos catp, CatClientes catc, char* fileRead)
	{
		FILE* fp;
		VendaUnica v;
		char str[BUFFERVENDAS];
		int linhasLidas = 0, linhasValidas = 0;

		VendasFactEFil ven = malloc(sizeof(struct vendasVarias));
		ven->fact = inicializa_Facturacao();
		for (int j = 0; j < NUMFILIAIS; ++j)
		{
			ven->fil[j] = inicializaFilial();
		}			

		if(fileRead == NULL)
			fileRead = g_strdup("Files/Vendas_1M.txt");


		fp = fopen(fileRead, "r");
		if(fp == NULL)
		{
			perror("File de vendas inexistente");
			ven = NULL;
			exit(1);
		}
		else
		{
			while(fgets(str, BUFFERVENDAS, fp) && linhasLidas < LINHASVENDAS)
			{
				v = divideLinhasDeVenda(str, catp, catc);
				if(v)
				{
					//atualizacao das flags de filiais em catalogo
					catp = setCatProdutos(catp, getCodProdVendas(v), getFilialVendas(v));
					catc = setCatClientes(catc, getCodCliVendas(v), getFilialVendas(v));

					//cria a faturacao e as filiais na estrutura de dados auxiliar
					ven->fact = insereNovaFacturacao(v, ven->fact);
					ven->fil[getFilialVendas(v)-1] = insereFilial(v, ven->fil[getFilialVendas(v)-1]);

					//conta as linhas que foram escritas na estrutura
					linhasValidas++;
				}
				//conta as linhas do ficheiro
				linhasLidas++;
			}
			fclose(fp);
			printf("Do ficheiro \"%s\" foram lidas %d linhas, sendo %d validas\n", fileRead, linhasLidas, linhasValidas);
		}
		return ven;
	}

Facturacao
	GeraFact(VendasFactEFil vF) {return vF->fact;}

Filial //dentro de um ciclo for lim=NUMFILIAIS
	GeraUmaFilial(VendasFactEFil vF, int i) {return vF->fil[i];}

SGV
	inicializaSGV()
	{
		SGV gestao = malloc(sizeof(struct sgv));
		//inicializacao das esruturas
		gestao->cp = inicializa_CatProdutos();
		gestao->ccli = inicializa_CatClientes();
		gestao->fact = inicializa_Facturacao();
		for (int i = 0; i < NUMFILIAIS; ++i)
			gestao->filiais[i] = inicializaFilial();

		return gestao;
	}
