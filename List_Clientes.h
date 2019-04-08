#include <glib.h>

#ifndef LIST_CLIENTES_H
#define LIST_CLIENTES_H

typedef struct listaClientes* List_Clientes; //Estrutura de dados que contem
											 //um array de Clientes

//Funcao que aloca memoria para uma List_Clientes
List_Clientes inicializa_List_Clientes();

//Funcao que dada uma lista e um cliente, o insere nessa mesma lista
List_Clientes insereUmCliente(List_Clientes l, Cliente c);

//Funcao que insere uma filial a informacao do cliente
List_Clientes setList_Clientes(List_Clientes l, char* cli, int fil);

//Print no ecra de uma lista ORDENADA de clientes
void consultarClientes(List_Clientes l);

//funcao que dada uma lista de clientes, a transforma num array
char** listaToArray(List_Clientes l);

//Funcao que dada uma lista, verifica se o codigo do cliente esta inserido
gboolean clienteExisteNaLista(List_Clientes l, char* codCli);

//dado uma lista de clientes, verifica aqueles que foram comprados em todas as filiais 
char** produtosCompradosPorTodos(char** codSempre, List_Clientes l);

#endif