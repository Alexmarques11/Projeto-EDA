/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções Aluguer
 * 
 * \author Utilizador Alexandre Marques
 * \date   April 2023
 *********************************************************************/

#include "Aluguer.h"	

#include "Aluguer.h"	

 /**
  * Esta função lê os alugueres de um ficheiro txt e insere-os numa lista encadeada
  * 1º Lê os dados de cada aluguer e envia para a função adicionarAluguerLista que insere na lista encadeada
  * 2º Retorna 1 se o ficheiro foi lido com sucesso e 0 se não foi lido com sucesso
  *
  * \param listaAlugueres
  * \param filename
  * \return
  */
int lerAluguerestxt(AluguerLista** listaAlugueres, char* filename, Vertice* g, MeiosLista* mlista) {
    FILE* ficheiro = fopen(filename, "r");
    if (ficheiro == NULL) {
        return 0;
    }

    // Lê os dados de cada aluguer e insere na lista encadeada
    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        Aluguer novoAluguer;
        sscanf(linha, "%d;%[^;];%d;%[^;];%d", &novoAluguer.id, novoAluguer.nif, &novoAluguer.idMeio, novoAluguer.data, &novoAluguer.idDestino);
        novoAluguer.km = CalcularKm(g, mlista, novoAluguer.idMeio, novoAluguer);
        novoAluguer.preco = CalcularPreco(mlista, novoAluguer.idMeio, novoAluguer);
        *listaAlugueres = adicionarAluguerLista(*listaAlugueres, novoAluguer);
    }

    fclose(ficheiro);
    return 1;
}

/**
 * Esta função serve para calcular os km de um aluguer
 * 1º Procura o meio de transporte pelo ID
 * 2º Converte o nome da localização para ID
 * 3º Calcula a distância entre a localização do meio de transporte e o destino do aluguer
 * 4º Retorna a distância
 * 
 * \param g
 * \param mlista
 * \param idMeio
 * \param a
 * \return 
 */

int CalcularKm(Vertice* g, MeiosLista* mlista, int idMeio, Aluguer a) {

    Meios* m = procurarMeioPorId(mlista, idMeio);

    int i = ConverterNomeParaID(g, m->localizacao);


    return CalculaDistancia(g, i, a.idDestino);

}

/**
 * Esta função calcula o preço de um aluguer
 * 1º Procura o meio de transporte pelo ID
 * 2º Verifica o tipo de meio de transporte
 * 3º Calcula o preço por km
 * 
 * \param mlista
 * \param idMeio
 * \param a
 * \return 
 */

float CalcularPreco(MeiosLista* mlista, int idMeio, Aluguer a) {
    Meios* m = procurarMeioPorId(mlista, idMeio);

    if (a.km == 0) {
		return 1;
	}

    // Verifica o tipo de meio de transporte
    switch (m->tipo) {
    case Bicicleta:
        return a.km * 0.1; // Preço por km para bicicleta: 0.1
    case Carro:
        return a.km * 0.5; // Preço por km para carro: 0.5
    case Trotinete:
        return a.km * 0.2; // Preço por km para trotinete: 0.2
    case Autocarro:
        return a.km * 0.3; // Preço por km para autocarro: 0.3
    default:
        return a.km * 0.4; // Preço por km para outros meios de transporte: 0.4
    }
}

/**
 * Esta função adiciona um aluguer à lista encadeada
 * 1º Aloca memória para o novo aluguer
 * 2º Verifica se a lista está vazia ou se o novo aluguer tem o menor ID
 * 3º Encontra a posição correta para inserir o novo aluguer na lista ordenada
 * 4º Retorna a lista com o novo aluguer
 *
 * \param lista
 * \param a
 * \return
 */

