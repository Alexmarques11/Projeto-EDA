/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções Aluguer
 * 
 * \author Utilizador Alexandre Marques
 * \date   April 2023
 *********************************************************************/

#include "Aluguer.h"	

/**
 * .Esta função cria um aluguer e envia para a lista encadeada
 * 
 * \param m
 * \param c
 * \param d
 * \param lista
 * \return 
 */



/*Aluguer* ConstruirAluguer(Aluguer* lista, Clientes c, Meios m, DadosAluguer d) {
	Aluguer a;
	a.cliente = c;
	a.meio = m;
	a.dados = d;
	adicionarAluguerLista(lista, a);

	return lista;
}*/

/**
 * .Esta função adiciona um aluguer à lista encadeada
 * 
 * \param lista
 * \param novoAluguer
 * \return 
 */

/*AluguerLista* adicionarAluguerLista(AluguerLista* lista, Aluguer novoAluguer) {
	AluguerLista* novoNo = (AluguerLista*)malloc(sizeof(AluguerLista));
	novoNo->a = novoAluguer;
	novoNo->next = NULL;

	if (lista == NULL) {
		return novoNo;
	}
	else if (lista->a.dados.id < novoAluguer.dados.id) {
		novoNo->next = lista;
		return novoNo;
	}
	else {
		AluguerLista* atual = lista;
		while (atual->next != NULL && atual->next->a.dados.id > novoAluguer.dados.id) {
			atual = atual->next;
		}
		novoNo->next = atual->next;
		atual->next = novoNo;
		return lista;
	}
}
*/

/**
 * .Esta função lê os dados do aluguer do ficheiro binário
 * 
 * \param lista
 * \return 
 */

bool guardarAluguerbin(AluguerLista* lista) {
	FILE* ficheiro = fopen("Alugueres.bin", "wb");
	if (ficheiro == NULL) {
		return false;
	}
	while (lista != NULL) {
		fwrite(&lista->a, sizeof(Aluguer), 1, ficheiro);
		lista = lista->next;
	}
	fclose(ficheiro);
	return true;
}

/**
 * Esta função lê os dados do aluguer do ficheiro binário
 * 
 * \param lista
 * \return 
 */

/*bool adicionarNovoAluguer(AluguerLista** listaAlugueres, MeiosLista* listaMeios, ClientesLista* listaClientes) {
	// Cria um novo aluguer com os dados inseridos pelo usuário
	Aluguer novoAluguer;
	obterDadosAluguerEcra(&novoAluguer, listaMeios, listaClientes);
	// Adiciona o novo aluguer à lista
	*listaAlugueres = adicionarAluguerLista(*listaAlugueres, novoAluguer);


		return true;
}	
*/




