/*****************************************************************//**
 * \file   Main.c
 * \brief  Main
 *
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Clientes.h"
#include "Gestores.h"
#include "MeiosMobilidade.h"


int main() {

#pragma region Clientes
	//ClientesLista* listaClientes = NULL;
	//lerClientestxt(&listaClientes);
	//lerClientesbin(&listaClientes);
	//adicionarNovoCliente(&listaClientes);
	//clienteRemovidoEcra(listaClientes);
	//system("cls");
	//mostrarClientes(listaClientes);

#pragma endregion

#pragma region Gestores
	//GestoresLista* listaGestores = NULL;
	//lerGestorestxt(&listaGestores);
	//lerGestoresbin(&listaGestores);
	//adicionarNovoGestor(&listaGestores);
	//GestorRemovidoEcra(listaGestores);
	//system("cls");
	//mostrarGestores(listaGestores);

#pragma endregion

#pragma region Meios
	MeiosLista* listaMeios = NULL;
	//lerMeiostxt(&listaMeios);
	lerMeiosbin(&listaMeios);
	//adicionarNovoMeio(&listaMeios);
	//MeioRemovidoEcra(listaMeios);
	system("cls");
	mostrarMeios(listaMeios);

#pragma endregion
}

