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
	//aux = ModificarCliente(listaClientes,"112233445", 2);
	//mostrarClientes(listaClientes);

#pragma endregion

#pragma region Gestores
	GestoresLista* listaGestores = NULL;
	//x=lerGestorestxt(&listaGestores);
	x=lerGestoresbin(&listaGestores);
	//adicionarNovoGestor(&listaGestores);
	//gestorRemovidoEcra(listaGestores);
	//mostrarGestores(listaGestores);
	//aux = guardarGestoresbin(listaGestores);

#pragma endregion

#pragma region Meios

	MeiosLista* listaMeios = NULL;
	//lerMeiostxt(&listaMeios);
	lerMeiosbin(&listaMeios);
	//adicionarNovoMeio(&listaMeios);
	//MeioRemovidoEcra(&listaMeios);

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
	}
	*/
	//DestruirListaM(listaMeios);

#pragma endregion

#pragma region Grafos


	static int total = 0; 
	bool res;
	int y = 0;

	Vertice* grafo = CriaGrafo();

	grafo = LerGrafoBin(grafo, "Vertices.bin", &res);
	grafo = LerAdjBin(grafo, &res);

	//GuardarGrafoBin(grafo, "Vertices.bin");

	MostraGrafo(grafo);

#pragma endregion

#pragma region Alugueres

	AluguerLista* listaAlugueres = NULL;


	//x = lerAluguerestxt(&listaAlugueres, "Alugueres.txt", grafo, listaMeios);

	x=carregarAlugueresBinario(&listaAlugueres, "Alugueres.bin", grafo, listaMeios);

	//imprimirAluguerLista(listaAlugueres);

#pragma endregion

#pragma region Gravações e destruições

	x=guardarAlugueresBinario(listaAlugueres, "Alugueres.bin");
	aux = guardarMeiosMobilidadebin(listaMeios);
	aux = guardarClientesbin(listaClientes);
	aux = guardarGestoresbin(listaGestores);


	DestruirListaG(listaGestores);
	DestruirListaC(listaClientes);
	destruirAluguerLista(listaAlugueres);
	DestruirListaM(listaMeios);
	grafo = DestruirGrafo(grafo);

#pragma endregion

}