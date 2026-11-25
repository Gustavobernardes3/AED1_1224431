/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1123
Data        : 25/11/2026
Objetivo    : Calcular o menor custo até o destino respeitando a rota de serviço
Dificuldade : Média (Algoritmo de Dijkstra com restrição de transições na rota)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
    int destino;
    int custo;
    struct Aresta* proximo;
} Aresta;

typedef struct {
    int vertice;
    int dist;
} NoHeap;

static void adicionar_aresta(Aresta** cabeca, int origem, int destino, int custo) {
    Aresta* nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->custo = custo;
    nova->proximo = cabeca[origem];
    cabeca[origem] = nova;
}

static void heap_push(NoHeap* heap, int* tamanho, int vertice, int dist) {
    int idx = (*tamanho)++;
    heap[idx].vertice = vertice;
    heap[idx].dist = dist;

    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (heap[pai].dist <= heap[idx].dist) {
            break;
        }
        NoHeap temp = heap[pai];
        heap[pai] = heap[idx];
        heap[idx] = temp;
        idx = pai;
    }
}

static NoHeap heap_pop(NoHeap* heap, int* tamanho) {
    NoHeap topo = heap[0];
    (*tamanho)--;

    if (*tamanho > 0) {
        heap[0] = heap[*tamanho];
        int idx = 0;

        while (1) {
            int esq = 2 * idx + 1;
            int dir = 2 * idx + 2;
            int menor = idx;

            if (esq < *tamanho && heap[esq].dist < heap[menor].dist) {
                menor = esq;
            }
            if (dir < *tamanho && heap[dir].dist < heap[menor].dist) {
                menor = dir;
            }
            if (menor == idx) {
                break;
            }

            NoHeap temp = heap[idx];
            heap[idx] = heap[menor];
            heap[menor] = temp;
            idx = menor;
        }
    }

    return topo;
}

static int dijkstra(Aresta** cabeca, int qtd_cidades, int rota_tam, int inicio) {
    int destino_final = rota_tam - 1;
    int* dist = (int*)malloc((size_t)qtd_cidades * sizeof(int));
    for (int i = 0; i < qtd_cidades; i++) {
        dist[i] = INT_MAX;
    }

    int capacidade_heap = qtd_cidades * 4 + 5;
    NoHeap* heap = (NoHeap*)malloc((size_t)capacidade_heap * sizeof(NoHeap));
    int tam_heap = 0;

    dist[inicio] = 0;
    heap_push(heap, &tam_heap, inicio, 0);

    while (tam_heap > 0) {
        NoHeap atual = heap_pop(heap, &tam_heap);
        int u = atual.vertice;
        int d = atual.dist;

        if (d > dist[u]) {
            continue;
        }
        if (u == destino_final) {
            break;
        }

        for (Aresta* aresta = cabeca[u]; aresta != NULL; aresta = aresta->proximo) {
            int v = aresta->destino;

            if (u < destino_final && v != u + 1) {
                continue;
            }

            if (dist[u] != INT_MAX && dist[u] + aresta->custo < dist[v]) {
                dist[v] = dist[u] + aresta->custo;
                heap_push(heap, &tam_heap, v, dist[v]);
            }
        }
    }

    int resposta = dist[destino_final];
    free(dist);
    free(heap);
    return resposta;
}

static void liberar_grafo(Aresta** cabeca, int qtd_cidades) {
    for (int i = 0; i < qtd_cidades; i++) {
        Aresta* atual = cabeca[i];
        while (atual != NULL) {
            Aresta* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(cabeca);
}

int main() {
    int n, m, c, k;

    while (scanf("%d %d %d %d", &n, &m, &c, &k) == 4) {
        if (n == 0 && m == 0 && c == 0 && k == 0) {
            break;
        }

        Aresta** cabeca = (Aresta**)calloc((size_t)n, sizeof(Aresta*));

        for (int i = 0; i < m; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);
            adicionar_aresta(cabeca, u, v, p);
            adicionar_aresta(cabeca, v, u, p);
        }

        int menor_custo = dijkstra(cabeca, n, c, k);
        printf("%d\n", menor_custo);

        liberar_grafo(cabeca, n);
    }

    return 0;
}
