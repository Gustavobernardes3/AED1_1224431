/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1610
Data        : 18/11/2026
Objetivo    : Detectar ciclos (dependências circulares) em um grafo direcionado usando DFS
Dificuldade : Média (Requer Busca em Profundidade com controle de estados)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

// Estrutura para os nós da lista de adjacência
typedef struct No {
    int destino;
    struct No* proximo;
} No;

// Estrutura do Grafo
typedef struct {
    No** cabeca;
    int* estado; // 0: não visitado, 1: visitando (na pilha), 2: visitado (concluído)
    int tem_ciclo;
} Grafo;

// Função para adicionar uma aresta direcionada
void adicionar_aresta(Grafo* g, int origem, int destino) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->destino = destino;
    novo_no->proximo = g->cabeca[origem];
    g->cabeca[origem] = novo_no;
}

// Busca em Profundidade (DFS) para detecção de ciclos
void dfs(Grafo* g, int u) {
    g->estado[u] = 1; // Marca como "visitando" no caminho atual
    
    No* atual = g->cabeca[u];
    while (atual != NULL) {
        int v = atual->destino;
        
        if (g->estado[v] == 1) {
            g->tem_ciclo = 1; // Encontrou um ciclo (back-edge)
            return;
        } else if (g->estado[v] == 0) {
            dfs(g, v);
            if (g->tem_ciclo) return;
        }
        
        atual = atual->proximo;
    }
    
    g->estado[u] = 2; // Marca como totalmente processado
}

// Função para resolver cada caso de teste
void resolver() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;

    Grafo g;
    g.cabeca = (No**)calloc(n + 1, sizeof(No*));
    g.estado = (int*)calloc(n + 1, sizeof(int));
    g.tem_ciclo = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adicionar_aresta(&g, u, v);
    }

    // Varre todos os vértices para garantir que componentes desconexas sejam visitadas
    for (int i = 1; i <= n; i++) {
        if (g.estado[i] == 0) {
            dfs(&g, i);
            if (g.tem_ciclo) break;
        }
    }

    if (g.tem_ciclo) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

    // Liberação correta da memória alocada dinamicamente
    for (int i = 1; i <= n; i++) {
        No* atual = g.cabeca[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g.cabeca);
    free(g.estado);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            resolver();
        }
    }
    return 0;
}
