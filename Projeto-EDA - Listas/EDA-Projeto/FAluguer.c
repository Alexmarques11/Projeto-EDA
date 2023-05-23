/*****************************************************************//**
 * \file   Aluguer.c
 * \brief  Funções Aluguer
 * 
 * \author Utilizador Alexandre Marques
 * \date   April 2023
 *********************************************************************/

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
        *listaAlugueres = adicionarAluguerLista(*listaAlugueres, novoAluguer);
    }

    fclose(ficheiro);
    return 1;
}

int CalcularKm(Vertice* g, MeiosLista* mlista, int idMeio, Aluguer a) {

    Meios* m=procurarMeioPorId(mlista, idMeio);
    
    int i= ConverterNomeParaID(g, m->localizacao);

    
    return CalculaDistancia(g, i ,a.idDestino );

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

    if(existeAluguer(lista, a)) return lista;
    

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





