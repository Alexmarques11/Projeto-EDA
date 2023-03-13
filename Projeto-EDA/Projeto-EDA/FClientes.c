/*****************************************************************//**
 * \file   FClientes.c
 * \brief  Funções clientes
 * 
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#pragma warning (disable: 4996)
#include "Clientes.h"
#define _CTR_SECURE_NO_WARNINGS

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
 * @author Alexandre Marques
 */
Clientes* criarCliente() {
	Clientes* cliente = malloc(sizeof(Clientes));
	printf("Digite o NIF do cliente: ");
	scanf("%s", cliente->nif);
	printf("Digite o nome do cliente: ");
	scanf("%s", cliente->nome);
	printf("Digite o saldo do cliente: ");
	scanf("%f", &cliente->saldo);
	printf("Digite a morada do cliente: ");
	scanf("%s", cliente->morada);
	return cliente;
}

/**
* \brief  
 *1º Abrir o ficheiro
 *2º Criar um cliente
 *3º Guardar o cliente
 * @author Alexandre Marques
 */
int adicionarCliente() {
    FILE* ficheiro;
    Clientes* cliente1;

    // abrir o ficheiro para escrita binária
    ficheiro = fopen("clientes.bin", "wb");
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

/*abrir o ficheiro para leitura binária
    ficheiro = fopen("clientes.bin", "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    // ler os clientes do ficheiro
    cliente1 = lerClientes(ficheiro);

    // imprimir os clientes lidos
    printf("Cliente 1: %s, %.2f\n", cliente1->nome, cliente1->saldo);

    fclose(ficheiro); // fechar o ficheiro

    return 0;
}
*/



