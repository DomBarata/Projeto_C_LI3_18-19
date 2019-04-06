#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "Facturacao.h"
#include "Queries.h"

static int menu();
static SGV Query1(SGV gestao);

void
	runQueries(SGV gestao)
	{
		gboolean flag = TRUE;
		//gestao = Query1(gestao);

		do
		{
			switch(menu())
			{
				case 1: gestao = Query1(gestao);
						break;
				case 2: break;
				case 3: break;
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
			printf("Query 1 - \n");
			printf("Query 2 - \n");
			printf("Query 3 - \n");
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
	Query1(SGV gestao)
	{
		system("clear");
		char* fileProd, *fileCli, *fileVendas;
		char files[100];
		VendasFactEFil auxStruct;

		printf("Insira o nome dos 3 ficheiros separados unicamente por um espaço\n(ex.: fileProdutos.txt fileClientes.txt fileVendas.txt)\n\n");
		fgets(files, 100, stdin);
		strtok(files, "\n\r");

		fileProd = strtok(files, " ");
		fileCli = strtok(NULL, " ");
		fileVendas = strtok(NULL, " ");
		
		printf("%s\n",fileProd);
		printf("%s\n",fileCli);
		printf("%s\n",fileVendas);

		gestao->cp = criaCatalogoProdutos(gestao->cp, fileProd);

		gestao->ccli = criaCatalogoClientes(gestao->ccli, fileCli);

		auxStruct = criaVendasDivididas(gestao->cp, gestao->ccli, fileVendas);

		gestao->fact = GeraFact(auxStruct);
		for (int i = 0; i < NUMFILIAIS; ++i)
			gestao->filiais[i] = GeraUmaFilial(auxStruct, i);

		return gestao;
	}


