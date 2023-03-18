/*****************************************************************//**
 * \file   MeiosMobilidade.h
 * \brief  Ficheiro header dos meios de mobilidade
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

#ifndef MeiosMobilidadeh
#define MeiosMobilidadeh

enum TipoMeio {
	Bicicleta,
	Carro,
	Trotinete,
	Autocarro,
	Outro
}TipoMeio;

typedef struct MeiosMobilidade {
	int id;
	enum TipoMeio tipo;
	char localizacao[20];
	int bateria;
	float custo;
	int status;
	int autonomia;
}Meios;

typedef struct MeiosMobilidadeLista {
	Meios m;
	struct MeiosMobilidadeLista* next;
}MeiosLista;

/**
 * \brief  Função para ler os dados dos meios de mobilidade do ficheiro txt
 * 1º  Lê os dados de cada meio de mobilidade e envia para a função adicionarMeioLista que insere na lista encadeada
 *2º Guarda a lista atualizada no ficheiro binário chamando a função guardarMeiosbin
 * \param listaMeios
 * \author Alexandre Marques
 */

int lerMeiostxt(MeiosLista** listaMeios);

/**
 * \brief  Insere Meios no incio de uma lista encadeada
 1º Cria um novo nó com os dados do meio de mobilidade
 * 2º Insere o novo nó no inicio da lista
 * 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarMeiosbin
 * \param recebe uma lista e um meio de mobilidade para o inserir na lista
 * \return retorna a lista atualizada
 * \author Alexandre Marques
 */

MeiosLista* adicionarMeioListaOrdenado(MeiosLista* listaMeiosMobilidade, Meios novoMeio);

/**
 * \brief  Esta função guarda a lista de meios de mobilidade no ficheiro binário
*1º Abre o ficheiro binário para escrita
*2º Percorre a lista encadeada e guarda os dados de cada meio de mobilidade no ficheiro
*3º Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

bool guardarMeiosMobilidadebin(MeiosLista* lista);

/**
 * \brief  Esta função lê os dados dos meios de mobilidade do ficheiro binário
*1º Abre o ficheiro binário para leitura
*2º Percorre o ficheiro e guarda os dados de cada meio de mobilidade na lista encadeada
*3º Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

MeiosLista* lerMeiosbin(MeiosLista** lista);

/*/**
* \brief  Esta função adiciona um novo meio à lista de meios de mobilidade
* 1º Cria um novo meio com os dados inseridos pelo usuário
* 2º Adiciona o novo meio à lista chamando a função adicionarMeioListaOrdenado
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarMeiosMobilidadebin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */


bool adicionarNovoMeio(MeiosLista** listaMeios);

/**
* \brief  Esta função remove um meio da lista de gestores
* 1º Procura pelo meio com o id correspondente na lista encadeada
* 2º Remove o meio da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarGestoresbin
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool RemoverMeio(MeiosLista** listaMeio, int id);


void mostrarMeios(MeiosLista* lista);

Meios* obterDadosMeiosEcra(Meios* m);

bool MeioRemovidoEcra(MeiosLista** listaMeios);


#endif // !MeiosMobilidadeh



