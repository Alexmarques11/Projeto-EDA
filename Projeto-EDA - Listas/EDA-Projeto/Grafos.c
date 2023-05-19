/*****************************************************************//**
 * \file   Grafos.c
 * \brief  Desenvolvimento do grafo
 * 
 * \author Utilizador Alexandre Marques
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h"	


/*
 .Esta função serve para criar um novo grafo
 *
* \param $PARAMS
* \return $RETURN
*/
Vertice* CriaGrafo() {
	return NULL;
}

  /**
   * .Esta função serve na criar um novo vertice
   * 1º passo: criar um novo vertice
   * 2º passo: inserir o novo vertice na lista de vertices
   * 3º passo: retornar o grafo
   *
   * \param $PARAMS
   * \return $RETURN
   */
Vertice* CriaVertice(char* cidade, int id) {
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) return NULL;
	novo->id = id;
	strcpy(novo->cidade, cidade);
	novo->next = NULL;			
	novo->adjacentes = NULL;	
	return novo;
}

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
Vertice* InsereVertice(Vertice* g, Vertice* novo, bool* res) {
	if (g == NULL) {
		g = novo;
		*res = true;
		return g;
	}
	else
	{
		Vertice* aux = g;
		Vertice* ant = aux;
		while (aux && aux->id < novo->id) {
			ant = aux;
			aux = aux->next;
		}
		if (aux == g) {
			novo->next = g;
			g = novo;
		}
		else
		{
			novo->next = aux;
			ant->next = novo;
		}
		*res = true;
	}
	return g;
}

/**
 * Esta função serve para criar um novo adjacente
 * 1º passo: criar um novo adjacente
 * 2º passo: retornar o adjacente
 * 
 * \param id
 * \param dist
 * \return 
 */

Adj* CriaAdj(int id, int dist) {
	Adj* novo = (Adj*)calloc(1, sizeof(Adj));
	if (novo == NULL) return NULL;
	novo->id = id;
	novo->dist = dist;
	novo->next = NULL;
	return novo;
}

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

Adj* InsereAdj(Adj* g, Adj* novo, bool* res) {
	if (g == NULL) {
		g = novo;
		*res = true;
		return g;
	}
	else {
		Adj* aux = g;
		Adj* ant = NULL;
		while (aux && aux->id < novo->id) {
			ant = aux;
			aux = aux->next;
		}
		if (ant == NULL) {
			novo->next = g;
			g = novo;
		}
		else {
			novo->next = aux;
			ant->next = novo;
		}
		*res = true;
	}
	return g;
}

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

