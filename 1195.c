/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1195
Data        : 25/11/2026
Objetivo    : Construir uma árvore binária de busca e imprimir os percursos prefixo, infixo e posfixo
Dificuldade : Fácil / Média (Implementação de BST e percursos clássicos em árvore)
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

void imprimir_prefixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->valor);
    *primeiro = 0;
    imprimir_prefixa(raiz->esq, primeiro);
    imprimir_prefixa(raiz->dir, primeiro);
}

void imprimir_infixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    imprimir_infixa(raiz->esq, primeiro);
    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->valor);
    *primeiro = 0;
    imprimir_infixa(raiz->dir, primeiro);
}

void imprimir_posfixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    imprimir_posfixa(raiz->esq, primeiro);
    imprimir_posfixa(raiz->dir, primeiro);
    if (!(*primeiro)) printf(" ");
    printf("%d", raiz->valor);
    *primeiro = 0;
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

    int primeiro;

    printf("Case %d:\n", numero_caso);

    printf("Pre.: ");
    primeiro = 1;
    imprimir_prefixa(raiz, &primeiro);
    printf("\n");

    printf("In..: ");
    primeiro = 1;
    imprimir_infixa(raiz, &primeiro);
    printf("\n");

    printf("Post: ");
    primeiro = 1;
    imprimir_posfixa(raiz, &primeiro);
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
