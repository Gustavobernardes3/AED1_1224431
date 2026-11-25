/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1466
Data        : 25/11/2026
Objetivo    : Construir uma árvore binária de busca e imprimir seus nós por nível usando BFS
Dificuldade : Média (Construção de ABB e percurso em largura com fila)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir_no(No* raiz, int valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserir_no(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir_no(raiz->dir, valor);
    }
    return raiz;
}

void imprimir_por_nivel(No* raiz, int total_nos) {
    if (raiz == NULL || total_nos <= 0) return;

    No** fila = (No**)malloc((size_t)total_nos * sizeof(No*));
    int inicio = 0;
    int fim = 0;
    int primeiro = 1;

    fila[fim++] = raiz;

    while (inicio < fim) {
        No* atual = fila[inicio++];

        if (!primeiro) {
            printf(" ");
        }
        printf("%d", atual->valor);
        primeiro = 0;

        if (atual->esq != NULL) {
            fila[fim++] = atual->esq;
        }
        if (atual->dir != NULL) {
            fila[fim++] = atual->dir;
        }
    }

    free(fila);
}

void liberar_arvore(No* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

void resolver_caso(int numero_caso) {
    int qtd_nos, valor;
    if (scanf("%d", &qtd_nos) != 1) return;

    No* raiz = NULL;
    for (int i = 0; i < qtd_nos; i++) {
        scanf("%d", &valor);
        raiz = inserir_no(raiz, valor);
    }

    printf("Case %d:\n", numero_caso);
    imprimir_por_nivel(raiz, qtd_nos);
    printf("\n\n");

    liberar_arvore(raiz);
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
