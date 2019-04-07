#include "VendaUnica.h"

#ifndef FILIAL_H
#define FILIAL_H

typedef struct filMes* Filial;

Filial inicializaFilial();
Filial insereFilial(VendaUnica v, Filial fil);
int prodsClienteMes(Filial fil, int mes, char* codCli);

#endif