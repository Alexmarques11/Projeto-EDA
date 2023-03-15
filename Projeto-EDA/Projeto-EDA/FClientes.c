/*****************************************************************//**
 * \file   FClientes.c
 * \brief  Fun��es clientes
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Clientes.h"
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define _CTR_SECURE_NO_WARNINGS
#include <stdbool.h>

/**
* \brief  Esta fun��o serve para mostrar todos os clientes que est�o guardados no ficheiro "clientes.bin"
 *
 * 1� Verifa se o ficheiro existe
 * 2� Se existir, mostra todos os clientes
 * 
 * @author Alexandre Marques
 */
Clientes* mostrarCLiente() {
	FILE* ficheiro;
	Clientes* cliente;
	// abrir o ficheiro para leitura bin�ria
	ficheiro = fopen("clientes.bin", "rb");
    if (ficheiro == NULL) {
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}
	// ler todos os clientes do ficheiro
    while ((cliente = lerClientes(ficheiro)) != NULL) {
		printf("NIF: %s\n", cliente->nif);
		printf("Nome: %s\n", cliente->nome);
		printf("Saldo: %.2f\n", cliente->saldo);
		printf("Morada: %s\n", cliente->morada);
		printf("\n");
		free(cliente);
	}
	fclose(ficheiro);
	return cliente;
}

/**
* \brief  Esta fun��o serve para ler os clientes do ficheiro "clientes.bin"
* 
 *1� Verifica se o ficheiro existe
 * 2� Se existir, l� os clientes
 * 
 * \param ficheiro
 * @author Alexandre Marques
 */
Clientes* lerClientes(FILE* ficheiro) {
    Clientes* cliente = malloc(sizeof(Clientes));
    if (fread(cliente, sizeof(Clientes), 1, ficheiro) == 0) {
        free(cliente);
        return NULL;
    }
    return cliente;
}

bool escreverCliente(Clientes* cliente, FILE* ficheiro) {
    fwrite(cliente, sizeof(Clientes), 1, ficheiro);
    return true;
}

/**
* \brief  Pede os dados ao utilizador para criar um novo cliente
 *
 */
Clientes* criarCliente() {
    Clientes* cliente = malloc(sizeof(Clientes));
    printf("Digite o NIF do cliente: ");
    scanf("%s", cliente->nif);
    fflush(stdin);
    printf("Digite o nome do cliente: ");
    scanf("%s", cliente->nome);
    fflush(stdin);
    printf("Digite o saldo do cliente: ");
    scanf("%f", &cliente->saldo);
    fflush(stdin);
    printf("Digite a morada do cliente: ");
    scanf("%s", cliente->morada);
    fflush(stdin);
    return cliente;
}

/**
* \brief
 *1� Abrir o ficheiro
 *2� Criar um cliente
 *3� Guardar o cliente
 *4� Fechar o ficheiro
 */
int adicionarCliente() {
    FILE* ficheiro;
    Clientes* cliente1;

    // abrir o ficheiro para escrita bin�ria
    ficheiro = fopen("clientes.bin", "ab");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    cliente1 = criarCliente();

    escreverCliente(cliente1, ficheiro);

    fclose(ficheiro);
    printf("O cliente foi guardado com sucesso");

    return 0;
}

/**
 * \brief  Ler todos os clientes do ficheiro "clientes.bin"
 *
 */
Clientes* listarClientes() {
    FILE* ficheiro;
    Clientes* cliente;

    // abrir o ficheiro para leitura bin�ria
    ficheiro = fopen("clientes.bin", "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // ler todos os clientes do ficheiro
    while ((cliente = lerClientes(ficheiro)) != NULL) {
        printf("NIF: %s\n", cliente->nif);
        printf("Nome: %s\n", cliente->nome);
        printf("Saldo: %.2f\n", cliente->saldo);
        printf("Morada: %s\n", cliente->morada);
        printf("\n");
        free(cliente);
    }

    fclose(ficheiro);

    return cliente;
}
