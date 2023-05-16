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
#include "Clientes.h"
#include "MeiosMobilidade.h"
#define _CTR_SECURE_NO_WARNINGS


#ifndef Aluguerh
#define Aluguerh

typedef struct DadosAluguer {
	int id;
	char data[11];
	int duracao;
	float preco;
}DadosAluguer;

typedef struct Aluguer {
	Clientes cliente;
	Meios meio;
	DadosAluguer dados;
}Aluguer;

typedef struct AluguerLista {
	Aluguer a;
	struct AluguerLista* next;
}AluguerLista;

Aluguer* ConstruirAluguer(Aluguer* lista, Clientes c, Meios m, DadosAluguer d);

AluguerLista* adicionarAluguerLista(AluguerLista* lista, Aluguer a);

#endif // !Aluguerh

