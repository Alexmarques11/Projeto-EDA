/*****************************************************************//**
 * \file   Aluguer.h
 * \brief  Ficheiro header dos alugueres
 * 
 * \author Utilizador Alexandre Marques
 * \date   April 2023
 *********************************************************************/

#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Clientes.h"
#include "MeiosMobilidade.h"
#include "Grafos.h"
#define _CTR_SECURE_NO_WARNINGS

#define A 11
#define N 10


#ifndef Aluguerh
#define Aluguerh

typedef struct Aluguer {
	int id;
	char nif[N];
	int idMeio;
	char data[A];
	int idDestino;
	int km;
	float preco;
}Aluguer;

typedef struct AluguerLista {
	Aluguer a;
	struct AluguerLista* next;
}AluguerLista;

/**
 * Esta fun��o l� os alugueres de um ficheiro txt e insere-os numa lista encadeada
 * 1� L� os dados de cada aluguer e envia para a fun��o adicionarAluguerLista que insere na lista encadeada
 * 2� Retorna 1 se o ficheiro foi lido com sucesso e 0 se n�o foi lido com sucesso
 *
 * \param listaAlugueres
 * \param filename
 * \return
 */

int lerAluguerestxt(AluguerLista** listaAlugueres, char* filename, Vertice* g, MeiosLista* mlista);

/**
 * Esta fun��o adiciona um aluguer � lista encadeada
 * 1� Aloca mem�ria para o novo aluguer
 * 2� Verifica se a lista est� vazia ou se o novo aluguer tem o menor ID
 * 3� Encontra a posi��o correta para inserir o novo aluguer na lista ordenada
 * 4� Retorna a lista com o novo aluguer
 *
 * \param lista
 * \param a
 * \return
 */

AluguerLista* adicionarAluguerLista(AluguerLista* lista, Aluguer a);

/**
 * Esta fun��o verifica se um aluguer existe na lista encadeada
 * 1� Percorre a lista encadeada e verifica se o ID do aluguer � igual ao ID do aluguer da lista
 * 2� Retorna true se o aluguer existe na lista e false se n�o existe
 *
 * \param lista
 * \param a
 * \return
 */
bool existeAluguer(AluguerLista* lista, Aluguer a);

int CalcularKm(Vertice* g, MeiosLista* mlista, int idMeio, Aluguer a);

#pragma region Ecra

void imprimirAluguerLista(AluguerLista* lista);

#pragma endregion


#endif // !Aluguerh

