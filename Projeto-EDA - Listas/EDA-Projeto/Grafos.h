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
 * Esta fun��o serve para criar um novo grafo
 * 
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaGrafo();

/**
 * .Esta fun��o serve para inserir um novo vertice
 * 1� passo: verificar se o grafo est� vazio
 * 2� passo: se estiver vazio, inserir o novo vertice
 * 3� passo: se n�o estiver vazio, percorrer a lista de vertices at� encontrar a posi��o correta
 * 3� passo: inserir o novo vertice na posi��o correta
 * 4� passo: retornar o grafo
 *
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* InsereVertice(Vertice* g, Vertice* novo, bool* res);

/**
 * .Esta fun��o serve na criar um novo vertice
 * 1� passo: criar um novo vertice
 * 2� passo: inserir o novo vertice na lista de vertices
 * 3� passo: retornar o grafo
 *
 * \param $PARAMS
 * \return $RETURN
 */
Vertice* CriaVertice(char* cidade, int tot);

/**
 * Esta fun��o serve para criar um novo adjacente
 * 1� passo: criar um novo adjacente
 * 2� passo: retornar o adjacente
 *
 * \param id
 * \param dist
 * \return
 */

Adj* CriaAdj(int id, int dist);

/**
 * Esta fun��o serve para inserir um novo adjacente
 * 1� passo: verificar se o adjacente est� vazio
 * 2� passo: se estiver vazio, inserir o novo adjacente
 * 3� passo: se n�o estiver vazio, percorrer a lista de adjacente at� encontrar a posi��o correta
 * 4� passo: inserir o novo adjacente na posi��o correta
 *
 * \param g
 * \param novo
 * \param res
 * \return
 */

Adj* InsereAdj(Adj* g, Adj* novo, bool* res);

/**
 * Esta fun��o serve para procurar um vertice
 * 1� passo: percorrer a lista de vertices at� encontrar o vertice
 * 2� passo: retornar o vertice
 * 3� passo: se n�o encontrar o vertice, retornar NULL
 *
 * \param g
 * \param id
 * \return
 */

Vertice* ProcuraVertice(Vertice* g, int id);

/**
 * Esta fun��o serve para adicionar um adjacente
 * 1� passo: procurar o vertice de origem
 * 2� passo: procurar o vertice de destino
 * 3� passo: criar um novo adjacente
 * 4� passo: inserir o novo adjacente na lista de adjacente
 * 5� passo: retornar o grafo
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
  * Esta fun��o serve para ler um grafo de um ficheiro bin�rio
  * 1� passo: verificar se o ficheiro existe
  * 2� passo: abrir o ficheiro
  * 3� passo: ler o ficheiro e guardar os vertices no grafo
  * 4� passo: fechar o ficheiro
  *
  * \param h
  * \param fileName
  * \param res
  * \return
  */

Vertice* LerGrafoBin(Vertice* h, char* fileName, bool* res);

/**
 * Esta fun��o serve para ler os adjacentes de um ficheiro bin�rio
 * 1� passo: verificar se o ficheiro existe
 * 2� passo: abrir o ficheiro
 * 3� passo: ler o ficheiro e guardar os adjacentes no grafo
 * 4� passo: fechar o ficheiro
 *
 * \param h
 * \param fileName
 * \param res
 * \return
 */

Vertice* LerAdjBin(Vertice* g, bool* res);

 /**
  * Esta fun��o serve para destruir o grafo
  * 1� passo: verificar se o grafo est� vazio
  * 2� passo: se n�o estiver vazio, percorrer a lista de vertices e destruir os adjacentes
  * 3� passo: destruir o vertice
  *
  * \param g
  * \return
  */

Vertice* DestruirGrafo(Vertice* g);

/**
 * Esta fun��o serve para destruir a lista de adjacencias
 * 1� passo: verificar se a lista de adjacencias est� vazia
 * 2� passo: se n�o estiver vazia, percorrer a lista de adjacencias e destruir os adjacentes
 *
 * \param h
 * \return
 */

Adj* DestruirAdjacencia(Adj* h);

#pragma region Ecra

void MostraGrafo(Vertice* g);

#pragma endregion

#endif // !Grafosh

