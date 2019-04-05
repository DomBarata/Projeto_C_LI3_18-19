#include "VendaUnica.h"

#ifndef FACTURACAO_H
#define FACTURACAO_H

typedef struct fact* Facturacao;

Facturacao inicializa_Facturacao();
Facturacao insereNovaFacturacao(VendaUnica v, Facturacao f);

#endif