/*****************************************************************//**
 * \file   Gestores.h
 * \brief  Ficheiro header dos gestores
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#pragma once

#include <stdio.h>
#include <stdbool.h>

#ifndef Gestoresh
#define Gestoresh
#define N 35
#define n 15

typedef struct Gestores {
	int id;
	char nome[N];
	char email[N];
	char password[n];
	struct Gestores* proximo;
}Gestores;

/**
* \brief  Esta função serve para ler os gestores do ficheiro "gestores.bin"
*
 *1º Verifica se o ficheiro existe
 * 2º Se existir, lê os gestores
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Gestores* lerGestores(FILE* ficheiro);

/**
* \brief  Esta função serve para escrever os gestores no ficheiro "gestores.bin"
 *
 * 1º Verifica se o ficheiro existe
 * 2º Se existir, escreve os gestores
 *
 * \param cliente
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverGestores(Gestores* gestor, FILE* ficheiro);

/**
* \brief  Esta função serve para criar um gestor
* 1º Pede os  dados do gestor
 *
 * @author Alexandre Marques
 */

Gestores* criarGestor();

/**
* \brief
 *1º Verifica se o ficheiro existe
 * 2º Se existir, cria um gestor
 * 3º Escreve o gestor no ficheiro
 *
 * @author Alexandre Marques
 */

int adicionarGestor();

/**
 * \brief  Esta função serve para mostrar todos os gestores que estão guardados no ficheiro "gestores.bin"
  *
  * 1º Verifa se o ficheiro existe
  * 2º Se existir, mostra todos os gestores
  *
  * @author Alexandre Marques
  */

Gestores* mostrarGestores();

#endif // !Gestoresh
