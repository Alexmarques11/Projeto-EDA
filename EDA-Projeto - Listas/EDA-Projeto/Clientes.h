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
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS

#ifndef Clientesh
#define Clientesh
#define N 35
#define A 10

typedef struct Clientes {
    char nome[20];
    char nif[10];
    char morada[50];
    float saldo;
}Clientes;

typedef struct ClientesLista {
    Clientes c;
    struct ClientesLista* next;
}ClientesLista;

int lerClientestxt(ClientesLista** listaClientes);

ClientesLista* adicionarClienteLista(ClientesLista* lista, Clientes c);

bool guardarClientesbin(ClientesLista* lista);

Clientes* obterDadosClienteEcra(Clientes* c);

bool adicionarNovoCliente(ClientesLista** listaClientes);

ClientesLista* lerClientesbin(ClientesLista** listaClientes);

void clienteRemovidoEcra(ClientesLista** listaClientes);

bool removerCliente(ClientesLista** listaClientes, char nif[]);

#endif // !Clientesh

