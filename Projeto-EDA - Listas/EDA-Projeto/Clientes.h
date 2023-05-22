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
* \brief  Fun��o para ler os dados dos clientes do ficheiro txt
* 1�  L� os dados de cada cliente e envia para a fun��o adicionarClietneLista que insere na lista encadeada
 *2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 * \param listaClientes
 * @author Alexandre Marques
 */

int lerClientestxt(ClientesLista** listaClientes);

/**
* \brief  Insere Clientes no incio de uma lista encadeada
 *1� Cria um novo n� com os dados do cliente
 * 2� Insere o novo n� no inicio da lista
 * 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 * \param recebe uma lista e um cliente para o inserir na lista
 * @author Alexandre Marques
 */

ClientesLista* adicionarClienteLista(ClientesLista* lista, Clientes c);

/**
* \brief  Esta fun��o guarda a lista de clientes no ficheiro bin�rio
* 1� Abre o ficheiro bin�rio para escrita
* 2� Percorre a lista encadeada e guarda os dados de cada cliente no ficheiro
* 3� Fecha o ficheiro
 * \param lista
 * @author Alexandre Marques
 */

bool guardarClientesbin(ClientesLista* lista);

/**
* \brief  Esta fun��o remove um cliente da lista de clientes
* 1� Procura pelo cliente com o NIF correspondente na lista encadeada
* 2� Remove o cliente da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */

bool removerCliente(ClientesLista** listaClientes, char nif[]);

/**
* \brief  Esta fun��o adiciona um novo cliente � lista de clientes
* 1� Cria um novo cliente com os dados inseridos pelo usu�rio
* 2� Adiciona o novo cliente � lista chamando a fun��o adicionarClienteLista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */

bool adicionarNovoCliente(ClientesLista** listaClientes);

/**
* \brief  Esta fun��o l� os dados dos clientes do ficheiro bin�rio
* 1� Abre o ficheiro bin�rio para leitura
* 2� L� os dados de cada cliente e insere na lista encadeada chamando a fun��o adicionarClienteLista
* 3� Fecha o ficheiro
 *
 * \param listaClientes
 * @author Alexandre Marques
 */


ClientesLista* lerClientesbin(ClientesLista** listaClientes, char* filename);

/**
 * Esta fun��o modifica um dado de um cliente
 * 1� Procura pelo cliente com o NIF correspondente na lista encadeada
 * 2� Modifica o dado do cliente
 *
 * \param listaClientes
 * \param nif
 * \param campo
 * \return
 */

bool ModificarCliente(ClientesLista* listaClientes, char* nif, int campo);

/**
 * Esta fun��o destroi a lista de clientes
 * 1� Percorre a lista encadeada e destroi cada n�
 * 2� Liberta a mem�ria alocada para a lista
 *
 * \param lista
 */

void DestruirListaC(ClientesLista* lista);


void clienteRemovidoEcra(ClientesLista** listaClientes);


Clientes* obterDadosClienteEcra(Clientes* c);

bool ModificarDadoCliente(ClientesLista* listaClientes, char* nif, int campo);

#endif // !Clientesh

