#include "VendaUnica.h"

#ifndef FILIAL_H
#define FILIAL_H

typedef struct movimentos* Filial;
typedef struct valueProd* QuantidadeProd;

Filial inicializaFilial();
Filial insereFilial(VendaUnica v, Filial fil);

#endif