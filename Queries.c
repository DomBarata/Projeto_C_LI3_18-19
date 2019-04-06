#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Facturacao.h"
#include "Queries.h"

static int menu();
static SGV Query1(SGV gestao, char* files);
static void Query2(SGV gestao);
static void Query3(SGV gestao);

void
	runQueries(SGV gestao)
	{
		gboolean flag = TRUE;
		char files[100] = "";

		gestao = Query1(gestao, files);

		do
		{
			switch(menu())
			{
				case 1: printf("Insira o nome dos 3 ficheiros separados unicamente por um espaço\n(ex.: fileProdutos.txt fileClientes.txt fileVendas.txt)\n\n");
						fgets(files, 100, stdin);
						gestao = Query1(gestao, files);
						break;
				case 2: Query2(gestao);
						break;
				case 3: Query3(gestao);
						break;
				case 4: break;
				case 5: break;
				case 6: break;
				case 7: break;
				case 8: break;
				case 9: break;
				case 10: break;
				case 11: break;
				case 12: break;
				case 0: flag = FALSE;
						break;
			}
		}
		while(flag);
	}

static int
	menu()
	{
		int choice = 0;
		do
		{
			system("clear");
			if (choice < 0 && choice > 12)
			{
				printf("Opção selecionada não existe, por favor estolha outra\n\n");
			}
			printf("\t---------MENU---------\n\n");
			printf("Query 1 - Fazer leitura de outros ficheiros de dados\n");
			printf("Query 2 - Consulta produtos do catalogo\n");
			printf("Query 3 - Consulta vendas de produtos\n");
			printf("Query 4 - \n");
			printf("Query 5 - \n");
			printf("Query 6 - \n");
			printf("Query 7 - \n");
			printf("Query 8 - \n");
			printf("Query 9 - \n");
			printf("Query 10 - \n");
			printf("Query 11 - \n");
			printf("Query 12 - \n");
			printf("0 - Sair\n");
			scanf("%d", &choice);
			getchar();
		}
		while(choice < 0 && choice > 12);

		return choice;
	}

static SGV
	Query1(SGV gestao, char* files)
	{
		system("clear");
		char* fileProd, *fileCli, *fileVendas;
		VendasFactEFil auxStruct;

		if(!strcmp(files, "\n\r"))
		{
			fileProd = NULL;
			fileCli = NULL;
			fileVendas = NULL;
		}
		else
		{
			strtok(files, "\n\r");
			fileProd = strtok(files, " ");
			fileCli = strtok(NULL, " ");
			fileVendas = strtok(NULL, " ");
		}

		printf("Ficheiro de produtos: \"%s\", ",fileProd?fileProd:"Files/Produtos.txt");
		printf("Ficheiro de clientes: \"%s\", ",fileCli?fileCli:"Files/Clientes.txt");
		printf("Ficheiro de Vendas: \"%s\"\n",fileVendas?fileVendas:"Files/Vendas_1M.txt");

		gestao->cp = criaCatalogoProdutos(gestao->cp, fileProd);

		gestao->ccli = criaCatalogoClientes(gestao->ccli, fileCli);

		auxStruct = criaVendasDivididas(gestao->cp, gestao->ccli, fileVendas);

		gestao->fact = GeraFact(auxStruct);
		for (int i = 0; i < NUMFILIAIS; ++i)
			gestao->filiais[i] = GeraUmaFilial(auxStruct, i);

		printf("(Prima ENTER para continuar...)"); getchar();
		return gestao;
	}

static void
	Query2(SGV gestao)
	{
		system("clear");
		List_Produtos l;
		char letra;

		printf("Insira a inicial dos produto que pretende listar\n");
		scanf("%c", &letra);
		getchar();

		l = listaPorLetraProdutos(gestao->cp, letra);
		consultarProdutos(l);
	}

static void
	Query3(SGV gestao)
	{	
		system("clear");
		int j = 0; 
		int mes, check, soma = 0;
		int** nVendas;
		double** totalFact, somaFact = 0;
		char cod[7];

		printf("Insira o mês:\n");
		scanf("%d", &mes);
		getchar();
		printf("Insira o codigo do produto\n");
		scanf("%s", cod);
		getchar();
		printf("Apresentar resultados:\n");
		printf("\t 1 - Globais\n");
		printf("\t 2 - Filial a Filial\n");
		scanf("%d", &check);
		getchar();
		
		nVendas = getNumeroVendas(gestao->fact, mes, cod);

		totalFact = getTotalFacturado(gestao->fact, mes, cod);

		if(check-1 == 0) //MODO GLOBAL	
		{
			system("clear");
			printf("O produto %s foi vendido no mes %d:\n", cod, mes);
			
			for (int k = 0; k < NUMFILIAIS; ++k)
				soma += nVendas[FALSE][k];
			for (int k = 0; k < NUMFILIAIS; ++k)
				somaFact += totalFact[FALSE][k];
			printf("%dx com preço Normal - %0.2fEUR em facturacao\n", soma, somaFact);

			soma = 0;
			somaFact = 0;

			for (int k = 0; k < NUMFILIAIS; ++k)
				soma += nVendas[TRUE][k];
			for (int k = 0; k < NUMFILIAIS; ++k)
				somaFact += totalFact[TRUE][k];
			printf("%dx com preço Promocional - %0.2fEUR em facturacao\n\n", soma, somaFact);
		}
		else	//MODO FILIAL
		{
			system("clear");
			printf("O produto %s foi vendido no mes %d em:\n", cod, mes);
			for(int i = 0; i < NUMFILIAIS; i++)
			{
				if (nVendas[FALSE][i] + nVendas[TRUE][i])
				{
					printf("-----FILIAL %d-----\n", i+1);
					printf("%dx com preço Normal - %0.2fEUR em facturacao\n", nVendas[FALSE][i], totalFact[FALSE][i]);
					printf("%dx com preço Promocional - %0.2fEUR em facturacao\n\n", nVendas[TRUE][i], totalFact[TRUE][i]);			
					j++;
				}
			}
			if (!j)
			{
				printf("O produto \"%s\" não foi vendido no mes %d em nenhuma filial\n\n", cod, mes);
			}
		}
		printf("(Prima ENTER para continuar...)"); getchar();
	}