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
 * .
 * 
 * \param id
 * \param dist
 * \return 
 */

Adj* CriaAdj(int id, float dist) {
	Adj* novo = (Adj*)calloc(1, sizeof(Adj));
	if (novo == NULL) return NULL;
	novo->id = id;
	novo->dist = dist;
	novo->next = NULL;
	return novo;
}

/**
 * .
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
 * .
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
 * .
 * 
 * \param g
 * \param idOrigem
 * \param idDestino
 * \param dist
 * \return 
 */

Vertice* AdicionaAdjacente(Vertice* g, int idOrigem, int idDestino, float dist) {
	Vertice* origem = ProcuraVertice(g, idOrigem);
	Vertice* destino = ProcuraVertice(g, idDestino);
	if (origem == NULL || destino == NULL) return g;
	bool res = false;
	Adj* novo = CriaAdj(idDestino, dist);
	origem->adjacentes = InsereAdj(origem->adjacentes, novo, &res);
	return g;
}


/**
 * .
 * 
 * \param verticeInicial
 * \param nomeArquivo
 * \return 
 */

Vertice* GuardarGrafoBinario(Vertice* verticeInicial, char* nomeArquivo) {
	FILE* arquivo = fopen(nomeArquivo, "wb");
	if (arquivo == NULL) {
		return verticeInicial;
	}

	// percorrer todos os vértices e seus adjacentes, escrevendo-os no arquivo
	Vertice* v = verticeInicial;
	while (v != NULL) {
		fwrite(v, sizeof(Vertice), 1, arquivo);
		Adj* adj = v->adjacentes;
		while (adj != NULL) {
			fwrite(adj, sizeof(Adj), 1, arquivo);
			adj = adj->next;
		}
		v = v->next;
	}

	fclose(arquivo);
}


/**
 * .
 * 
 * \param g
 * \param nomeFicheiro
 * \return 
 */

Vertice* LerFicheiroTexto(Vertice* g, char* nomeFicheiro) {
	FILE* f = fopen(nomeFicheiro, "r");
	if (f == NULL) return NULL;
	char cidade[100];
	int id, idOrigem, idDestino;
	float dist;
	while (fscanf(f, "%d %s", &id, cidade) == 2) {
		g = InsereVertice(g, id, cidade);
	}
	rewind(f);
	while (fscanf(f, "%d %s", &idOrigem, cidade) == 2) {
		while (fscanf(f, "%d %f", &idDestino, &dist) == 2) {
			g = AdicionaAdjacente(g, idOrigem, idDestino, dist);
		}
	}
	fclose(f);
	return g;
}


#pragma region Ecra

/**
 *Esta função serve para imprimir o grafo
 *
 *\param $PARAMS
 *\return $RETURN
 */

void MostraAdjacencias(Adj* h) {
	if (h == NULL) return;
	printf(" -> %s (%d) Distancia: %.2f\n", h->cidade, h->id, h->dist);
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