AluguerLista* adicionarAluguerLista(AluguerLista* lista, Aluguer a) {
    AluguerLista* novo = (AluguerLista*)malloc(sizeof(AluguerLista));
    if (novo == NULL) return NULL;
    novo->a = a;
    novo->next = NULL;

    if (existeAluguer(lista, a)) return lista;


    // Verifica se a lista está vazia ou se o novo aluguer tem o menor ID
    if (lista == NULL || a.id < lista->a.id) {
        novo->next = lista;
        return novo;
    }

    // Encontra a posição correta para inserir o novo aluguer na lista ordenada
    AluguerLista* anterior = lista;
    AluguerLista* atual = lista->next;
    while (atual != NULL && atual->a.id < a.id) {
        anterior = atual;
        atual = atual->next;
    }

    novo->next = atual;
    anterior->next = novo;

    return lista;
}

/**
 * Esta função verifica se um aluguer existe na lista encadeada
 * 1º Percorre a lista encadeada e verifica se o ID do aluguer é igual ao ID do aluguer da lista
 * 2º Retorna true se o aluguer existe na lista e false se não existe
 *
 * \param lista
 * \param a
 * \return
 */

bool existeAluguer(AluguerLista* lista, Aluguer a) {
    AluguerLista* atual = lista;
    while (atual != NULL) {
        if (atual->a.id == a.id) {
            return true;
        }
        atual = atual->next;
    }
    return false;
}

/**
 * Esta função guarda os alugueres de uma lista encadeada num ficheiro binário
 * 1º Abre o ficheiro binário
 * 2º Percorre a lista encadeada e guarda os alugueres no ficheiro
 * 3º Fecha o ficheiro
 * 
 * \param listaAlugueres
 * \param nomeArquivo
 * \return 
 */

int guardarAlugueresBinario(AluguerLista* listaAlugueres, char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        return -1;
    }

    AluguerLista* atual = listaAlugueres;
    while (atual != NULL) {
        if (fwrite(&(atual->a), sizeof(Aluguer), 1, arquivo) != 1) {
            break;
        }
        atual = atual->next;
    }

    fclose(arquivo);
}

/**
 * Esta função carrega os alugueres de um ficheiro binário para uma lista encadeada
 * 1º Abre o ficheiro binário
 * 2º Lê os alugueres do ficheiro e adiciona-os à lista encadeada
 * 3º Retorna -1 se o ficheiro foi carregado com sucesso e -1 se não foi carregado com sucesso
 * 4º Fecha o ficheiro
 * 
 * \param listaAlugueres
 * \param nomeArquivo
 * \return 
 */

int carregarAlugueresBinario(AluguerLista** listaAlugueres, char* nomeArquivo) {
	FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
		return -1;
	}
	Aluguer a;
    while (fread(&a, sizeof(Aluguer), 1, arquivo) == 1) {
		*listaAlugueres = adicionarAluguerLista(*listaAlugueres, a);
		}
		fclose(arquivo);
		return 1;
}

/**
 * Esta função serve para destruir uma lista encadeada
 * 1º Percorre a lista encadeada e liberta a memória alocada para cada aluguer
 * 2º Libertar a memória alocada para a lista
 * 
 * \param listaAlugueres
 */

void destruirAluguerLista(AluguerLista* listaAlugueres) {
    AluguerLista* atual = listaAlugueres;
    while (atual != NULL) {
        AluguerLista* proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}


#pragma region Ecra

void imprimirAluguerLista(AluguerLista* lista) {
    if (lista == NULL) {
        printf("A lista de aluguers esta vazia.\n");
        return;
    }

    printf("Lista de Aluguers:\n");
    printf("ID |    NIF     | ID Meio | Data       | ID Destino | KM | Preco\n");
    printf("-----------------------------------------------------\n");

    AluguerLista* atual = lista;
    while (atual != NULL) {

        printf("%-2d | %-10s | %-7d | %-10s | %-11d | %-2d | %.2f\n",
            atual->a.id, atual->a.nif, atual->a.idMeio, atual->a.data,
            atual->a.idDestino, atual->a.km, atual->a.preco);
        atual = atual->next;
    }
}


#pragma endregion






