#include <glib.h>
#include "VendaUnica.h"

#ifndef FACTURACAO_H
#define FACTURACAO_H

//Estrutura de dados onde e guardado tudo de relevante para a faturacao
typedef struct fact* Facturacao;

Facturacao inicializa_Facturacao();

//insere uma linha de venda na faturacao
Facturacao insereNovaFacturacao(VendaUnica v, Facturacao f);

//dado um codigo e um mes, retorna um array com o numero de vendas
//[0] - tipo Normal
//[1] - tipo Promocao
int** getNumeroVendas(Facturacao f, int m, char* cod);

//dado um codigo e um mes, retorna um array com o total faturado nesse mes por esse codigo
//se cod for NULL, retorna o total faturado nesse mes, de todos os codigos juntos
//[0] - tipo Normal
//[1] - tipo Promocao
double** getTotalFacturado(Facturacao f, int m, char* cod);
#endif