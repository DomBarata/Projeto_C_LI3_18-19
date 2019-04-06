#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cliente.h"

struct cli
{
	char* cliente;
	gboolean filialCompra[3];
};

Cliente
	criaCliente(char* codCli)
	{
		Cliente c = malloc(sizeof(struct cli));
		c->cliente = g_strdup(codCli);
		for (int i = 0; i < 3; ++i)
		{
			c->filialCompra[i] = 0;
		}

		return c;
	}

char*
	getCodCli(Cliente c) {return c->cliente;}

gboolean
	verificaCliente(Cliente codigo)
	{
		int check = 1;
		int num;

		codigo->cliente += 1;
		num = atoi (codigo->cliente);
		codigo->cliente -= 1;

		if(!((codigo->cliente[0] >='A' && codigo->cliente[0] <= 'Z')
			&& (strlen(codigo->cliente) == 5) && (num >= 1000 && num <= 5000)))
			check = 0;

		return check;
	}

Cliente
	setFilialCompra(Cliente c, int fil) {c->filialCompra[fil-1] = TRUE;}

void //Esta funcao envia para o utilizador o cliente
	printCliente(Cliente c)	{printf("%s\n", c->cliente);}
