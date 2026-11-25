/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1076
Data        : 25/11/2026
Objetivo    : Calcular o número mínimo de movimentos para desenhar o labirinto
Dificuldade : Média (Modelagem em grafos e contagem de arestas únicas)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

#define MAX_V 105

static void resolver_caso() {
    int inicio, qtd_vertices, qtd_linhas;
    if (scanf("%d", &inicio) != 1) {
        return;
    }
    if (scanf("%d %d", &qtd_vertices, &qtd_linhas) != 2) {
        return;
    }

    int adj[MAX_V][MAX_V];
    memset(adj, 0, sizeof(adj));

    int arestas_unicas = 0;

    for (int i = 0; i < qtd_linhas; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u != v && !adj[u][v]) {
            adj[u][v] = 1;
            adj[v][u] = 1;
            arestas_unicas++;
        }
    }

    printf("%d\n", 2 * arestas_unicas);
}

int main() {
    int casos;
    if (scanf("%d", &casos) == 1) {
        while (casos--) {
            resolver_caso();
        }
    }
    return 0;
}
