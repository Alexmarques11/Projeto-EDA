/*****************************************************************//**
 * \file   Main.c
 * \brief  Main
 *
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Clientes.h"


int main() {

#pragma region Clientes
	ClientesLista* listaClientes = NULL;
	//lerClientestxt(&listaClientes);
	lerClientesbin(&listaClientes);
	//adicionarNovoCliente(&listaClientes);
	//clienteRemovidoEcra(listaClientes);
	system("cls");
	mostrarClientes(listaClientes);

#pragma endregion



}