/*****************************************************************//**
 * \file   FMeiosMobilidade.c
 * \brief  Desenvolvimento das fun��es dos meios de mobilidade
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
 * \brief  Fun��o para ler os dados dos meios de mobilidade do ficheiro txt
* 1�  L� os dados de cada meio de mobilidade e envia para a fun��o adicionarMeioMobilidadeLista que insere na lista encadeada
*2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarMeiosMobilidadebin
 \param listaMeiosMobilidade
* @author Alexandre Marques
*/


int lerMeiostxt(MeiosLista** listaMeiosMobilidade) {
	FILE* ficheiro = fopen("MeiosMobilidade.txt", "r");
	if (ficheiro == NULL) {
		return 0;
	}
	// L� os dados de cada cliente e insere na lista encadeada
	char linha[200];
	while (fgets(linha, 200, ficheiro) != NULL) {
		Meios novoMeio;
		char tipoMeio[20];
		sscanf(linha, "%d;%[^;];%[^;];%d;%f;%d", &novoMeio.id, tipoMeio, novoMeio.localizacao, &novoMeio.bateria, &novoMeio.custo, &novoMeio.status);

		if (strcmp(tipoMeio, "Bicicleta") == 0) {
			novoMeio.tipo = Bicicleta;
			novoMeio.autonomia= ((novoMeio.bateria+20)*novoMeio.custo)/3;
		}
		else if (strcmp(tipoMeio, "Carro") == 0) {
			novoMeio.tipo = Carro;
			novoMeio.autonomia = ((novoMeio.bateria+20)*novoMeio.custo)/3;
		}
		else if (strcmp(tipoMeio, "Trotinete") == 0) {
			novoMeio.tipo = Trotinete;
			novoMeio.autonomia =((novoMeio.bateria+20)*novoMeio.custo)/3;
		}
		else if (strcmp(tipoMeio, "Autocarro") == 0) {
			novoMeio.tipo = Autocarro;
			novoMeio.autonomia = ((novoMeio.bateria + 20) * novoMeio.custo) / 3;
		}
		else {
			novoMeio.tipo = Outro;
			((novoMeio.bateria + 20) * novoMeio.custo) / 3;
		}

		*listaMeiosMobilidade = adicionarMeioListaOrdenado(*listaMeiosMobilidade, novoMeio);
		guardarMeiosMobilidadebin(*listaMeiosMobilidade);
	}
	fclose(ficheiro);
	return 1;
}

/**
 * \brief  Fun��o para adicionar um meio de mobilidade � lista encadeada
* 1� Cria um novo n�
* 2� Insere os dados do meio de mobilidade no n�
* 3� Insere o n� na lista encadeada
* 4� Retorna a lista atualizada
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
 *\brief  Esta fun��o guarda a lista de meios de mobilidade no ficheiro bin�rio
 *1� Abre o ficheiro bin�rio para escrita
 *2� Percorre a lista encadeada e guarda os dados de cada meio de mobilidade no ficheiro
 *3� Fecha o ficheiro
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
*\brief  Esta fun��o l� os dados dos meios de mobilidade do ficheiro bin�rio
*1� Abre o ficheiro bin�rio para leitura
*2� Percorre o ficheiro e guarda os dados de cada meio na lista encadeada
*3� Fecha o ficheiro
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
* \brief  Esta fun��o adiciona um novo meio � lista de meios de mobilidade
* 1� Cria um novo meio com os dados inseridos pelo usu�rio
* 2� Adiciona o novo meio � lista chamando a fun��o adicionarMeioListaOrdenado
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarMeiosMobilidadebin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */
 

bool adicionarNovoMeio(MeiosLista** listaMeios) {
	// Cria um novo meio com os dados inseridos pelo usu�rio
	Meios novoMeio;
	obterDadosMeiosEcra(&novoMeio);
	// Adiciona o novo meio � lista
	*listaMeios = adicionarMeioListaOrdenado(*listaMeios, novoMeio);
	// Guarda a lista atualizada no arquivo bin�rio
	guardarMeiosMobilidadebin(*listaMeios);
	return true;
}

/**
* \brief  Esta fun��o remove um meio da lista de gestores
* 1� Procura pelo meio com o id correspondente na lista encadeada
* 2� Remove o meio da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarGestoresbin
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
	// Atualiza o arquivo bin�rio com a lista atualizada
	guardarMeiosMobilidadebin(*listaMeios);
	return true;

}

/**
 * Esta fun��o destroi a lista de meios de mobilidade
 * 1� Percorre a lista encadeada e destroi cada n�
 * 2� Atribui NULL � lista
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
		printf("Custo: %.2f\n", lista->m.custo);
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
	switch (x)
	{
	case 0:
		m->tipo = Bicicleta;
		m->autonomia = ((m->bateria+20)*m->custo)/3;
		break;
	case 1:
		m->tipo = Carro;
		m->autonomia = ((m->bateria + 20) * m->custo) / 3;
		break;
	case 2:
		m->tipo = Trotinete;
		m->autonomia = ((m->bateria + 20) * m->custo) / 3;
		break;
	case 3:
		m->tipo = Autocarro;
		m->autonomia = ((m->bateria + 20) * m->custo) / 3;
		break;
	case 4:
		m->tipo = Outro;
		break;
	default:
		break;
	}
	printf("Localizacao: ");
	scanf("%s", m->localizacao);
	printf("Bateria: ");
	scanf("%d", &m->bateria);
	printf("Custo: ");
	scanf("%f", &m->custo);
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


#pragma endregion


