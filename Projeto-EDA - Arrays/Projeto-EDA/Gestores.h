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
* \brief  Esta fun��o serve para ler os gestores do ficheiro "gestores.bin"
*
 *1� Verifica se o ficheiro existe
 * 2� Se existir, l� os gestores
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Gestores* lerGestores(FILE* ficheiro);

/**
* \brief  Esta fun��o serve para escrever os gestores no ficheiro "gestores.bin"
 *
 * 1� Verifica se o ficheiro existe
 * 2� Se existir, escreve os gestores
 *
 * \param cliente
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverGestores(Gestores* gestor, FILE* ficheiro);

/**
* \brief  Esta fun��o serve para criar um gestor
* 1� Pede os  dados do gestor
 *
 * @author Alexandre Marques
 */

Gestores* criarGestor();

/**
* \brief
 *1� Verifica se o ficheiro existe
 * 2� Se existir, cria um gestor
 * 3� Escreve o gestor no ficheiro
 *
 * @author Alexandre Marques
 */

int adicionarGestor();

/**
 * \brief  Esta fun��o serve para mostrar todos os gestores que est�o guardados no ficheiro "gestores.bin"
  *
  * 1� Verifa se o ficheiro existe
  * 2� Se existir, mostra todos os gestores
  *
  * @author Alexandre Marques
  */

Gestores* mostrarGestores();

#endif // !Gestoresh
