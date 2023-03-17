/*****************************************************************//**
 * \file   FGestores.c
 * \brief  Desenvolvimento das fun��es dos gestores
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Gestores.h"

/**
 * \brief  Fun��o para ler os dados dos gestores do ficheiro txt
 * 1�  L� os dados de cada gestor e envia para a fun��o adicionarGestorLista que insere na lista encadeada
 *2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestoresbin
 * \param listaGestores
 * @author Alexandre Marques
 */

int lerGestorestxt(GestoresLista** listaGestores) {
    FILE* ficheiro = fopen("Gestores.txt", "r");
    if (ficheiro == NULL) {
		return 0;
	}
	// L� os dados de cada cliente e insere na lista encadeada
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
*1� Cria um novo n� com os dados do gestor
* 2� Insere o novo n� no inicio da lista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestoresbin
* \param recebe uma lista e um gestor para o inserir na lista
* \return retorna a lista atualizada
* \author Alexandre Marques
*/

GestoresLista* adicionarGestorLista(GestoresLista* lista, Gestores g) {
	GestoresLista* novo = (GestoresLista*)malloc(sizeof(GestoresLista));
	novo->g = g;
	novo->next = lista;
	guardarGestoresbin(novo);
	return novo;
}

/**
 * \brief  Esta fun��o guarda a lista de gestores no ficheiro bin�rio
 *1� Abre o ficheiro bin�rio para escrita
 *2� Percorre a lista encadeada e guarda os dados de cada gestor no ficheiro
 *3� Fecha o ficheiro
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
*\brief  Esta fun��o l� os dados dos gestores do ficheiro bin�rio
*1� Abre o ficheiro bin�rio para leitura
*2� Percorre o ficheiro e guarda os dados de cada gestor na lista encadeada
*3� Fecha o ficheiro
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
* \brief  Esta fun��o adiciona um novo gestor � lista de gestores
* 1� Cria um novo gestor com os dados inseridos pelo usu�rio
* 2� Adiciona o novo gestor � lista chamando a fun��o adicionarGestorLista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarGestorbin
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
* \brief  Esta fun��o remove um cliente da lista de clientes
* 1� Procura pelo cliente com o NIF correspondente na lista encadeada
* 2� Remove o cliente da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */


bool RemoverGestor(GestoresLista** listaGestor, int id) {
    GestoresLista* gestorAtual = *listaGestor;
    GestoresLista* gestorAnterior = NULL;
    bool encontrado = false;
    // Procura pelo cliente com o id correspondente na lista encadeada
    while (gestorAtual != NULL) {
        if (gestorAtual->g.id == id) {
			encontrado = true;
			break;
		}
		gestorAnterior = gestorAtual;
		gestorAtual = gestorAtual->next;
	}
    if (!encontrado) {
		return false;
	}
    // Remove o gestor da lista encadeada
    if (gestorAnterior == NULL) {
		*listaGestor = gestorAtual->next;
	 }
	 else 
    {
		gestorAnterior->next = gestorAtual->next;
	}
	// Atualiza o arquivo bin�rio com a lista atualizada
	guardarGestoresbin(*listaGestor);
	return true;
	
}

bool GestorRemovidoEcra(GestoresLista** listaGestor) {
	int id;
	printf("Introduza o ID do gestor que pretende remover: ");
	scanf("%d", &id);
	if (RemoverGestor(listaGestor, id)) {
		return true;
	}
	else {
		return false;
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






