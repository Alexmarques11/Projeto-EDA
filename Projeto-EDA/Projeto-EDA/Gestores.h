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
	char passaword[n];
};

#endif // !Gestoresh
