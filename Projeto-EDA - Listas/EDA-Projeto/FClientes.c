/*****************************************************************//**
 * \file   FClientes.c
 * \brief  Fun��es clientes
 *
 * \author Alexandre Marques
 * \date   March 2023
 *********************************************************************/

#include "Clientes.h"

/**
* \brief  Fun��o para ler os dados dos clientes do ficheiro txt
* 1�  L� os dados de cada cliente e envia para a fun��o adicionarClietneLista que insere na lista encadeada
 *2� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 * \param listaClientes
 * @author Alexandre Marques
 */

int lerClientestxt(ClientesLista** listaClientes) {
    FILE* ficheiro = fopen("Clientes.txt", "r");
    if (ficheiro == NULL) {
        return 0;
    }

    // L� os dados de cada cliente e insere na lista encadeada
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        Clientes novoCliente;
        sscanf(linha, "%[^;];%[^;];%[^;];%f", novoCliente.nome, novoCliente.nif, novoCliente.morada, &novoCliente.saldo);
        *listaClientes = adicionarClienteLista(*listaClientes, novoCliente);
    }

    fclose(ficheiro);
    return 1;
}

/**
* \brief  Insere Clientes no incio de uma lista encadeada   
 *1� Cria um novo n� com os dados do cliente
 * 2� Insere o novo n� no inicio da lista
 * 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 * \param recebe uma lista e um cliente para o inserir na lista
 * @author Alexandre Marques
 */

ClientesLista* adicionarClienteLista(ClientesLista* lista, Clientes c) {
    ClientesLista* novo = (ClientesLista*)malloc(sizeof(ClientesLista));
    if (novo == NULL) return NULL;
    novo->c = c;
    novo->next = NULL;

    // Verifica se a lista est� vazia ou se o novo cliente tem o menor NIF
    if (lista == NULL || strcmp(c.nif, lista->c.nif) < 0) {
        novo->next = lista;
        return novo;
    }

    // Encontra a posi��o correta para inserir o novo cliente na lista ordenada
    ClientesLista* anterior = lista;
    ClientesLista* atual = lista->next;
    while (atual != NULL && strcmp(c.nif, atual->c.nif) >= 0) {
        anterior = atual;
        atual = atual->next;
    }

    novo->next = atual;
    anterior->next = novo;

    return lista;
}

/**
* \brief  Esta fun��o guarda a lista de clientes no ficheiro bin�rio
* 1� Abre o ficheiro bin�rio para escrita
* 2� Percorre a lista encadeada e guarda os dados de cada cliente no ficheiro
* 3� Fecha o ficheiro
 * \param lista
 * @author Alexandre Marques
 */

bool guardarClientesbin(ClientesLista* lista) {
    FILE* ficheiro = fopen("Clientes.bin", "ab");
    if (ficheiro == NULL) {
        return false;
    }

    while (lista != NULL) {
        fwrite(&lista->c, sizeof(Clientes), 1, ficheiro);
        lista = lista->next;
    }

    fclose(ficheiro);
    return true;
}


/**
* \brief  Esta fun��o adiciona um novo cliente � lista de clientes
* 1� Cria um novo cliente com os dados inseridos pelo usu�rio
* 2� Adiciona o novo cliente � lista chamando a fun��o adicionarClienteLista
* 3� Guarda a lista atualizada no ficheiro bin�rio chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * @author Alexandre Marques
 */

bool adicionarNovoCliente(ClientesLista** listaClientes) {
    // Cria um novo cliente com os dados inseridos pelo usu�rio
    Clientes novoCliente;
    obterDadosClienteEcra(&novoCliente);

    // Adiciona o novo cliente � lista
    *listaClientes = adicionarClienteLista(*listaClientes, novoCliente);

    // Guarda a lista atualizada no arquivo bin�rio
    guardarClientesbin(*listaClientes);

    return true;
}

/**
* \brief  Esta fun��o l� os dados dos clientes do ficheiro bin�rio
* 1� Abre o ficheiro bin�rio para leitura
* 2� L� os dados de cada cliente e insere na lista encadeada chamando a fun��o adicionarClienteLista
* 3� Fecha o ficheiro
 *
 * \param listaClientes
 * @author Alexandre Marques
 */

ClientesLista* lerClientesbin(ClientesLista** listaClientes, char* fileName) {
	FILE* ficheiro = fopen("Clientes.bin", "rb");
    if (ficheiro == NULL) {
		return 0;
	}
	// L� os dados de cada cliente e insere na lista encadeada
	Clientes novoCliente;
    while (fread(&novoCliente, sizeof(Clientes), 1, ficheiro) != 0) {
		*listaClientes = adicionarClienteLista(*listaClientes, novoCliente);
		}
			fclose(ficheiro);
		 	return listaClientes;
}

/**
* \brief  Esta fun��o remove um cliente da lista de clientes
* 1� Procura pelo cliente com o NIF correspondente na lista encadeada
* 2� Remove o cliente da lista encadeada
* 3� Atualiza o arquivo bin�rio com a lista atualizada chamando a fun��o guardarClientesbin
 *
 * \param listaClientes
 * \param nif
 * @author Alexandre Marques
 */

bool removerCliente(ClientesLista** listaClientes, char nif[]) {
    ClientesLista* clienteAtual = *listaClientes;
    ClientesLista* clienteAnterior = NULL;
    bool encontrado = false;
    // Procura pelo cliente com o NIF correspondente na lista encadeada
    while (clienteAtual != NULL) {
        if (strcmp(clienteAtual->c.nif, nif) == 0) {
            encontrado = true;
            break;
        }
        clienteAnterior = clienteAtual;
        clienteAtual = clienteAtual->next;
    }
    if (!encontrado) {

        return false;
    }
    // Remove o cliente da lista encadeada
    if (clienteAnterior == NULL) {
        *listaClientes = clienteAtual->next;
    }
    else {
        clienteAnterior->next = clienteAtual->next;
    }
    // Atualiza o arquivo bin�rio com a lista atualizada
    free(clienteAtual);
    guardarClientesbin(*listaClientes);

    return true;
}

Clientes* obterClientePorNIF(ClientesLista* lista, char* nif) {
    ClientesLista* atual = lista;

    while (atual != NULL && strcmp(atual->c.nif, nif) <= 0) {
        if (strcmp(atual->c.nif, nif) == 0) {
            return &(atual->c);
        }
        atual = atual->next;
    }

    return NULL;
}

#pragma region Ecra

Clientes* obterDadosClienteEcra(Clientes* c) {
    printf("Nome: ");
    scanf("%s", c->nome);
    printf("NIF: ");
    scanf("%s", c->nif);
    printf("Morada: ");
    scanf("%s", c->morada);
    printf("Saldo: ");
    scanf("%f", &c->saldo);
    return c;
}

void mostrarClientes(ClientesLista* lista) {
    printf("Lista de clientes:\n\n");
    while (lista != NULL) {
        printf("Nome: %s\n", lista->c.nome);
        printf("NIF: %s\n", lista->c.nif);
        printf("Morada: %s\n", lista->c.morada);
        printf("Saldo: %.2f\n", lista->c.saldo);
        printf("\n");
        lista = lista->next;
    }
}

void clienteRemovidoEcra(ClientesLista** listaClientes) {
    char nif[10];
    printf("NIF do cliente a remover: ");
    scanf("%s", nif);
    removerCliente(&listaClientes, nif);

}

#pragma endregion
