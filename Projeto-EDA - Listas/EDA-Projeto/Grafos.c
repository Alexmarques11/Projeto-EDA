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
 * Esta função serve para converter o nome da cidade para o id
 * 1º passo: percorrer a lista de vertices até encontrar o vertice
 * 2º passo: retornar o id
 * 3º passo: se não encontrar o vertice, retornar NULL
 * 
 * \param g
 * \param nome
 * \return 
 */

int ConverterNomeParaID(Vertice* g, char* nome) {
	Vertice* aux = g;
	while (aux != NULL) {
		if (strcmp(aux->cidade, nome) == 0) {
			return aux->id;
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
 * Esta função realiza uma busca em profundidade recursiva em um grafo a partir de um vértice de origem,
 * ela verifica se existe um caminho entre a origem e o destino no grafo.
 * 1º passo: verificar se o grafo está vazio
 * 2º passo: verificar se o vértice de origem e o vértice de destino existem no grafo
 * 3º passo: marcar o vértice de origem como visitado
 * 4º passo: percorrer a lista de adjacentes do vértice de origem
 * 5º passo: verificar se o vértice adjacente já foi visitado
 * 6º passo: se o vértice adjacente não foi visitado, chamar a função recursivamente
 *
 * \param g       Ponteiro para o primeiro vértice do grafo
 * \param origem  Valor do vértice de origem
 * \param dest    Valor do vértice de destino
 * \return        Retorna true se existe um caminho entre a origem e o destino, caso contrário, retorna false.
 */

bool DepthFirstSearchRec(Vertice* g, int origem, int dest) {
	if (origem == dest)
		return true;

	Vertice* aux = ProcuraVertice(g, origem);
	aux->visitado = true;
	//printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

	Adj* adj = aux->adjacentes;
	while (adj) {
		Vertice* adjacente = ProcuraVertice(g, adj->id);
		if (adjacente->visitado == false) {
			bool existe = DepthFirstSearchRec(g, adj->id, dest);
			if (existe)
				return true;
		}
		adj = adj->next;
	}
	return false;
}

/**
 * Esta função calcula a distância entre dois vértices em um grafo.
 *
 * \param g       Ponteiro para o primeiro vértice do grafo
 * \param origem  Valor do vértice de origem
 * \param dest    Valor do vértice de destino
 * \return        Retorna a distância entre os vértices origem e destino. Se não houver um caminho, retorna -1.
 */

int CalculaDistancia(Vertice* g, int origem, int dest) {
	if (g == NULL)
		return -1;

	if (origem == dest)
		return 0;

	// Inicialização dos vértices
	Vertice* verticeAtual = ProcuraVertice(g, origem);
	verticeAtual->visitado = true;

	// Array para armazenar as distâncias
	int* distancias = (int*)malloc(sizeof(int) * 100); // Tamanho máximo do array
	for (int i = 0; i < 100; i++) {
		distancias[i] = INT_MAX;
	}
	distancias[verticeAtual->id] = 0;

	// Fila para armazenar os vértices a serem visitados
	Vertice** fila = (Vertice**)malloc(sizeof(Vertice*) * 100); // Tamanho máximo da fila
	int frente = 0;
	int tras = 0;
	fila[tras++] = verticeAtual;

	while (frente != tras) {
		Vertice* v = fila[frente++];
		Adj* adjacente = v->adjacentes;

		while (adjacente != NULL) {
			Vertice* adjacenteVertice = ProcuraVertice(g, adjacente->id);

			if (adjacenteVertice->visitado == false) {
				adjacenteVertice->visitado = true;
				distancias[adjacenteVertice->id] = distancias[v->id] + adjacente->dist;

				if (adjacenteVertice->id == dest) {
					int distancia = distancias[adjacenteVertice->id];

					// Resetar os vértices
					for (int i = 0; i < tras; i++) {
						fila[i]->visitado = false;
					}
					free(distancias);
					free(fila);
					return distancia;
				}

				fila[tras++] = adjacenteVertice;
			}
			adjacente = adjacente->next;
		}
	}

	// Resetar os vértices
	for (int i = 0; i < tras; i++) {
		fila[i]->visitado = false;
	}
	free(distancias);
	free(fila);

	return -1; 
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





