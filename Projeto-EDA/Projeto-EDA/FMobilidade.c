/*****************************************************************//**
 * \file   FMobilidade.c
 * \brief  Fun��es dos meios de mobilidade
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Mobilidade.h"	
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS
#include <stdbool.h>

 /**
 * \brief  Esta fun��o serve para mostrar todos os meios de mobilidade que est�o guardados no ficheiro "mobilidade.bin"
  *
  * 1� Verifa se o ficheiro existe
  * 2� Se existir, mostra todos os meios de mobilidade
  *
  * @author Alexandre Marques
  */

Mobilidade* mostrarMeios() {
	FILE* ficheiro;
	Mobilidade* meio;

	ficheiro = fopen("mobilidade.bin", "rb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}

	while ((meio = lerMeios(ficheiro)) != NULL) {
		printf("ID: %d\n", meio->id);
		printf("Tipo de meio: %s\n", meio->tipo);
		printf("Pre�o: %d\n", meio->custo);
		printf("Localizacao: %d\n", meio->localizacao);
		printf("Bateria: %d\n", meio->bateria);
		printf("Status: %d\n", meio->status);

		free(meio);
	}
	fclose(ficheiro);
	return meio;
}

/**
* \brief  Esta fun��o serve para ler os meios de mobilidade do ficheiro "mobilidade.bin"
*
 *1� Verifica se o ficheiro existe
 * 2� Se existir, l� os meios de mobilidade
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Mobilidade* lerMeios(FILE* ficheiro) {
	Mobilidade* meio = malloc(sizeof(Mobilidade));
	if (fread(meio, sizeof(Mobilidade), 1, ficheiro) == 0) {
		return NULL;
	}
	return meio;
}

/**
* \brief  Esta fun��o serve para escrever os gestores no ficheiro "mobilidade.bin"
 *
 * 1� Verifica se o ficheiro existe
 * 2� Se existir, escreve os meios de mobilidade
 *
 * \param meio
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverMeios(Mobilidade* meio, FILE* ficheiro) {
	fwrite(meio, sizeof(Mobilidade), 1, ficheiro);
	return true;
}

/**
* \brief  Esta fun��o serve para criar um meios de mobilidade
* 1� Pede os  dados do meios de mobilidade
 *
 * @author Alexandre Marques
 */
Mobilidade* criarMeio() {
	Mobilidade* meio = malloc(sizeof(Mobilidade));
	printf("ID: ");
	scanf("%d", &meio->id);
	printf("Tipo de meio: ");
	scanf("%s", meio->tipo);
	printf("Preco: ");
	scanf("%d", &meio->custo);
	printf("Localizacao: ");
	scanf("%s", &meio->localizacao);
	printf("Bateria: ");
	scanf("%d", &meio->bateria);
	meio->status = true;
	return meio;
}

/**
* \brief
 *1� Verifica se o ficheiro existe
 * 2� Se existir, cria um meios de mobilidade
 * 3� Escreve o meios de mobilidade no ficheiro
 *
 * @author Alexandre Marques
 */
int adicionarMeio() {
	FILE* ficheiro;
	Mobilidade* meio;

	ficheiro = fopen("mobilidade.bin", "ab");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}

	meio = criarMeio();

	escreverMeios(meio, ficheiro);

	fclose(ficheiro);

	free(meio);

	printf("O gestor foi guardado com sucesso\n");

	return 0;
}

