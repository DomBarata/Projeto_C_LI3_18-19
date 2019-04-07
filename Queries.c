#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Facturacao.h"
#include "Queries.h"

static int menu();

static SGV Query1(SGV gestao, char* files);
static void Query2(SGV gestao);
static void Query4(SGV gestao);
static void Query8(SGV gestao, char* meses);

static int totalVendasRegistadas(Facturacao fact, int i);
static double* totalFaturado(Facturacao fact, int mes);

void
	runQueries(SGV gestao)
	{
		gboolean flag = TRUE;
		char files[100] = "";
		char meses[10] = "";

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
				case 3: break;
				case 4: Query4(gestao);
						break;
				case 5: break;
				case 6: break;
				case 7: break;
				case 8: printf("Indique de que mês a que mês pretende nhenhe (separados apenas por espaço): \n");
						fgets(meses,10,stdin);
						Query8(gestao,meses);
						break;
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
		List_Produtos l;
		char letra;

		printf("Insira a inicial dos produto que pretende listar\n");
		scanf("%c", &letra);
		getchar();

		l = listaPorLetraProdutos(gestao->cp, letra);
		consultarProdutos(l);
	}


static void 
	Query4(SGV gestao)
	{
		List_Produtos l[26];
		for(int i=0;i<26;i++){
		char*** array = malloc(sizeof((int)*3));
		for(int i=0;i<26;i++){
			 array = descobreNaoVendidos(l[i])
		}

		do{
			printf("Pretende o numero de produtos:\n");
			printf("1 - Total\n");
			printf("2 - Dividido pelas filiais\n");
			printf("0 - Sair\n");
			scanf("%d",&c);
			getchar();
			printf("%d\n",c);

			if(c==1){
				printf("Número total de produtos não comprados: %d\n\n", count);
				printf("Prima enter para ver a lista de produtos!\n");
				getchar();
				for(int i=0; i<3; i++){
					consultarProdutos(prodsNaoComprados[i]);
				}
			}
			if(c==2)
			{
				for (int i = 0; i < 3; ++i)
				{
					tam = dimensaoLista(prodsNaoComprados[i]);
					printf("Número de produtos não comprados na filial %d: %d\n\n", (i+1), tam);
					char** array[3];
					for(int i=0; i<3; i++){
					tam = dimensaoLista(prodsNaoComprados[i]);
					array[i]=getKeysAsArrayLista(prodsNaoComprados[i]);
					for(int j=0; j<tam; j++){
						printf("%s\n",array [i][j]);
					}
				}
				}
				printf("\n\n");
			}
			if(c!=1 && c!=2 && c!=0){
				printf("Por favor, escolha um dos números indicados!\n\n");
			}
		}while(c!=0);
}

static void Query8(SGV gestao, char* meses)
{	
	char* mes1, *mes2;
	mes1 = strtok(meses," ");
	mes2 = strtok(NULL," ");

	int m1 = 0, m2 = 0;
	m1 = atoi(mes1);
	m2 = atoi(mes2);

		printf("%d\n", m1);
		printf("%d\n", m2);
	int totalVendas = 0;
	double* totalFact = 0;
	double* aux = 0;
	for(int i=m1; i<m2; i++){
		printf("%d\n", i);
		totalVendas += totalVendasRegistadas(gestao->fact, i);
		aux = totalFaturado(gestao->fact, i);
		*totalFact += *aux;
	}

}

static int
	totalVendasRegistadas(Facturacao f, int i)
	{return getTamanhoListaFactMes(f, i);}

static double*
	totalFaturado(Facturacao f, int mes)
	{
	double* total = 0;
	*total = totalFaturadoMes(f, mes);

	return total;
	}
