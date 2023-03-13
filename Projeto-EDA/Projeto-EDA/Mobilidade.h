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
	float custo;
	bool status;
}Mobilidade;


#endif // !Mobilidadeh

