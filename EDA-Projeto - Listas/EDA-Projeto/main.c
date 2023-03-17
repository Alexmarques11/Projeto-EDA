/*****************************************************************//**
 * \file   Main.c
 * \brief  Main
 *
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Clientes.h"


int main() {
	ClientesLista* listaClientes = NULL;
	lerClientesbin(&listaClientes);
	//adicionarNovoCliente(&listaClientes);
	clienteRemovidoEcra(listaClientes);
	system("cls");
	mostrarClientes(listaClientes);
}
