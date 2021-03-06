#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Facturacao.h"
#include "Queries.h"

#define PAGINACAO 25

static int menu();
static SGV Query1(SGV gestao, char* files);
static void Query2(SGV gestao);
static void Query3(SGV gestao);
static void Query4(SGV gestao);
static void	Query5(SGV gestao);
static void Query6(SGV gestao);
static void Query7(SGV gestao);
static void Query8(SGV gestao);
static void Query9(SGV gestao);
static void Query10(SGV gestao);	//Nao esta a 100% - Falta juntar as quantidades dos produtos com os mesmo codigo

static void Query12(SGV gestao);	//Nao esta a funcionar!!!!

//Funcoes auxiliares
static void	ordenaProdQtd(char** cod, int* quant);
static int comp(const void* p1, const void* p2);
static int compStr(const void* p1, const void* p2);


void
	runQueries(SGV gestao)
	{
		gboolean flag = TRUE;
		char files[100] = "";

		gestao = Query1(gestao, files);	//le os ficheiros predefinidos

		do
		{
			switch(menu())
			{
				case 1:	system("clear");
						printf("Query 1 - Fazer leitura de outros ficheiros de dados\n\n");
						printf("Insira o nome dos 3 ficheiros separados unicamente por um espaço\n(ex.: fileProdutos.txt fileClientes.txt fileVendas.txt)\n\n");
						fgets(files, 100, stdin);
						gestao = Query1(gestao, files);
						break;
				case 2: Query2(gestao);
						break;
				case 3: Query3(gestao);
						break;
				case 4: Query4(gestao);
						break;
				case 5: Query5(gestao);
						break;
				case 6: Query6(gestao);
						break;
				case 7: Query7(gestao);
						break;
				case 8: Query8(gestao);
						break;
				case 9: Query9(gestao);
						break;
				case 10: Query10(gestao);
						 break;
				case 11: break;
				case 12: Query12(gestao);
						 break;
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
			printf("Query 4 - Consultar produtos nao comprados\n");
			printf("Query 5 - Consultar clientes que fizeram compras em todas as filiais\n");
			printf("Query 6 - Consultar clientes sem compras e produtos nunca comprados\n");
			printf("Query 7 - Tabela de numero total de produtos comprados por determinado cliente\n");
			printf("Query 8 - Consultar numero de vendas e totais faturados num intervalo de meses\n");
			printf("Query 9 - Consultar clientes que compraram determinado produto, em determinada filial\n");
			printf("Query 10 - Lista de produtos mais comprados por determinado cliente\n");
			printf("Query 11 - \n");
			printf("Query 12 - \n");
			printf("0 - Sair\n");
			printf("Insira a Query pretendida: ");
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

		if(!strcmp(files, "\n"))
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
		int dim;
		printf("Query 2 - Consulta produtos do catalogo\n\n");

		printf("Insira a inicial dos produto que pretende listar\n");
		scanf("%c", &letra);
		getchar();

		l = listaPorLetraProdutos(gestao->cp, letra);
		dim = getDimensaoLista(l);
		printf("Ha %d produtos começados pela letra %c\n", dim, letra);
		printf("(Prima ENTER para continuar...)"); getchar();

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

		printf("Query 3 - Consulta vendas de produtos\n\n");
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

static void
	Query4(SGV gestao)
	{
		system("clear");
		int check, i = 0, j = 0, k = 0, pag = 0;
		char*** array; //[Filial][indice][string]
		char** codNunca;
		int total[NUMFILIAIS];
			
		printf("Query 4 - Consultar produtos nao comprados\n\n");
		printf("Apresentar resultados:\n");
		printf("\t 1 - Todos as filiais\n");
		printf("\t 2 - Filial a Filial\n");
		scanf("%d", &check);
		getchar();

				
		if (check-1 == 0) //Total
		{
			codNunca = codigosNenhumaFilial(gestao->cp);
			while(codNunca[j])
					j++;

			qsort(codNunca, j, sizeof(char*), compStr);	
		
		
			system("clear");
			k = 0;
			printf("\nHouveram %d produtos nao comprados em nenhuma filial\n", j);
			printf("(Prima ENTER para continuar...)"); getchar();
			
			while(codNunca[i])
			{
				system("clear");
				k = 0;
				
				//print 25 por paginas, e no fim, se nao tiver 25, print as que tem e sai
				while(k < PAGINACAO && codNunca[i])
				{
					printf("%s\n", codNunca[i]);	
					i++;
					k++;
				}
				pag++;
				printf("Pagina %d de %d\n", pag, (j / PAGINACAO)+1); getchar();
				
			}
		}
		else //Filial
		{
			array = listaProdutosNaoComprados(gestao->cp);

			//ciclo for a executar um vez por filial
			for (i = 0; i < NUMFILIAIS; ++i)
			{
				j=0;

				//Calcular a dimensao do array
				while(array[i][j])
					j++;				

				//guardar a dimensao do array
				total[i] = j;

				//ordenacao do array
				qsort(array[i], j, sizeof(char*), compStr);
			}

			for (i = 0; i < NUMFILIAIS; ++i)
			{
				printf("\nNa filial %d houveram %d produtos nao comprados\n", i+1, total[i]);
				printf("(Prima ENTER para continuar...)"); getchar();

				j = 0;
				pag = 0;
				//enquanto na filial i, existirem strings em j, repete
				while(array[i][j])
				{
					system("clear");
					k = 0;

					//print 25 por paginas, e no fim, se nao tiver 25, print as que tem e sai
					while(k < PAGINACAO && array[i][j])
					{
						printf("%s\n", array[i][j]);	
						j++;
						k++;
					}
					pag++;
					printf("Filial %d - Pagina %d de %d\n", i+1, pag, (total[i] / PAGINACAO)+1); getchar();
					
				}
			}
		}
	}

static void
	Query5(SGV gestao)
	{
		system("clear");
		int i = 0, j = 0, k = 0, pag = 0;
		char** codSempre;
			
		printf("Query 5 - Consultar clientes que fizeram compras em todas as filiais\n\n");
				
		codSempre = codigosSempreCompras(gestao->ccli);
		while(codSempre[j])
				j++;

		qsort(codSempre, j, sizeof(char*), compStr);	
	
	
		system("clear");
		k = 0;
		printf("\nHouveram %d que fizeram compras em todas as filiais\n", j);
		printf("(Prima ENTER para continuar...)"); getchar();
		
		while(codSempre[i])
		{
			system("clear");
			k = 0;
			
			//print 25 por paginas, e no fim, se nao tiver 25, print as que tem e sai
			while(k < PAGINACAO && codSempre[i])
			{
				printf("%s\n", codSempre[i]);	
				i++;
				k++;
			}
			pag++;
			printf("Pagina %d de %d\n", pag, (j / PAGINACAO)+1); getchar();
				
		}
	}

static void
	Query6(SGV gestao)
	{
		system("clear");
		int totalClientes, produtosNada = 0, clientesTudo = 0;
		char** codSempre, **codNunca;

		totalClientes = getClientesLidos(gestao->ccli);

		codSempre = codigosSempreCompras(gestao->ccli);
		while(codSempre[clientesTudo])
				clientesTudo++;


		codNunca = codigosNenhumaFilial(gestao->cp);
			while(codNunca[produtosNada])
					produtosNada++;

		printf("Query 6 - Consultar clientes sem compras e produtos nunca comprados\n\n");
		printf("Houveram %d clientes que não fizeram compras\n", totalClientes-clientesTudo);
		printf("Houveram %d produtos que não foram comprados\n", produtosNada);
		printf("(Prima ENTER para continuar...)"); getchar();
	}

static void
	Query7(SGV gestao)
	{
		int somaMesFil[12][NUMFILIAIS], total = 0;
		char codCli[10];
		printf("Insira o código do cliente: \n");
		scanf("%s", codCli);
		getchar();

		if(clienteExisteNoCatalogo(gestao->ccli, codCli))
		{
			
			for(int j = 0; j < 12; j++)
			{
				for(int i = 0; i < NUMFILIAIS; i++)
				{
					somaMesFil[i][j] = quantidadeClienteMes(gestao->filiais[i], j, codCli);
					total += somaMesFil[i][j];
				}
			}

			//Cria a tabela
			printf("%s\t|%s|%s|%s\n", "MES", "    FILIAL 1   ", "    FILIAL 2   ", "     FILIAL 3   ");
			for(int j = 0; j < 12; j++)
				printf("%d\t|\t%d\t|\t%d\t|\t%d\n", j+1, somaMesFil[0][j], somaMesFil[1][j], somaMesFil[2][j]);
			printf("\nO Cliente %s comprou %d produtos no total\n", codCli, total);
		}
		else
		{
			printf("O código inserido não existe no catálogo!\n");
		}
		printf("(Prima ENTER para continuar...)"); getchar();
	}


static void 
	Query8(SGV gestao)
	{	
		system("clear");
		int min = 0, max = 0;
		char* mes1, *mes2;
		char meses[6];
		int somaQtd = 0;
		double somaPreco = 0;
		double** totais;

		printf("Query 8 - Consultar numero de vendas e totais faturados num intervalo de meses\n\n");
		printf("Indique o intervalo de tempo(meses) em que deseja ver a facturacao(separado por 1 espaco): \n");
		fgets(meses,6,stdin);

		mes1 = strtok(meses," ");
		mes2 = strtok(NULL," ");

		min = atoi(mes1);
		max = atoi(mes2);

		if(min>max)
		{
			max += min;
			min = max - min;
			max -= min;
		}

		for (int i = min; i <= max; ++i)
		{
			totais = getTotalFacturado(gestao->fact, i, NULL);
			somaQtd += (int)totais[0][0];
			somaPreco += totais[1][0];

			printf("No mês %d, venderam-se %d produtos, e faturou-se %.2fEUR\n", i, (int)totais[0][0], totais[1][0]);
		}
		printf("Entre o mês %d e %d, venderam-se %d produtos, e faturou-se %.2fEUR\n", min, max, somaQtd, somaPreco);
		printf("(Prima ENTER para continuar...)"); getchar();
	}

static void 
	Query9(SGV gestao)
	{
		system("clear");
		char cod[7];
		int fil;
		char** codigosN;
		char** codigosP;
		int i = 0, j = 0;

		printf("Query 9 - Consultar clientes que compraram determinado produto, em determinada filial\n\n");
		printf("Insira o codigo do produto\n");
		scanf("%s", cod);
		getchar();
		printf("Insira o numero da filial onde pretende efetuar a busca\n");
		scanf("%d", &fil);
		getchar();

		codigosN = cClienteQueCompraramOProduto(gestao->filiais[fil-1], gestao->ccli, cod, FALSE);
		codigosP = cClienteQueCompraramOProduto(gestao->filiais[fil-1], gestao->ccli, cod, TRUE);

		system("clear");
		printf("Os codigos de clientes que compraram o produto %s na filial %d sao:\n", cod, fil);
		printf("MODO NORMAL:\n");
		while(codigosN[i])
		{
			printf("%s\n", codigosN[i]);
			i++;
		}
		if(i != 1)
			printf("%d clientes compraram o produto\n", i);
		else
			printf("%d cliente comprou o produto\n", i);


		printf("\nMODO PROMOCIONAL:\n");
		while(codigosP[j])
		{
			printf("%s\n", codigosP[j]);
			j++;
		}
		if(j != 1)
			printf("%d clientes compraram o produto\n", j);
		else
			printf("%d cliente comprou o produto\n", j);

		printf("O produto foi comprado por %d clientes\n", i+j);	
		printf("(Prima ENTER para continuar...)"); getchar();
	}

static void //Nesta query, falta ver quando os codigos das filias sao repetidos e somar as suas quantidades
	Query10(SGV gestao)
	{
		system("clear");
		char** arrayProdutos, **codigosProdutos = malloc(sizeof(char*));
		int* arrayQuantidade;
		int* quantidades = malloc(sizeof(int));
		int i = 0, j = 0, k = 0;
		char cliente[6];
		codigosProdutos[0] = NULL;
		quantidades[0] = 0;

		printf("Query 10 - Lista de produtos mais comprados por determinado cliente\n\n");
		printf("Insira o codigo de cliente\n");
		scanf("%s", cliente);
		getchar();

		for(i = 0; i < NUMFILIAIS; i++)
		{
			arrayProdutos = getProdutos(gestao->filiais[i], cliente);
			arrayQuantidade = getQuantidades(gestao->filiais[i], cliente);
			
			j = 0;
			while(arrayProdutos[j])
			{
				codigosProdutos[k] = g_strdup(arrayProdutos[j]);
				codigosProdutos = realloc(codigosProdutos, sizeof(char*) * (k+2));
				codigosProdutos[k+1] = NULL;
				quantidades[k] = arrayQuantidade[j];
				quantidades = realloc(quantidades, sizeof(int) * (k+2));
				quantidades[k+1] = 0;
				k++;
				j++;
			}
		}

		ordenaProdQtd(codigosProdutos, quantidades);
		i = 0;
		while(codigosProdutos[i])
		{
			printf("%s - %d\n", codigosProdutos[i], quantidades[i]);
			i++;
		}
		getchar();
	}

static void 
	Query12(SGV gestao)
	{
		char** arrayProdutos;
		int i = 0, j = 0;
		char cliente[6];

		printf("insira o codigo de cliente\n");
		scanf("%s", cliente);
		getchar();

		for(i = 0; i < NUMFILIAIS; i++)
		{
			arrayProdutos = getProdutos(gestao->filiais[i], cliente);
			j=0;
			while(arrayProdutos[j])
			{
				printf("%s\n", arrayProdutos[j]);
				j++;
			}
		}
		getchar();
	}

static void
	ordenaProdQtd(char** cod, int* quant)
	{
		int* permanece;
		char** codCopy;
		int i = 0, j = 0, tam = 0;

		while(quant[tam])
			tam++;

		permanece = malloc(sizeof(int) * tam);
		codCopy = malloc(sizeof(char*) * tam);
		for (int i = 0; i < tam; ++i)
		{
			permanece[i] = quant[i];
			codCopy[i] = g_strdup(cod[i]);
		}
		qsort(quant, tam, sizeof(int), comp);

		while(quant[i])
		{
			j = 0;
			while(quant[i] != permanece[j])
				j++;
			cod[i] = g_strdup(codCopy[j]);
			i++;
		}
	}

static int 
	comp(const void* p1, const void* p2)
	{
		return ( *(int*)p2 - *(int*)p1 );
	}

static int 
	compStr(const void* p1, const void* p2)
	{
		int size = strcmp(* (char * const *) p1, * (char * const *) p2);

		return size;
	}