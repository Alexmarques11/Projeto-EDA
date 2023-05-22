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
    char nome[N];
    char nif[A];
    char morada[N];
    float saldo;
}Clientes;


typedef struct ClientesLista {
    Clientes c;
    struct ClientesLista* next;
}ClientesLista;

/**
* \brief  Função para ler os dados dos clientes do ficheiro txt
* 1º  Lê os dados de cada cliente e envia para a função adicionarClietneLista que insere na lista encadeada
 *2º Guarda a lista atualizada no ficheiro binário chamando a função guardarClientesbin
 * \param listaClientes
 * @author Alexandre Marques
 */

int lerClientestxt(ClientesLista** listaClientes);

/**
* \brief  Insere Clientes no incio de uma lista encadeada
 *1º Cria um novo nó com os dados do cliente
 * 2º Insere o novo nó no inicio da lista
 * 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarClientesbin
 * \param recebe uma lista e um cliente para o inserir na lista
 * @author Alexandre Marques
 */

ClientesLista* adicionarClienteLista(ClientesLista* lista, Clientes c);

/**
* \brief  Esta função guarda a lista de clientes no ficheiro binário
* 1º Abre o ficheiro binário para escrita
* 2º Percorre a lista encadeada e guarda os dados de cada cliente no ficheiro
* 3º Fecha o ficheiro
 * \param lista
 * @author Alexandre Marques
 */

bool guardarClientesbin(ClientesLista* lista);

/**
* \brief  Esta função remove um cliente da lista de clientes
* 1º Procura pelo cliente com o NIF correspondente na lista encadeada
* 2º Remove o cliente da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */

bool removerCliente(ClientesLista** listaClientes, char nif[]);

/**
* \brief  Esta função adiciona um novo cliente à lista de clientes
* 1º Cria um novo cliente com os dados inseridos pelo usuário
* 2º Adiciona o novo cliente à lista chamando a função adicionarClienteLista
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarClientesbin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */

bool adicionarNovoCliente(ClientesLista** listaClientes);

/**
* \brief  Esta função lê os dados dos clientes do ficheiro binário
* 1º Abre o ficheiro binário para leitura
* 2º Lê os dados de cada cliente e insere na lista encadeada chamando a função adicionarClienteLista
* 3º Fecha o ficheiro
 *
 * \param listaClientes
 * @author Alexandre Marques
 */


ClientesLista* lerClientesbin(ClientesLista** listaClientes, char* filename);

/**
 * Esta função modifica um dado de um cliente
 * 1º Procura pelo cliente com o NIF correspondente na lista encadeada
 * 2º Modifica o dado do cliente
 *
 * \param listaClientes
 * \param nif
 * \param campo
 * \return
 */

bool ModificarCliente(ClientesLista* listaClientes, char* nif, int campo);

/**
 * Esta função destroi a lista de clientes
 * 1º Percorre a lista encadeada e destroi cada nó
 * 2º Liberta a memória alocada para a lista
 *
 * \param lista
 */

void DestruirListaC(ClientesLista* lista);


void clienteRemovidoEcra(ClientesLista** listaClientes);


Clientes* obterDadosClienteEcra(Clientes* c);

bool ModificarDadoCliente(ClientesLista* listaClientes, char* nif, int campo);

#endif // !Clientesh

