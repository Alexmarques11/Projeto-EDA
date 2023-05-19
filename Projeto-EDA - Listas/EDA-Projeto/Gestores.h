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
 * \brief  Fun��o para ler os dados dos gestores do ficheiro txt
 * 1�  L� os dados de cada gestor e envia para a fun��o adicionarGestorLista que insere na lista encadeada
 *2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestoresbin
 * \param listaGestores
 * @author Alexandre Marques
 */

int lerGestorestxt(GestoresLista** listaGestores);

/**
* \brief  Insere Gestores no incio de uma lista encadeada
*1� Cria um novo n� com os dados do gestor
* 2� Insere o novo n� no inicio da lista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestoresbin
* \param recebe uma lista e um gestor para o inserir na lista
* \return retorna a lista atualizada
* \author Alexandre Marques
*/

GestoresLista* adicionarGestorLista(GestoresLista* lista, Gestores c);

/**
 * \brief  Esta fun��o guarda a lista de gestores no ficheiro bin�rio
 *1� Abre o ficheiro bin�rio para escrita
 *2� Percorre a lista encadeada e guarda os dados de cada gestor no ficheiro
 *3� Fecha o ficheiro
 * \param lista
 * \author Alexandre Marques
 */

bool guardarGestoresbin(GestoresLista* lista);

/**
*\brief  Esta fun��o l� os dados dos gestores do ficheiro bin�rio
*1� Abre o ficheiro bin�rio para leitura
*2� Percorre o ficheiro e guarda os dados de cada gestor na lista encadeada
*3� Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

GestoresLista* lerGestoresbin(GestoresLista** listaGestores);

/**
* \brief  Esta fun��o remove um cliente da lista de gestores
* 1� Procura pelo gestor com o id correspondente na lista encadeada
* 2� Remove o cliente da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarGestoresbin
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool RemoverGestor(GestoresLista** listaGestor, int id);

/**
* \brief  Esta fun��o adiciona um novo gestor � lista de gestores
* 1� Cria um novo gestor com os dados inseridos pelo usu�rio
* 2� Adiciona o novo gestor � lista chamando a fun��o adicionarGestorLista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestorbin
 *
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool adicionarNovoGestor(GestoresLista** listaGestor);


/*
* \brief  Esta fun��o remove um cliente da lista de clientes
* 1� Procura pelo cliente com o NIF correspondente na lista encadeada
* 2� Remove o cliente da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */


bool RemoverGestor(GestoresLista** listaGestor, int id);

/**
 * Esta fun��o destroi a lista de gestores
 * 1� Percorre a lista encadeada e destroi cada n�
 * 2� Liberta a mem�ria alocada para a lista
 *
 * \param lista
 */


void DestruirListaG(GestoresLista* lista);



Gestores* obterDadosGestorEcra(Gestores* c);


#endif // !Gestorsh





