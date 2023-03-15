/*****************************************************************//**
 * \file   FGestores.c
 * \brief  Fun��es Gestores
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/


#include "Gestores.h"	
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS
#include <stdbool.h>

 /**
 * \brief  Esta fun��o serve para mostrar todos os gestores que est�o guardados no ficheiro "gestores.bin"
  *
  * 1� Verifa se o ficheiro existe
  * 2� Se existir, mostra todos os gestores
  *
  * @author Alexandre Marques
  */
Gestores* mostrarGestores() {
	FILE* ficheiro;
	Gestores* gestor;

	ficheiro = fopen("gestores.bin", "rb");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}

	while ((gestor = lerGestores(ficheiro)) != NULL) {
		printf("ID: %d\n", gestor->id);
		printf("Nome: %s\n", gestor->nome);
		printf("Email: %s\n\n", gestor->email);
		free(gestor);
	}
	fclose(ficheiro);
	return gestor;
}

/**
* \brief  Esta fun��o serve para ler os gestores do ficheiro "gestores.bin"
*
 *1� Verifica se o ficheiro existe
 * 2� Se existir, l� os gestores
 *
 * \param ficheiro
 * @author Alexandre Marques
 */

Gestores* lerGestores(FILE* ficheiro) {
	Gestores* gestor = malloc(sizeof(Gestores));
	if (fread(gestor, sizeof(Gestores), 1, ficheiro) == 0) {
		return NULL;
	}
	return gestor;
}

/**
* \brief  Esta fun��o serve para escrever os gestores no ficheiro "gestores.bin"
 *
 * 1� Verifica se o ficheiro existe
 * 2� Se existir, escreve os gestores
 *
 * \param gestor
 * \param ficheiro
 * @author Alexandre Marques
 */

bool escreverGestores(Gestores* gestor, FILE* ficheiro) {
	fwrite(gestor, sizeof(Gestores), 1, ficheiro);
	return true;
}

/**
* \brief  Esta fun��o serve para criar um gestor
* 1� Pede os  dados do gestor
 *
 * @author Alexandre Marques
 */
Gestores* criarGestor() {
	Gestores* gestor = malloc(sizeof(Gestores));
	printf("ID: ");
	scanf("%d", &gestor->id);
	printf("Nome: ");
	scanf("%s", gestor->nome);
	printf("Email: ");
	scanf("%s", gestor->email);
	printf("Password: ");
	scanf("%s", gestor->password);
	return gestor;
}	

/**
* \brief  
 *1� Verifica se o ficheiro existe
 * 2� Se existir, cria um gestor
 * 3� Escreve o gestor no ficheiro
 * 
 * @author Alexandre Marques
 */
int adicionarGestor() {
	FILE* ficheiro;
	Gestores* gestor;

	ficheiro = fopen("gestores.bin", "ab");
	if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}
	

	
	gestor = criarGestor();
	


	escreverGestores(gestor, ficheiro);

	fclose(ficheiro);

	free(gestor);

	printf("O gestor foi guardado com sucesso\n");

	return 0;
}	
