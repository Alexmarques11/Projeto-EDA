/*****************************************************************//**
 * \file   FGestores.c
 * \brief  Desenvolvimento das funções dos gestores
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Gestores.h"

/**
 * \brief  Função para ler os dados dos gestores do ficheiro txt
 * 1º  Lê os dados de cada gestor e envia para a função adicionarGestorLista que insere na lista encadeada
 *2º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestoresbin
 * \param listaGestores
 * @author Alexandre Marques
 */

int lerGestorestxt(GestoresLista** listaGestores) {
    FILE* ficheiro = fopen("Gestores.txt", "r");
    if (ficheiro == NULL) {
		return 0;
	}
	// Lê os dados de cada cliente e insere na lista encadeada
	char linha[100];
    while (fgets(linha, 200, ficheiro) != NULL) {
		Gestores novoGestor;
		sscanf(linha, "%d;%[^;];%[^;];%[^;]", &novoGestor.id, novoGestor.nome, novoGestor.email, novoGestor.password);
		*listaGestores = adicionarGestorLista(*listaGestores, novoGestor);
		 		guardarGestoresbin(*listaGestores);
		}
		fclose(ficheiro);
	return 1;
}

/**
* \brief  Insere Gestores no incio de uma lista encadeada
*1º Cria um novo nó com os dados do gestor
* 2º Insere o novo nó no inicio da lista
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestoresbin
* \param recebe uma lista e um gestor para o inserir na lista
* \return retorna a lista atualizada
* \author Alexandre Marques
*/

GestoresLista* adicionarGestorLista(GestoresLista* lista, Gestores g) {
    GestoresLista* novo = (GestoresLista*)malloc(sizeof(GestoresLista));
    if (novo == NULL) return NULL;
    novo->g = g;
    novo->next = NULL;

    // Verifica se a lista está vazia ou se o novo gestor tem o menor ID
    if (lista == NULL || g.id < lista->g.id) {
        novo->next = lista;
        return novo;
    }

    // Encontra a posição correta para inserir o novo gestor na lista ordenada
    GestoresLista* anterior = lista;
    GestoresLista* atual = lista->next;
    while (atual != NULL && atual->g.id < g.id) {
        anterior = atual;
        atual = atual->next;
    }

    novo->next = atual;
    anterior->next = novo;

    return lista;
}

/**
 * \brief  Esta função guarda a lista de gestores no ficheiro binário
 *1º Abre o ficheiro binário para escrita
 *2º Percorre a lista encadeada e guarda os dados de cada gestor no ficheiro
 *3º Fecha o ficheiro
 * \param lista
 * \author Alexandre Marques
 */


bool guardarGestoresbin(GestoresLista* lista) {
	FILE* ficheiro = fopen("Gestores.bin","wb");
    if (ficheiro == NULL) {
        return false;
    }
    while (lista != NULL) {
        fwrite(&lista->g, sizeof(Gestores), 1, ficheiro);
        lista = lista->next;
    }
    fclose(ficheiro);
    return true;

}

/**
*\brief  Esta função lê os dados dos gestores do ficheiro binário
*1º Abre o ficheiro binário para leitura
*2º Percorre o ficheiro e guarda os dados de cada gestor na lista encadeada
*3º Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/


GestoresLista* lerGestoresbin(GestoresLista** listaGestores) {
	FILE* ficheiro = fopen("Gestores.bin", "rb");
	if (ficheiro == NULL) {
		return 0;
	}
	Gestores novoGestor;
	while (fread(&novoGestor, sizeof(Gestores), 1, ficheiro) != 0) {
		*listaGestores = adicionarGestorLista(*listaGestores, novoGestor);
	}
	fclose(ficheiro);
	return listaGestores;
}

/**
* \brief  Esta função adiciona um novo gestor à lista de gestores
* 1º Cria um novo gestor com os dados inseridos pelo usuário
* 2º Adiciona o novo gestor à lista chamando a função adicionarGestorLista
* 3º Guarda a lista atualizada no ficheiro binário chamando a função guardarGestorbin
 *
 * \param $PARAMS
 * @author Alexandre Marques
 */


bool adicionarNovoGestor(GestoresLista** listaGestor) {
	Gestores novoGestor;
	obterDadosGestorEcra(&novoGestor);

	*listaGestor = adicionarGestorLista(*listaGestor, novoGestor);
	
	guardarGestoresbin(*listaGestor);
	return true;
}

/*
* \brief  Esta função remove um cliente da lista de clientes
* 1º Procura pelo cliente com o NIF correspondente na lista encadeada
* 2º Remove o cliente da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */


bool RemoverGestor(GestoresLista** listaGestor, int id) {
    GestoresLista* gestorAtual = *listaGestor;
    GestoresLista* gestorAnterior = NULL;
    bool encontrado = false;
    // Procura pelo gestor com o id correspondente na lista encadeada
    while (gestorAtual != NULL) {
        if (gestorAtual->g.id == id) {
            encontrado = true;
            break;
        }
        gestorAnterior = gestorAtual;
        gestorAtual = gestorAtual->next;
    }
    if (encontrado) {
        if (gestorAnterior == NULL) {
            *listaGestor = gestorAtual->next;
        }
        else {
            gestorAnterior->next = gestorAtual->next;
        }
		free(gestorAtual);
        guardarGestoresbin(*listaGestor);
        return true;
    }
    else {
        return false;
    }
}

/**
 * Esta função destroi a lista de gestores
 * 1º Percorre a lista encadeada e destroi cada nó
 * 2º Liberta a memória alocada para a lista
 * 
 * \param lista
 */


void DestruirListaG(GestoresLista* lista) {
    GestoresLista* atual = lista;
    while (atual != NULL) {
        GestoresLista* proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}



#pragma region Ecra

bool gestorRemovidoEcra(GestoresLista** listaGestor) {
    int id;
    printf("ID do gestor a remover: ");
    scanf("%d", &id);
    if (RemoverGestor(listaGestor, id)) {
        printf("Gestor removido com sucesso.\n");
    }
    else {
        printf("Não foi encontrado nenhum gestor com o ID %d.\n", id);
    }
}


Gestores* obterDadosGestorEcra(Gestores* g) {
	printf("ID: ");
	scanf("%d", &g->id);
	printf("Nome: ");
	scanf("%s", g->nome);
	printf("Email: ");
	scanf("%s", g->email);
	printf("Password: ");
	scanf("%s", g->password);
	return g;
}


void mostrarGestores(GestoresLista* lista) {
	printf("Lista de Gestores:\n\n");
	while (lista != NULL) {
		printf("ID: %d\n", lista->g.id);
		printf("Nome: %s\n", lista->g.nome);
		printf("Email: %s\n", lista->g.email);
		printf("\n");
		lista = lista->next;
	}
}


#pragma endregion



