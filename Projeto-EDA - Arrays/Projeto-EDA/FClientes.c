/*****************************************************************//**
 * \file   FClientes.c
 * \brief  Funções clientes
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
 * \brief  Esta função serve para mostrar todos os clientes que estão guardados no ficheiro "clientes.bin"
  *
  * 1º Verifa se o ficheiro existe
  * 2º Se existir, mostra todos os clientes
  *
  * @author Alexandre Marques
  */
Clientes* mostrarCLiente() {
    FILE* ficheiro;
    Clientes* cliente;
    // abrir o ficheiro para leitura binária
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
* \brief  Esta função serve para ler os clientes do ficheiro "clientes.bin"
*
 *1º Verifica se o ficheiro existe
 * 2º Se existir, lê os clientes
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

/**
* \brief  Esta função serve para escrever os clientes no ficheiro "clientes.bin"
 *
 * 1º Verifica se o ficheiro existe
 * 2º Se existir, escreve os clientes
 *
 * \param cliente
 * \param ficheiro
 * @author Alexandre Marques
 */
bool escreverCliente(Clientes* cliente, FILE* ficheiro) {
    fwrite(cliente, sizeof(Clientes), 1, ficheiro);
    return true;
}

/**
* \brief  Esta função serve para criar um cliente
* 1º Pede os  dados do cliente
 *
 * @author Alexandre Marques
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
 *1º Abrir o ficheiro
 *2º Criar um cliente
 *3º Guardar o cliente
 *4º Fechar o ficheiro
 */
int adicionarCliente() {
    FILE* ficheiro;
    Clientes* cliente1;

    // abrir o ficheiro para escrita binária
    ficheiro = fopen("clientes.bin", "ab");
    if (ficheiro == NULL) {
        return 0;
    }

    cliente1 = criarCliente();

    escreverCliente(cliente1, ficheiro);

    fclose(ficheiro);

    return 1;
}

Clientes* alterarCliente() {
    FILE* ficheiro;
    Clientes* cliente;
    char nif[10];
    int opcao;

    // abrir o ficheiro para leitura e escrita binária
    ficheiro = fopen("clientes.bin", "rb+");  //leitura e escrita do ficheiro binario, apontado assim para o inicio do arquivo
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }

    printf("Digite o NIF do cliente que pretende modificar: ");
    scanf("%s", nif);

    while ((cliente = lerClientes(ficheiro)) != NULL) {
        if (strcmp(cliente->nif, nif) == 0) {

            printf("NIF: %s\n", cliente->nif);
            printf("Nome: %s\n", cliente->nome);
            printf("Saldo: %.2f\n", cliente->saldo);
            printf("Morada: %s\n", cliente->morada);
            printf("\n");

            printf("Qual dos dados pretende modificar?\n");
            printf("1 - NIF\n");
            printf("2 - Nome\n");
            printf("3 - Saldo\n");
            printf("4 - Morada\n");
            printf("5 - Sair\n");
            printf("Opcao:");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Introduz o Nif do cliente: ");
                scanf("%s", cliente->nif);
                break;
            case 2:
                printf("Introduz o nome do cliente: ");
                scanf("%s", cliente->nome);
                break;
            case 3:
                printf("Introduz o saldo do cliente: ");
                scanf("%f", &cliente->saldo);
                break;
            case 4:
                printf("Introduz a morada do cliente: ");
                scanf("%s", cliente->morada);
                break;
            default:
                break;
            }

            printf("NIF: %s\n", cliente->nif);
            printf("Nome: %s\n", cliente->nome);
            printf("Saldo: %.2f\n", cliente->saldo);
            printf("Morada: %s\n", cliente->morada);
            printf("\n");

            // reposicionar o ponteiro no ficheiro para a posição correta
            fseek(ficheiro, -(long)sizeof(Clientes), SEEK_CUR);
            // escrever o cliente atualizado no ficheiro
            escreverCliente(cliente, ficheiro);

            free(cliente);
            break;
        }
        free(cliente);
    }

    fclose(ficheiro);

    return NULL;
}


/*void removerCliente(char* nif) {
    FILE* ficheiro;
    Clientes* cliente;
    Clientes* anterior = NULL;

    // Abrir o ficheiro para leitura e escrita binária
    ficheiro = fopen("clientes.bin", "rb+");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // Percorre a lista até encontrar o cliente com o NIF correspondente
    while ((cliente = lerClientes(ficheiro)) != NULL) {
        if (strcmp(cliente->nif, nif) == 0) {
            // Remove o cliente da estrutura
            if (anterior == NULL) {
                fseek(ficheiro, 0, SEEK_SET); // Posiciona o ponteiro no início do ficheiro
                fwrite(cliente->proximo, sizeof(Clientes), 1, ficheiro);
            }
            else {
                fseek(ficheiro, -(long)(sizeof(Clientes) * 2), SEEK_CUR); // Volta para o início do cliente anterior
                fwrite(cliente->proximo, sizeof(Clientes), 1, ficheiro);
            }

            free(cliente); // Libera o espaço de memória alocado para o cliente removido
            printf("Cliente com NIF %s removido com sucesso.\n", nif);
            fclose(ficheiro);
            return;
        }
        anterior = cliente;
    }

    // Caso o cliente não seja encontrado
    printf("Cliente com NIF %s nao encontrado.\n", nif);
    fclose(ficheiro);
}

bool eliminarCliente() {
    char nif[10];

    printf("Introduza o nif do cliente que deseja eliminar: ");
    scanf("%s", nif);
    printf("\n");

    removerCliente(nif);

    return true;
}*/

