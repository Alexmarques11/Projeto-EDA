/*****************************************************************//**
 * \file   FMeiosMobilidade.c
 * \brief  Desenvolvimento das funções dos meios de mobilidade
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "MeiosMobilidade.h"
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS

/**
 * \brief  Função para ler os dados dos meios de mobilidade do ficheiro txt
* 1º  Lê os dados de cada meio de mobilidade e envia para a função adicionarMeioMobilidadeLista que insere na lista encadeada
*2º Guarda a lista atualizada no ficheiro binário chamando a função guardarMeiosMobilidadebin
 \param listaMeiosMobilidade
* @author Alexandre Marques
*/


int lerMeiostxt(MeiosLista** listaMeiosMobilidade) {
	FILE* ficheiro = fopen("MeiosMobilidade.txt", "r");
	if (ficheiro == NULL) {
		return 0;
	}
	// Lê os dados de cada cliente e insere na lista encadeada
	char linha[200];
	while (fgets(linha, 200, ficheiro) != NULL) {
		Meios novoMeio;
		char tipoMeio[20];
		sscanf(linha, "%d;%[^;];%[^;];%d;%d", &novoMeio.id, tipoMeio, novoMeio.localizacao, &novoMeio.bateria, &novoMeio.status);

		if (strcmp(tipoMeio, "Bicicleta") == 0) {
			novoMeio.tipo = Bicicleta;
		}
		else if (strcmp(tipoMeio, "Carro") == 0) {
			novoMeio.tipo = Carro;
		}
		else if (strcmp(tipoMeio, "Trotinete") == 0) {
			novoMeio.tipo = Trotinete;
		}
		else if (strcmp(tipoMeio, "Autocarro") == 0) {
			novoMeio.tipo = Autocarro;
		}
		else {
			novoMeio.tipo = Outro;
		}

		novoMeio.autonomia = calcularAutonomia(&novoMeio);

		*listaMeiosMobilidade = adicionarMeioListaOrdenado(*listaMeiosMobilidade, novoMeio);
	}
	fclose(ficheiro);
	return 1;
}


/**
 * \brief  Função para adicionar um meio de mobilidade à lista encadeada
* 1º Cria um novo nó
* 2º Insere os dados do meio de mobilidade no nó
* 3º Insere o nó na lista encadeada
* 4º Retorna a lista atualizada
* @param listaMeiosMobilidade
* @param novoMeio
* @return listaMeiosMobilidade
* @author Alexandre Marques
*/

MeiosLista* adicionarMeioListaOrdenado(MeiosLista* listaMeiosMobilidade, Meios novoMeio) {
	MeiosLista* novoNo = (MeiosLista*)malloc(sizeof(MeiosLista));
	novoNo->m = novoMeio;
	novoNo->next = NULL;

	if (listaMeiosMobilidade == NULL) {
		return novoNo;
	}
	else if (listaMeiosMobilidade->m.autonomia < novoMeio.autonomia) {
		novoNo->next = listaMeiosMobilidade;
		return novoNo;
	}
	else {
		MeiosLista* atual = listaMeiosMobilidade;
		while (atual->next != NULL && atual->next->m.autonomia > novoMeio.autonomia) {
			atual = atual->next;
		}
		novoNo->next = atual->next;
		atual->next = novoNo;
		return listaMeiosMobilidade;
	}
}


/**
 *\brief  Esta função guarda a lista de meios de mobilidade no ficheiro binário
 *1º Abre o ficheiro binário para escrita
 *2º Percorre a lista encadeada e guarda os dados de cada meio de mobilidade no ficheiro
 *3º Fecha o ficheiro
 * \param lista
 * \author Alexandre Marques
 */

bool guardarMeiosMobilidadebin(MeiosLista* lista) {
	FILE* ficheiro = fopen("MeiosMobilidade.bin", "wb");
	if (ficheiro == NULL) {
		return false;
	}
	while (lista != NULL) {
		fwrite(&lista->m, sizeof(Meios), 1, ficheiro);
		lista = lista->next;
	}
	fclose(ficheiro);
	return true;
}

