/*****************************************************************//**
 * \file   Grafos.c
 * \brief  Desenvolvimento do grafo
 * 
 * \author Utilizador Alexandre Marques
 * \date   May 2023
 *********************************************************************/

#include "Grafos.h"	


/*
 .Esta fun��o serve para criar um novo grafo
 *
* \param $PARAMS
* \return $RETURN
*/
Vertice* CriaGrafo() {
	return NULL;
}

  /**
   * .Esta fun��o serve na criar um novo vertice
   * 1� passo: criar um novo vertice
   * 2� passo: inserir o novo vertice na lista de vertices
   * 3� passo: retornar o grafo
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
 * Esta fun��o serve para criar um novo adjacente
 * 1� passo: criar um novo adjacente
 * 2� passo: retornar o adjacente
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
 * Esta fun��o serve para procurar um vertice
 * 1� passo: percorrer a lista de vertices at� encontrar o vertice
 * 2� passo: retornar o vertice
 * 3� passo: se n�o encontrar o vertice, retornar NULL
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
 * Esta fun��o serve para guardar um grafo num ficheiro bin�rio
 * 1� passo: verificar se o grafo est� vazio
 * 2� passo: abrir o ficheiro
 * 3� passo: percorrer a lista de vertices e guardar os vertices no ficheiro
 * 4� passo: percorrer a lista de adjacente e guardar os adjacentes no ficheiro
 * 5� passo: fechar o ficheiro
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
 * Esta fun��o serve para guardar os adjacentes num ficheiro bin�rio
 * 1� passo: verificar se o adjacente est� vazio
 * 2� passo: abrir o ficheiro
 * 3� passo: percorrer a lista de adjacente e guardar os adjacentes no ficheiro
 * 4� passo: fechar o ficheiro
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
 * Esta fun��o serve para destruir o grafo
 * 1� passo: verificar se o grafo est� vazio
 * 2� passo: se n�o estiver vazio, percorrer a lista de vertices e destruir os adjacentes
 * 3� passo: destruir o vertice
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
 * Esta fun��o serve para destruir a lista de adjacencias
 * 1� passo: verificar se a lista de adjacencias est� vazia
 * 2� passo: se n�o estiver vazia, percorrer a lista de adjacencias e destruir os adjacentes
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
	printf("\n"); // imprime uma linha em branco para separar os v�rtices
	MostraGrafo(g->next);
}


#pragma endregion