Vertice* ProcuraVertice(Vertice* g, int id) {
    Vertice* aux = g;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

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

Vertice* AdicionaAdjacente(Vertice* g, int idOrigem, int idDestino, int dist) {
	Vertice* origem = ProcuraVertice(g, idOrigem);
	Vertice* destino = ProcuraVertice(g, idDestino);
	if (origem == NULL || destino == NULL) return g;
	bool res = false;
	Adj* novo = CriaAdj(idDestino, dist);
	origem->adjacentes = InsereAdj(origem->adjacentes, novo, &res);
	return g;
}


/**
 * Esta função serve para guardar um grafo num ficheiro binário
 * 1º passo: verificar se o grafo está vazio
 * 2º passo: abrir o ficheiro
 * 3º passo: percorrer a lista de vertices e guardar os vertices no ficheiro
 * 4º passo: percorrer a lista de adjacente e guardar os adjacentes no ficheiro
 * 5º passo: fechar o ficheiro
 * 
 * \param h
 * \param fileName
 * \return 
 */

int GuardarGrafoBin(Vertice* h, char* fileName) {
	if (h == NULL) return -1;
	FILE* fp;
	int r;

	fp = fopen(fileName, "wb");

	if (fp == NULL) return -2;

	Vertice* aux = h;
	VerticeFile auxFicheiro;

	while (aux != NULL) {
		auxFicheiro.id = aux->id;
		strcpy(auxFicheiro.cidade, aux->cidade);
		fwrite(&auxFicheiro, 1, sizeof(VerticeFile), fp);

		if (aux->adjacentes) {
			r = GuardarAdjBin(aux->adjacentes, aux->cidade, aux->id);

		}
		aux = aux->next;
	}

	fclose(fp);
	return 1;
}

/**
 * Esta função serve para guardar os adjacentes num ficheiro binário
 * 1º passo: verificar se o adjacente está vazio
 * 2º passo: abrir o ficheiro
 * 3º passo: percorrer a lista de adjacente e guardar os adjacentes no ficheiro
 * 4º passo: fechar o ficheiro
 * 
 * \param h
 * \param fileName
 * \param codVerticeOrigem
 * \return 
 */

int GuardarAdjBin(Adj* h, char* fileName, int codVerticeOrigem) {
	FILE* fp;

	if (h == NULL) return -2;

	fp = fopen(fileName, "ab");

	if (fp == NULL) {
		return -1;
	}
	Adj* aux = h;
	AdjFile auxFile;

	while (aux) {
		auxFile.codDestino = aux->id;
		auxFile.codOrigem = codVerticeOrigem;
		auxFile.dist = aux->dist;
		fwrite(&auxFile, 1, sizeof(AdjFile), fp);
		aux = aux->next;
	}

	fclose(fp);
	return 1;
}

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

Vertice* LerGrafoBin(Vertice* h, char* fileName, bool* res) {
	*res = false;
	
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) return NULL;

	VerticeFile aux;
	Vertice* novo;

	while (fread(&aux, 1, sizeof(VerticeFile), fp))
	{
		novo = CriaVertice(aux.cidade, aux.id);
		h = InsereVertice(h, novo, res);
	}
	fclose(fp);
	return h;
}

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

Vertice* LerAdjBin(Vertice* g, bool* res) {
	*res = false;
	FILE* fp;

	AdjFile aux;
	Vertice* auxGraph = g;
	while (auxGraph) {
		fp = fopen(auxGraph->cidade, "rb");
		if (fp != NULL) {
			while (fread(&aux, 1, sizeof(AdjFile), fp)) {
				g = AdicionaAdjacente(g, aux.codOrigem, aux.codDestino, aux.dist, res);
			}
			fclose(fp);
		}
		auxGraph = auxGraph->next;
	}
	return g;
}


/**
 * Esta função serve para destruir o grafo
 * 1º passo: verificar se o grafo está vazio
 * 2º passo: se não estiver vazio, percorrer a lista de vertices e destruir os adjacentes
 * 3º passo: destruir o vertice
 * 
 * \param g
 * \return 
 */

Vertice* DestruirGrafo(Vertice* g) {
	if (g == NULL) return NULL;
	Vertice* aux = NULL;
	while (g) {
		if (g->next)
			aux = g->next;
		g->adjacentes = DestruirAdjacencia(g->adjacentes);
		free(g);
		g = aux;
		aux = NULL;
	}
	return g;
}

/**
 * Esta função serve para destruir a lista de adjacencias
 * 1º passo: verificar se a lista de adjacencias está vazia
 * 2º passo: se não estiver vazia, percorrer a lista de adjacencias e destruir os adjacentes
 * 
 * \param h
 * \return 
 */

Adj* DestruirAdjacencia(Adj* h) {
	if (h == NULL) return NULL;
	Adj* aux = NULL;
	while (h) {
		if (h->next != NULL)
			aux = h->next;
		free(h);
		h = aux;
		aux = NULL;
	}
	return h;
}

#pragma region Ecra


void MostraAdjacencias(Adj* h) {
	if (h == NULL) return;
	printf(" -> %s (%d) Distancia: %d\n", h->cidade, h->id, h->dist);
	MostraAdjacencias(h->next);
}

void MostraGrafo(Vertice* g) {
	if (g == NULL) return;
	printf("V: %d - %s\n", g->id, g->cidade);
	MostraAdjacencias(g->adjacentes);
	printf("\n"); // imprime uma linha em branco para separar os vértices
	MostraGrafo(g->next);
}


#pragma endregion