/**
*\brief  Esta função lê os dados dos meios de mobilidade do ficheiro binário
*1º Abre o ficheiro binário para leitura
*2º Percorre o ficheiro e guarda os dados de cada meio na lista encadeada
*3º Fecha o ficheiro
* \param lista
* \author Alexandre Marques
*/

MeiosLista* lerMeiosbin(MeiosLista** listaMeios) {
	FILE* ficheiro = fopen("MeiosMobilidade.bin", "rb");
	if (ficheiro == NULL) {
		return 0;
	}
	Meios novoMeio;
	while (fread(&novoMeio, sizeof(Meios), 1, ficheiro) != 0) {
		*listaMeios = adicionarMeioListaOrdenado(*listaMeios, novoMeio);
		}
	fclose(ficheiro);
	return listaMeios;
}

/*/**
* \brief  Esta função adiciona um novo meio à lista de meios de mobilidade
* 1º Cria um novo meio com os dados inseridos pelo usuário
* 2º Adiciona o novo meio à lista chamando a função adicionarMeioListaOrdenado
 *
 * \param listaClientes
 * @author Alexandre Marques
 */
 

bool adicionarNovoMeio(MeiosLista** listaMeios) {
	// Cria um novo meio com os dados inseridos pelo usuário
	Meios novoMeio;
	obterDadosMeiosEcra(&novoMeio);
	// Adiciona o novo meio à lista
	*listaMeios = adicionarMeioListaOrdenado(*listaMeios, novoMeio);
	
	return true;
}

/**
* \brief  Esta função remove um meio da lista de gestores
* 1º Procura pelo meio com o id correspondente na lista encadeada
* 2º Remove o meio da lista encadeada
* 3º Atualiza o arquivo binário com a lista atualizada chamando a função guardarGestoresbin
 * \param $PARAMS
 * @author Alexandre Marques
 */

bool RemoverMeio(MeiosLista** listaMeios, int id) {
	if (listaMeios == NULL) {
		return false;
	}
	MeiosLista* meioAtual = *listaMeios;
	MeiosLista* meioAnterior = NULL;
	bool encontrado = false;
	// Procura pelo cliente com o id correspondente na lista encadeada
	while (meioAtual != NULL) {
		if (meioAtual->m.id == id) {
			encontrado = true;
			break;
		}
		meioAnterior = meioAtual;
		meioAtual = meioAtual->next;
	}
	if (!encontrado) {
		return false;
	}
	// Remove o meio da lista encadeada
	if (meioAnterior == NULL) {
		*listaMeios = meioAtual->next;
	}
	else
	{
		meioAnterior->next = meioAtual->next;
	}
	
	return true;

}

/**
 * Esta função procura um meio de mobilidade na lista de meios por id
 * 1º Percorre a lista encadeada e compara o id do meio com o id inserido pelo usuário
 * 2º Retorna o meio se for encontrado
 * 
 * \param listaMeios
 * \param id
 * \return 
 */

Meios* procurarMeioPorId(MeiosLista* listaMeios, int id) {
	MeiosLista* current = listaMeios;
	while (current != NULL) {
		if (current->m.id == id) {
			return &(current->m);
		}
		current = current->next;
	}
	return NULL;  // Retorna NULL se o meio de mobilidade não for encontrado
}

/**
 * Esta função modifica um dado de um meio de mobilidade
 * 1º Procura o meio de mobilidade na lista de meios por id
 * 2º Modifica o dado do meio de mobilidade
 * 
 * \param listaMeios
 * \param id
 * \param campo
 * \return 
 */

bool ModificarMeioMobilidade(MeiosLista* listaMeios, int id, int campo) {
	bool sucesso = false;

	sucesso = ModificarDadoMeioMobilidade(listaMeios, id, campo);

	return sucesso;
}


/**
 * Esta função destroi a lista de meios de mobilidade
 * 1º Percorre a lista encadeada e destroi cada nó
 * 2º Atribui NULL à lista
 * 
 * \param lista
 */

void DestruirListaM(MeiosLista* lista) {
	MeiosLista* atual = lista;
	while (atual != NULL) {
		MeiosLista* proximo = atual->next;
		free(atual);
		atual = proximo;
	}
}

