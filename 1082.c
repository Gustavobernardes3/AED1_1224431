/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1082
Data        : 25/11/2026
Objetivo    : Encontrar e imprimir os componentes conexos de um grafo não direcionado
Dificuldade : Média (DFS em grafos não direcionados e ordenação alfabética dos componentes)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

#define MAX_V 26

static void dfs(int u, int qtd_vertices, int adj[MAX_V][MAX_V],
                int visitado[MAX_V], int componente[MAX_V]) {
    visitado[u] = 1;
    componente[u] = 1;

    for (int v = 0; v < qtd_vertices; v++) {
        if (adj[u][v] && !visitado[v]) {
            dfs(v, qtd_vertices, adj, visitado, componente);
        }
    }
}

static void resolver_caso(int numero_caso) {
    int qtd_vertices, qtd_arestas;
    if (scanf("%d %d", &qtd_vertices, &qtd_arestas) != 2) {
        return;
    }

    int adj[MAX_V][MAX_V];
    int visitado[MAX_V];
    memset(adj, 0, sizeof(adj));
    memset(visitado, 0, sizeof(visitado));

    for (int i = 0; i < qtd_arestas; i++) {
        char c1, c2;
        scanf(" %c %c", &c1, &c2);
        int u = c1 - 'a';
        int v = c2 - 'a';
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int total_componentes = 0;

    printf("Case #%d:\n", numero_caso);

    for (int i = 0; i < qtd_vertices; i++) {
        if (!visitado[i]) {
            int componente[MAX_V];
            memset(componente, 0, sizeof(componente));

            dfs(i, qtd_vertices, adj, visitado, componente);
            total_componentes++;

            for (int v = 0; v < qtd_vertices; v++) {
                if (componente[v]) {
                    printf("%c,", (char)('a' + v));
                }
            }
            printf("\n");
        }
    }

    printf("%d connected components\n\n", total_componentes);
}

int main() {
    int casos;
    if (scanf("%d", &casos) == 1) {
        for (int c = 1; c <= casos; c++) {
            resolver_caso(c);
        }
    }
    return 0;
}
