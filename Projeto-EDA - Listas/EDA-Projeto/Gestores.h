/*****************************************************************//**
 * \file   Gestores.h
 * \brief  Ficheiro header dos gestores
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS

#ifndef Gestorsh
#define Gestorsh

typedef struct Gestores {
	int id;
	char nome[20];
	char email[50];
	char password[15];
}Gestores;

typedef struct GestoresLista {
	Gestores g;
	struct GestoresLista* next;
}GestoresLista;

/**
 * \brief  Função para ler os dados dos gestores do ficheiro txt
 * 1º  Lê os dados de cada gestor e envia para a função adicionarGestorLista que insere na lista encadeada
 *2º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestoresbin
 * \param listaGestores
 * @author Alexandre Marques
 */

int lerGestorestxt(GestoresLista** listaGestores);

/**
* \brief  Insere Gestores no incio de uma lista encadeada
*1º Cria um novo nó com os dados do gestor
* 2º Insere o novo nó no inicio da lista
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestoresbin
* \param recebe uma lista e um gestor para o inserir na lista
* \return retorna a lista atualizada
* \author Alexandre Marques
*/

GestoresLista* adicionarGestorLista(GestoresLista* lista, Gestores c);

/**
 * \brief  Esta função guarda a lista de gestores no ficheiro binário
 *1º Abre o ficheiro binário para escrita
 *2º Percorre a lista encadeada e guarda os dados de cada gestor no ficheiro
 *3º Fecha o ficheiro
 * \param lista
 * \author Alexandre Marques
 */

bool guardarGestoresbin(GestoresLista* lista);

/**
*\brief  Esta função lê os dados dos gestores do ficheiro binário
*1º Abre o ficheiro binário para leitura
*2º Percorre o ficheiro e guarda os dados de cada gestor na lista encadeada
*3º Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

GestoresLista* lerGestoresbin(GestoresLista** listaGestores);

/**
* \brief  Esta função remove um cliente da lista de gestores
* 1º Procura pelo gestor com o id correspondente na lista encadeada
* 2º Remove o cliente da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarGestoresbin
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool RemoverGestor(GestoresLista** listaGestor, int id);

/**
* \brief  Esta função adiciona um novo gestor à lista de gestores
* 1º Cria um novo gestor com os dados inseridos pelo usuário
* 2º Adiciona o novo gestor à lista chamando a função adicionarGestorLista
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestorbin
 *
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool adicionarNovoGestor(GestoresLista** listaGestor);


/*
* \brief  Esta função remove um cliente da lista de clientes
* 1º Procura pelo cliente com o NIF correspondente na lista encadeada
* 2º Remove o cliente da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */


bool RemoverGestor(GestoresLista** listaGestor, int id);

/**
 * Esta função destroi a lista de gestores
 * 1º Percorre a lista encadeada e destroi cada nó
 * 2º Liberta a memória alocada para a lista
 *
 * \param lista
 */


void DestruirListaG(GestoresLista* lista);



Gestores* obterDadosGestorEcra(Gestores* c);


#endif // !Gestorsh





