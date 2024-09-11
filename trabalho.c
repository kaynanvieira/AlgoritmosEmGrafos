#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
No grafoTransposto[MAX_NODES];
int ponderado = 0;
int direcionado = 0;
bool visitado[MAX_NODES];
int descoberta[MAX_NODES], finalizacao[MAX_NODES], tempo = 0;
int ordemTopologica[MAX_NODES];
int indiceTopologico = 0;

void adicionarAresta(int origem, int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = grafo[origem].arestas;
    grafo[origem].arestas = novaAresta;

    if (!direcionado) {
        novaAresta = (Aresta*)malloc(sizeof(Aresta));
        novaAresta->destino = origem;
        novaAresta->peso = peso;
        novaAresta->proxima = grafo[destino].arestas;
        grafo[destino].arestas = novaAresta;
    } else {
        Aresta* transposta = (Aresta*)malloc(sizeof(Aresta));
        transposta->destino = origem;
        transposta->peso = peso;
        transposta->proxima = grafoTransposto[destino].arestas;
        grafoTransposto[destino].arestas = transposta;
    }
}

void DFS(int v) {
    visitado[v] = true;
    descoberta[v] = ++tempo;
    Aresta* aresta = grafo[v].arestas;

    while (aresta != NULL) {
        int u = aresta->destino;
        if (!visitado[u]) {
            DFS(u);
        }
        aresta = aresta->proxima;
    }
    finalizacao[v] = ++tempo;
    ordemTopologica[indiceTopologico++] = v;
}

void ordenacaoTopologica(int numNos) {
    for (int i = 0; i < numNos; i++) {
        visitado[i] = false;
    }
    indiceTopologico = 0;
    tempo = 0;

    for (int i = 0; i < numNos; i++) {
        if (!visitado[i]) {
            DFS(i);
        }
    }

    printf("Ordenação Topológica: ");
    for (int i = indiceTopologico - 1; i >= 0; i--) {
        printf("%d ", ordemTopologica[i]);
    }
    printf("\n");
}

void DFS_Transposto(int v) {
    visitado[v] = true;
    printf("%d ", v);
    Aresta* aresta = grafoTransposto[v].arestas;

    while (aresta != NULL) {
        int u = aresta->destino;
        if (!visitado[u]) {
            DFS_Transposto(u);
        }
        aresta = aresta->proxima;
    }
}

void encontrarComponentesFortementeConectados(int numNos) {
    for (int i = 0; i < numNos; i++) {
        visitado[i] = false;
    }
    indiceTopologico = 0;
    tempo = 0;
    for (int i = 0; i < numNos; i++) {
        if (!visitado[i]) {
            DFS(i);
        }
    }

    for (int i = 0; i < numNos; i++) {
        visitado[i] = false;
    }

    printf("Componentes fortemente conectados:\n");
    for (int i = indiceTopologico - 1; i >= 0; i--) {
        int v = ordemTopologica[i];
        if (!visitado[v]) {
            DFS_Transposto(v);
            printf("\n");
        }
    }
}

void imprimirGrafoTransposto(int numNos) {
    printf("Grafo Transposto:\n");
    for (int i = 0; i < numNos; i++) {
        printf("Nó %d: ", i);
        Aresta* aresta = grafoTransposto[i].arestas;
        while (aresta != NULL) {
            printf("-> %d ", aresta->destino);
            aresta = aresta->proxima;
        }
        printf("\n");
    }
}

int main() {
    int numNos, origem, destino, peso, i, escolha;

    printf("Escolha o tipo de grafo:\n");
    printf("1. Grafo direcional não ponderado\n");
    printf("2. Grafo não direcional ponderado\n");
    scanf("%d", &escolha);

    if (escolha == 1) {
        direcionado = 1;
        ponderado = 0;
    } else if (escolha == 2) {
        direcionado = 0;
        ponderado = 1;
    } else {
        printf("Escolha inválida!\n");
        return 1;
    }

    printf("Informe o número de nós (máximo %d): ", MAX_NODES);
    scanf("%d", &numNos);

    if (numNos <= 0 || numNos > MAX_NODES) {
        printf("Número de nós inválido!\n");
        return 1;
    }

    for (i = 0; i < numNos; i++) {
        grafo[i].id = i;
        grafo[i].arestas = NULL;
        grafoTransposto[i].id = i;
        grafoTransposto[i].arestas = NULL;
    }

    while (1) {
        printf("Informe a origem da aresta (ou -1 para sair): ");
        scanf("%d", &origem);
        if (origem == -1) break;
        if (origem < 0 || origem >= numNos) {
            printf("Nó de origem inválido!\n");
            continue;
        }

        printf("Informe o destino da aresta: ");
        scanf("%d", &destino);
        if (destino < 0 || destino >= numNos) {
            printf("Nó de destino inválido!\n");
            continue;
        }

        if (ponderado) {
            printf("Informe o peso da aresta: ");
            scanf("%d", &peso);
        } else {
            peso = 1;
        }

        adicionarAresta(origem, destino, peso);
    }

    ordenacaoTopologica(numNos);

    encontrarComponentesFortementeConectados(numNos);

    imprimirGrafoTransposto(numNos);

    return 0;
}
