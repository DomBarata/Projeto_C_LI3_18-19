#include <glib.h>
#include "VendaUnica.h"

#ifndef FACTURACAO_H
#define FACTURACAO_H

typedef struct fact* Facturacao;

Facturacao inicializa_Facturacao();
Facturacao insereNovaFacturacao(VendaUnica v, Facturacao f);
int** getNumeroVendas(Facturacao f, int m, char* cod);
double** getTotalFacturado(Facturacao f, int m, char* cod);
#endif