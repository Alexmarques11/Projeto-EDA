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
 * \brief  Fun��o para ler os dados dos meios de mobilidade do ficheiro txt
 * 1�  L� os dados de cada meio de mobilidade e envia para a fun��o adicionarMeioLista que insere na lista encadeada
 *2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarMeiosbin
 * \param listaMeios
 * \author Alexandre Marques
 */

int lerMeiostxt(MeiosLista** listaMeios);

/**
 * \brief  Insere Meios no incio de uma lista encadeada
 1� Cria um novo n� com os dados do meio de mobilidade
 * 2� Insere o novo n� no inicio da lista
 * 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarMeiosbin
 * \param recebe uma lista e um meio de mobilidade para o inserir na lista
 * \return retorna a lista atualizada
 * \author Alexandre Marques
 */

MeiosLista* adicionarMeioListaOrdenado(MeiosLista* listaMeiosMobilidade, Meios novoMeio);

/**
 * \brief  Esta fun��o guarda a lista de meios de mobilidade no ficheiro bin�rio
*1� Abre o ficheiro bin�rio para escrita
*2� Percorre a lista encadeada e guarda os dados de cada meio de mobilidade no ficheiro
*3� Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

bool guardarMeiosMobilidadebin(MeiosLista* lista);

/**
 * \brief  Esta fun��o l� os dados dos meios de mobilidade do ficheiro bin�rio
*1� Abre o ficheiro bin�rio para leitura
*2� Percorre o ficheiro e guarda os dados de cada meio de mobilidade na lista encadeada
*3� Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

MeiosLista* lerMeiosbin(MeiosLista** lista);

/*/**
* \brief  Esta fun��o adiciona um novo meio � lista de meios de mobilidade
* 1� Cria um novo meio com os dados inseridos pelo usu�rio
* 2� Adiciona o novo meio � lista chamando a fun��o adicionarMeioListaOrdenado
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarMeiosMobilidadebin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */


bool adicionarNovoMeio(MeiosLista** listaMeios);

/**
* \brief  Esta fun��o remove um meio da lista de gestores
* 1� Procura pelo meio com o id correspondente na lista encadeada
* 2� Remove o meio da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarGestoresbin
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool RemoverMeio(MeiosLista** listaMeio, int id);


void mostrarMeios(MeiosLista* lista);

Meios* obterDadosMeiosEcra(Meios* m);

bool MeioRemovidoEcra(MeiosLista** listaMeios);


#endif // !MeiosMobilidadeh



