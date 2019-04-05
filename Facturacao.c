#include <glib.h>
#include <stdlib.h>
#include "Facturacao.h"
#include "Promo.h"
#include "Fact_Info.h"

struct fact
{
	Promo mes[12];
};

Facturacao
	inicializa_Facturacao()
	{
		Facturacao f = malloc(sizeof(struct fact));

		for (int i = 0; i < 12; ++i)
		{
			f->mes[1] = inicializa_Promo();
		}
		return f;
	}

Facturacao
	insereNovaFacturacao(VendaUnica v, Facturacao f)
	{
		f->mes[getMesVendas(v)-1] = insereNaPromo(v, f->mes[getMesVendas(v)-1]);

		return f;
	}