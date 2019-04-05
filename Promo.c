#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Promo.h"
#include "Fact_Info.h"

struct promocao
{
	Fact_Info ePromo[2];//0 - Venda N | 1 - Venda P
};

Promo 
	inicializa_Promo()
	{
		Promo p = malloc(sizeof(struct promocao));
		p->ePromo[0] = inicializa_Fact_Info();
		p->ePromo[1] = inicializa_Fact_Info();

		return p;
	}

Promo
	insereNaPromo(VendaUnica v, Promo p)
	{
		if(strcmp(getTipoVendas(v), "N") == 0)//alterar para char caso não funcione
			p->ePromo[0] = insereInfo(v, p->ePromo[0]);
		else
			p->ePromo[1] = insereInfo(v, p->ePromo[1]);

		return p;
	}