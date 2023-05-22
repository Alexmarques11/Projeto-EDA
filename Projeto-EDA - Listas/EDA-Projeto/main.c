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
	ClientesLista* listaClientes = NULL;
	//x=lerClientestxt(&listaClientes);
	lerClientesbin(&listaClientes, "Clientes.bin");
	//adicionarNovoCliente(&listaClientes);
	//clienteRemovidoEcra(listaClientes);
	//system("cls");
	mostrarClientes(listaClientes);
	//aux = ModificarCliente(listaClientes,"112233445", 2);
	aux=guardarClientesbin(listaClientes);
	//mostrarClientes(listaClientes);

	DestruirListaC(listaClientes);
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

	//DestruirListaG(listaGestores);
#pragma endregion

#pragma region Meios

	//MeiosLista* listaMeios = NULL;
	//lerMeiostxt(&listaMeios);
	//lerMeiosbin(&listaMeios);
	//adicionarNovoMeio(&listaMeios);
	//MeioRemovidoEcra(&listaMeios);
	//system("cls");
	//mostrarMeios(listaMeios);

	//aux= ModificarMeioMobilidade(listaMeios, 1, 2);

	//aux = guardarMeiosMobilidadebin(listaMeios);


	/*Meios* meioEncontrado = procurarMeioPorId(listaMeios, 1);

	if (meioEncontrado != NULL) {
		printf("ID: %d\n", meioEncontrado->id);
		printf("Localizacao: %s\n", meioEncontrado->localizacao);
		printf("Bateria: %d\n", meioEncontrado->bateria);
		printf("Custo: %.2f\n", meioEncontrado->custo);
		printf("Autonomia: %d\n", meioEncontrado->autonomia);
		printf("Status: %d\n", meioEncontrado->status);
		printf("\n");
		// Imprima os outros campos do meio de mobilidade conforme necessário
	}
	*/
	//DestruirListaM(listaMeios);

#pragma region Grafos

	
	//static int total = 0;					//total de vertices
	//bool res;

	//Vertice* grafo = CriaGrafo();
	
	
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

	//grafo = LerGrafoBin(grafo, "Vertices.bin", &res);

	//MostraGrafo(grafo);

	//grafo = LerAdjBin(grafo, &res);

	//MostraGrafo(grafo);

	//grafo = DestruirGrafo(grafo);
	
#pragma endregion

}
