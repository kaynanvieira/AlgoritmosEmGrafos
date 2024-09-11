#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct No {
    int id;
    Aresta* arestas;
} No;

No grafo[MAX_NODES];
int ehPonderado = 0;
int ehDirecional = 0;

void adicionarAresta(int origem, int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = grafo[origem].arestas;
    grafo[origem].arestas = novaAresta;

    if (!ehDirecional) {
        novaAresta = (Aresta*)malloc(sizeof(Aresta));
        novaAresta->destino = origem;
        novaAresta->peso = peso;
        novaAresta->proxima = grafo[destino].arestas;
        grafo[destino].arestas = novaAresta;
    }
}

void imprimirGrafo(int numNos) {
    int i;
    for (i = 0; i < numNos; i++) {
        printf("No %d: ", i);
        Aresta* aresta = grafo[i].arestas;
        while (aresta != NULL) {
            if (ehPonderado) {
                printf("(%d: %d) ", aresta->destino, aresta->peso);
            } else {
                printf("-> %d ", aresta->destino);
            }
            aresta = aresta->proxima;
        }
        printf("\n");
    }
}

int main() {

    printf("Questao 1 \n\n");
    int numNos, origem, destino, peso, i;

    printf("Escolha o tipo de grafo:\n");
    printf("1. Grafo direcional nao ponderado\n");
    printf("2. Grafo nao direcional ponderado\n");
    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
        ehDirecional = 1;
        ehPonderado = 0;
    } else if (escolha == 2) {
        ehDirecional = 0;
        ehPonderado = 1;
    } else {
        printf("Escolha invalida!\n");
        return 1;
    }

    printf("Informe o numero de nos (maximo %d): ", MAX_NODES);
    scanf("%d", &numNos);

    if (numNos <= 0 || numNos > MAX_NODES) {
        printf("Numero de nos invalido!\n");
        return 1;
    }

    for (i = 0; i < numNos; i++) {
        grafo[i].id = i;
        grafo[i].arestas = NULL;
    }

    while (1) {
        printf("Informe a origem da aresta (ou -1 para sair): ");
        scanf("%d", &origem);
        if (origem == -1) break;
        if (origem < 0 || origem >= numNos) {
            printf("No de origem invalido!\n");
            continue;
        }

        printf("Informe o destino da aresta: ");
        scanf("%d", &destino);
        if (destino < 0 || destino >= numNos) {
            printf("No de destino invalido!\n");
            continue;
        }

        if (ehPonderado) {
            printf("Informe o peso da aresta: ");
            scanf("%d", &peso);
        } else {
            peso = 1;
        }

        adicionarAresta(origem, destino, peso);
    }

    imprimirGrafo(numNos);

    return 0;
}