/**
 * Esta função calcula a autonomia de um meio de mobilidade
 * 1º Calcula a autonomia de acordo com o tipo de meio de mobilidade
 * 2º Retorna a autonomia
 * 
 * \param meio
 * \return 
 */

int calcularAutonomia(Meios* m) {
	switch (m->tipo) {
	case Bicicleta:
		m->autonomia = m->bateria / 6;
		break;
	case Carro:
		m->autonomia = m->bateria / 3;
		break;
	case Trotinete:
		m->autonomia = m->bateria / 5;
		break;
	case Autocarro:
		m->autonomia = m->bateria / 4;
		break;
	default:
		// Defina um valor de autonomia padrão para outros tipos de meios de mobilidade, se necessário
		break;
	}

	return m->autonomia;
}




#pragma region Ecra

void mostrarMeios(MeiosLista* lista) {
	printf("Lista de meios de mobilidade:\n\n");
	while (lista != NULL) {
		printf("ID: %d\n", lista->m.id);
		printf("Tipo: ");
		switch (lista->m.tipo) {
		case Bicicleta:
			printf("Bicicleta\n");
			break;
		case Carro:
			printf("Carro\n");
			break;
		case Trotinete:
			printf("Trotinete\n");
			break;
		case Autocarro:
			printf("Autocarro\n");
			break;
		case Outro:
			printf("Outro\n");
			break;
		default:
			printf("Desconhecido\n");
			break;
		}
		printf("Localizacao: %s\n", lista->m.localizacao);
		printf("Bateria: %d\n", lista->m.bateria);
		printf("Autonomia: %d\n", lista->m.autonomia);
		printf("Status: %d\n", lista->m.status);
		printf("\n");
		lista = lista->next;
	}
}

Meios* obterDadosMeiosEcra(Meios* m) {
	int x = 0;
	printf("ID: ");
	scanf("%d", &m->id);
	printf("Tipo (0 - Bicicleta, 1 - Carro, 2 - Trotinete, 3 - Autocarro, 4 - Outro): ");
	scanf("%d", &x);
	switch (x) {
	case 0:
		m->tipo = Bicicleta;
		break;
	case 1:
		m->tipo = Carro;
		break;
	case 2:
		m->tipo = Trotinete;
		break;
	case 3:
		m->tipo = Autocarro;
		break;
	case 4:
		m->tipo = Outro;
		break;
	default:
		break;
	}

	m->autonomia = calcularAutonomia(m);

	printf("Localizacao: ");
	scanf("%s", m->localizacao);
	printf("Bateria: ");
	scanf("%d", &m->bateria);
	printf("Status (0 - Inativo, 1 - Ativo): ");
	scanf("%d", &m->status);
	return m;
}


bool MeioRemovidoEcra(MeiosLista** listaMeios) {
	int id;
	printf("Introduza o ID do meio que pretende remover: ");
	scanf("%d", &id);
	if (RemoverMeio(listaMeios, id)) {
		return true;
	}
	else {
		return false;
	}
}

bool ModificarDadoMeioMobilidade(MeiosLista* listaMeios, int id, int campo) {
	Meios* meio = procurarMeioPorId(listaMeios, id);

	if (meio == NULL) {
		return false;
	}

	switch (campo) {
	case 1:
		printf("Novo Tipo (0 - Bicicleta, 1 - Carro, 2 - Trotinete, 3 - Autocarro, 4 - Outro): ");
		int novoTipo;
		scanf("%d", &novoTipo);
		meio->tipo = novoTipo;
		break;
	case 2:
		printf("Nova Localizacao: ");
		scanf("%s", meio->localizacao);
		break;
	case 3:
		printf("Nova Bateria: ");
		scanf("%d", &meio->bateria);
		break;
	case 4:
		printf("Novo Status (0 - Inativo, 1 - Ativo): ");
		int novoStatus;
		scanf("%d", &novoStatus);
		meio->status = novoStatus;
		break;
	default:
		printf("Campo inválido.\n");
		break;
	}
	return true;
}


#pragma endregion


