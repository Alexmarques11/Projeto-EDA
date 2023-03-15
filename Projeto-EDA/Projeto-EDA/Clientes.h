/*****************************************************************//**
 * \file   Clientes.h
 * \brief  Ficheiro header dos clientes
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#define _CTR_SECURE_NO_WARNINGS

#ifndef Clientesh
#define Clientesh
#define N 35
#define A 10

typedef struct Clientes {
    char nif[10];
    float saldo;
    char nome[50];
    char morada[100];
    struct Clientes* proximo;
}Clientes;

Clientes* lerClientes(FILE* ficheiro);

bool escreverCliente(Clientes* cliente, FILE* ficheiro); 

Clientes* criarCliente();

int adicionarCliente();

Clientes* mostrarCLiente();

#endif // !Clientesh

