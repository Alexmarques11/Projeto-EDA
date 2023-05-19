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

typedef struct Adjacencia {
	int id;	
	char cidade[N];
	int dist;		
	bool pcontrolo;
	struct Adj* next;
}Adj;

typedef struct Vertice {
	int id;					
	char cidade[N];				
	struct Vertice* next;		
	struct Adj* adjacentes;		
} Vertice;


typedef struct AdjacenciaParaFicheiro {
	int codOrigem;
	int codDestino;		
	int dist;		
}AdjFile;

typedef struct VerticeParaFicheiro {
	int id;					
	char cidade[N];				
} VerticeFile;


/**
 * Esta função serve para criar um novo grafo
 * 
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaGrafo();

/**
 * .Esta função serve para inserir um novo vertice
 * 1º passo: verificar se o grafo está vazio
 * 2º passo: se estiver vazio, inserir o novo vertice
 * 3º passo: se não estiver vazio, percorrer a lista de vertices até encontrar a posição correta
 * 3º passo: inserir o novo vertice na posição correta
 * 4º passo: retornar o grafo
 *
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* InsereVertice(Vertice* g, Vertice* novo, bool* res);

/**
 * .Esta função serve na criar um novo vertice
 * 1º passo: criar um novo vertice
 * 2º passo: inserir o novo vertice na lista de vertices
 * 3º passo: retornar o grafo
 *
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaVertice(char* cidade, int tot);

/**
 * Esta função serve para criar um novo adjacente
 * 1º passo: criar um novo adjacente
 * 2º passo: retornar o adjacente
 *
 * \param id
 * \param dist
 * \return
 */

Adj* CriaAdj(int id, int dist);

/**
 * Esta função serve para inserir um novo adjacente
 * 1º passo: verificar se o adjacente está vazio
 * 2º passo: se estiver vazio, inserir o novo adjacente
 * 3º passo: se não estiver vazio, percorrer a lista de adjacente até encontrar a posição correta
 * 4º passo: inserir o novo adjacente na posição correta
 *
 * \param g
 * \param novo
 * \param res
 * \return
 */

Adj* InsereAdj(Adj* g, Adj* novo, bool* res);

/**
 * Esta função serve para procurar um vertice
 * 1º passo: percorrer a lista de vertices até encontrar o vertice
 * 2º passo: retornar o vertice
 * 3º passo: se não encontrar o vertice, retornar NULL
 *
 * \param g
 * \param id
 * \return
 */

Vertice* ProcuraVertice(Vertice* g, int id);

/**
 * Esta função serve para adicionar um adjacente
 * 1º passo: procurar o vertice de origem
 * 2º passo: procurar o vertice de destino
 * 3º passo: criar um novo adjacente
 * 4º passo: inserir o novo adjacente na lista de adjacente
 * 5º passo: retornar o grafo
 *
 * \param g
 * \param idOrigem
 * \param idDestino
 * \param dist
 * \return
 */

Vertice* AdicionaAdjacente(Vertice* g, int idOrigem, int idDestino, int dist);

/**
 * .Esta mostra o grafo
 * 
 * \param $PARAMS
 * \return $RETURN
 */

 /**
  * Esta função serve para ler um grafo de um ficheiro binário
  * 1º passo: verificar se o ficheiro existe
  * 2º passo: abrir o ficheiro
  * 3º passo: ler o ficheiro e guardar os vertices no grafo
  * 4º passo: fechar o ficheiro
  *
  * \param h
  * \param fileName
  * \param res
  * \return
  */

Vertice* LerGrafoBin(Vertice* h, char* fileName, bool* res);

/**
 * Esta função serve para ler os adjacentes de um ficheiro binário
 * 1º passo: verificar se o ficheiro existe
 * 2º passo: abrir o ficheiro
 * 3º passo: ler o ficheiro e guardar os adjacentes no grafo
 * 4º passo: fechar o ficheiro
 *
 * \param h
 * \param fileName
 * \param res
 * \return
 */

Vertice* LerAdjBin(Vertice* g, bool* res);

 /**
  * Esta função serve para destruir o grafo
  * 1º passo: verificar se o grafo está vazio
  * 2º passo: se não estiver vazio, percorrer a lista de vertices e destruir os adjacentes
  * 3º passo: destruir o vertice
  *
  * \param g
  * \return
  */

Vertice* DestruirGrafo(Vertice* g);

/**
 * Esta função serve para destruir a lista de adjacencias
 * 1º passo: verificar se a lista de adjacencias está vazia
 * 2º passo: se não estiver vazia, percorrer a lista de adjacencias e destruir os adjacentes
 *
 * \param h
 * \return
 */

Adj* DestruirAdjacencia(Adj* h);

#pragma region Ecra

void MostraGrafo(Vertice* g);

#pragma endregion

#endif // !Grafosh

