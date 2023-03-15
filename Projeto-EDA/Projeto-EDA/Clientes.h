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

/**
* \brief  Esta função serve para ler os clientes do ficheiro "clientes.bin"
*
 *1º Verifica se o ficheiro existe
 * 2º Se existir, lê os clientes
 *
 * \param ficheiro
 * @author Alexandre Marques
 */
Clientes* lerClientes(FILE* ficheiro);

/**
* \brief  Esta função serve para escrever os clientes no ficheiro "clientes.bin"
 *
 * 1º Verifica se o ficheiro existe
 * 2º Se existir, escreve os clientes
 *
 * \param cliente
 * \param ficheiro
 * @author Alexandre Marques
 */
bool escreverCliente(Clientes* cliente, FILE* ficheiro); 

/**
* \brief  Esta função serve para criar um cliente
* 1º Pede os  dados do cliente
 *
 * @author Alexandre Marques
 */

Clientes* criarCliente();

/**
* \brief
 *1º Abrir o ficheiro
 *2º Criar um cliente
 *3º Guardar o cliente
 *4º Fechar o ficheiro
 * 
 * @author Alexandre Marques
 */

int adicionarCliente();

/**
* \brief  Esta função serve para mostrar todos os clientes que estão guardados no ficheiro "clientes.bin"
 *
 * 1º Verifa se o ficheiro existe
 * 2º Se existir, mostra todos os clientes
 *
 * @author Alexandre Marques
 */
Clientes* mostrarCLiente();

#endif // !Clientesh

