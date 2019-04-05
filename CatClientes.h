#include <glib.h>
#include "Cliente.h"
#include "List_Clientes.h"

#ifndef CATCLINTES_H
#define CATCLIENES_H

typedef struct catClis* CatClientes; //Estrutura que define um array
									 //de 26 List_Clientes

//Funcao que aloca memoria para a estrutura de dados
CatClientes inicializa_CatClientes();

//Funcao que dado um catalogo e um cliente, o insere nesse mesmo catalogo
CatClientes insereClientes(CatClientes catCli, Cliente cli);

//Funcao que dado um catalogo e uma letra, retorna uma lista de
//clientes comecados por essa mesma letra
List_Clientes listaPorLetraClientes(CatClientes catc, char letra);

//funcao que verifica que o cliente esta inserido no catalogo
gboolean clienteExisteNoCatalogo(CatClientes catc, char* cod);

#endif