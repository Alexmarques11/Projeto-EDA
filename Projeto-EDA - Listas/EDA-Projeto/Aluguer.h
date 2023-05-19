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
	int duracao;
	float preco;
}Aluguer;

typedef struct AluguerLista {
	Aluguer a;
	struct AluguerLista* next;
}AluguerLista;


/**
 * .
 * 
 * \param $PARAMS
 * \return $RETURN
 */
//Aluguer* ConstruirAluguer(Aluguer* lista, Clientes c, Meios m, DadosAluguer d);

/**
 * .
 * 
 * \param $PARAMS
 * \return $RETURN
 */

AluguerLista* adicionarAluguerLista(AluguerLista* lista, Aluguer a);

#endif // !Aluguerh

