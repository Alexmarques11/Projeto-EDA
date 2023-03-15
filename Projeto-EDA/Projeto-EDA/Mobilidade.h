/*****************************************************************//**
 * \file   Mobilidade.h
 * \brief  Ficheiro header dos meios de mobilidade
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#pragma once
#include <stdio.h>
#include <stdbool.h>

#ifndef Mobilidadeh
#define Mobilidadeh
#define N 35
#define n 20

typedef struct Mobilidade {
	int id;
	char tipo[n];
	char localizacao[N];
	int bateria;
	int custo;
	bool status;
	struct Mobilidade* proximo;
}Mobilidade;

/**
* \brief  Esta fun��o serve para ler os meios de mobilidade do ficheiro "mobilidade.bin"
*
 *1� Verifica se o ficheiro existe
 * 2� Se existir, l� os gestores
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Mobilidade* lerMeios(FILE* ficheiro);

/**
* \brief  Esta fun��o serve para escrever os gestores no ficheiro "mobilidade.bin"
 *
 * 1� Verifica se o ficheiro existe
 * 2� Se existir, escreve os meios de mobilidade
 *
 * \param meios
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverMeios(Mobilidade* mobilidade, FILE* ficheiro);

/**
* \brief  Esta fun��o serve para criar um gestor
* 1� Pede os  dados do gestor
 *
 * @author Alexandre Marques
 */

Mobilidade* criarMeio();

/**
* \brief
 *1� Verifica se o ficheiro existe
 * 2� Se existir, cria um meio de mobilidade
 * 3� Escreve o meio no ficheiro
 *
 * @author Alexandre Marques
 */

int adicionarMeio();

/**
 * \brief  Esta fun��o serve para mostrar todos os meios que est�o guardados no ficheiro "mobilidade.bin"
  *
  * 1� Verifa se o ficheiro existe
  * 2� Se existir, mostra todos os meios
  *
  * @author Alexandre Marques
  */

Mobilidade* mostrarMeios();

#endif // !Mobilidadeh

