/*****************************************************************//**
 * \file   Grafos.h
 * \brief  Ficheiro header para a estrutura de dados grafos
 * 
 * \author Utilizador Alexandre Marques
 * \date   May 2023
 *********************************************************************/

#pragma once

#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS

#ifndef Grafosh
#define Grafosh
#define N 20

typedef struct Adj {
	int id;	
	char cidade[N];
	float dist;		
	bool pcontrolo;
	struct Adj* next;
}Adj;

typedef struct Vertice {
	int id;					
	char cidade[N];				
	struct Vertice* next;		
	struct Adj* adjacentes;		
} Vertice;

/**
 * Esta função serve para criar um novo grafo
 * 
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaGrafo();

/**
 * .Esta função serve para inserir um novo vertice
 * 
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* InsereVertice(Vertice* g, Vertice* novo, bool* res);

/**
 * .Esta função serve na criar um novo vertice
 * 
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaVertice(char* cidade, int tot);

/**
 * .Esta mostra o grafo
 * 
 * \param $PARAMS
 * \return $RETURN
 */

void MostraGrafo(Vertice* g);


#endif // !Grafosh

