#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Produto.h"

struct prod
{
	char* produto;
};

Produto //Inicializa a struct prod alocando memoria
	criaProduto(char* codProd)
	{
		Produto p = malloc(sizeof(struct prod));
		p->produto = g_strdup(codProd);

		return p;
	}

char* //retorna o valor de pordudo
	getCodProd(Produto p) {return p->produto;}

gboolean //Verifica se o codigo de produto esta semanticamente correto
	verificaProduto(Produto codigo)
	{
		int check = 1;

		if(!((strlen(codigo->produto) == 6) && 
			(codigo->produto[0] >= 'A' && codigo->produto[0]<= 'Z') && 
			(codigo->produto[1] >= 'A' && codigo->produto[1]<='Z') && 
			(codigo->produto[2] >= '1' && codigo->produto[2]<= '9') && 
			(codigo->produto[3] >= '0' && codigo->produto[3]<= '9') &&
			(codigo->produto[4] >= '0' && codigo->produto[4]<= '9') &&
			(codigo->produto[5] >= '0' && codigo->produto[5]<= '9')))
				check = 0;
		return check;
	}

void //Esta funcao envia para o utilizador o produto
	printProduto(Produto p)	{printf("%s\n", p->produto);}
