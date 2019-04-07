#include "VendaUnica.h"

#ifndef FACTURACAO_H
#define FACTURACAO_H

typedef struct fact* Facturacao;

Facturacao inicializa_Facturacao();
Facturacao insereNovaFacturacao(VendaUnica v, Facturacao f);
char** getKeysFact(Facturacao fact);
int getTamanhoListaFactMes(Facturacao f, int m);
double totalFaturadoMes(Facturacao f, int m);

#endif