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
#include "Grafos.h"	
#include "Aluguer.h"


int main() {

#pragma region Clientes
	bool aux;
	int x;
	//ClientesLista* listaClientes = NULL;
	//x=lerClientestxt(&listaClientes);
	//x=lerClientesbin(&listaClientes);
	//adicionarNovoCliente(&listaClientes);
	//clienteRemovidoEcra(listaClientes);
	//system("cls");
	//aux=guardarClientesbin(listaClientes);
	//mostrarClientes(listaClientes);

	//DestruirListaC(listaClientes);
#pragma endregion

#pragma region Gestores
	//GestoresLista* listaGestores = NULL;
	//x=lerGestorestxt(&listaGestores);
	//x=lerGestoresbin(&listaGestores);
	//adicionarNovoGestor(&listaGestores);
	//GestorRemovidoEcra(listaGestores);
	//system("cls");
	//mostrarGestores(listaGestores);
	//aux = guardarGestoresbin(listaGestores);
#pragma endregion

#pragma region Meios
	//MeiosLista* listaMeios = NULL;
	//lerMeiostxt(&listaMeios);
	//lerMeiosbin(&listaMeios);
	//adicionarNovoMeio(&listaMeios);
	//MeioRemovidoEcra(&listaMeios);
	//system("cls");
	//mostrarMeios(listaMeios);

	//

#pragma region Grafos
	
	static int total = 0;					//total de vertices
	bool res;

	Vertice* grafo = CriaGrafo();
	
	
	/*
	
	Vertice* novoVertice = CriaVertice("Braga", total);
	if (novoVertice != NULL) {
		grafo = InsereVertice(grafo, novoVertice, &res);
		total++;
	}

	novoVertice = CriaVertice("Amares", total);
	if (novoVertice != NULL) {
		grafo = InsereVertice(grafo, novoVertice, &res);
		total++;
	}

	novoVertice = CriaVertice("VilaVerde", total);
	if (novoVertice != NULL) {
		grafo = InsereVertice(grafo, novoVertice, &res);
		total++;
	}

	AdicionaAdjacente(grafo, 0, 1, 10);
	AdicionaAdjacente(grafo, 0, 2, 20);
	AdicionaAdjacente(grafo, 1, 2, 15);
	
	*/

	//MostraGrafo(grafo);
	
	//GuardarGrafoBin(grafo, "Vertices.bin");

	//system("cls");

	//grafo = DestruirGrafo(grafo);

	//MostraGrafo(grafo);

	grafo = LerGrafoBin(grafo, "Vertices.bin", &res);

	grafo = LerAdjBin(grafo, &res);

	MostraGrafo(grafo);

	
#pragma endregion

}
