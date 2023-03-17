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
* \brief  Esta função serve para ler os meios de mobilidade do ficheiro "mobilidade.bin"
*
 *1º Verifica se o ficheiro existe
 * 2º Se existir, lê os gestores
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Mobilidade* lerMeios(FILE* ficheiro);

/**
* \brief  Esta função serve para escrever os gestores no ficheiro "mobilidade.bin"
 *
 * 1º Verifica se o ficheiro existe
 * 2º Se existir, escreve os meios de mobilidade
 *
 * \param meios
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverMeios(Mobilidade* mobilidade, FILE* ficheiro);

/**
* \brief  Esta função serve para criar um gestor
* 1º Pede os  dados do gestor
 *
 * @author Alexandre Marques
 */

Mobilidade* criarMeio();

/**
* \brief
 *1º Verifica se o ficheiro existe
 * 2º Se existir, cria um meio de mobilidade
 * 3º Escreve o meio no ficheiro
 *
 * @author Alexandre Marques
 */

int adicionarMeio();

/**
 * \brief  Esta função serve para mostrar todos os meios que estão guardados no ficheiro "mobilidade.bin"
  *
  * 1º Verifa se o ficheiro existe
  * 2º Se existir, mostra todos os meios
  *
  * @author Alexandre Marques
  */

Mobilidade* mostrarMeios();

#endif // !Mobilidadeh

