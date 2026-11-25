/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1200
Data        : 25/11/2026
Objetivo    : Executar inserção, busca e percursos (infixo, prefixo e posfixo) em uma ABP
Dificuldade : Média (Manipulação de ABP com caracteres e formatação exata de saída)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char chave;
    struct No* esq;
    struct No* dir;
} No;

No* criar_no(char chave) {
    No* novo = (No*)malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir_chave(No* raiz, char chave) {
    if (raiz == NULL) {
        return criar_no(chave);
    }
    if (chave < raiz->chave) {
        raiz->esq = inserir_chave(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = inserir_chave(raiz->dir, chave);
    }
    return raiz;
}

int buscar_chave(No* raiz, char chave) {
    if (raiz == NULL) {
        return 0;
    }
    if (chave == raiz->chave) {
        return 1;
    }
    if (chave < raiz->chave) {
        return buscar_chave(raiz->esq, chave);
    }
    return buscar_chave(raiz->dir, chave);
}

void imprimir_infixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    imprimir_infixa(raiz->esq, primeiro);
    if (!(*primeiro)) printf(" ");
    printf("%c", raiz->chave);
    *primeiro = 0;
    imprimir_infixa(raiz->dir, primeiro);
}

void imprimir_prefixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    if (!(*primeiro)) printf(" ");
    printf("%c", raiz->chave);
    *primeiro = 0;
    imprimir_prefixa(raiz->esq, primeiro);
    imprimir_prefixa(raiz->dir, primeiro);
}

void imprimir_posfixa(No* raiz, int* primeiro) {
    if (raiz == NULL) return;
    imprimir_posfixa(raiz->esq, primeiro);
    imprimir_posfixa(raiz->dir, primeiro);
    if (!(*primeiro)) printf(" ");
    printf("%c", raiz->chave);
    *primeiro = 0;
}

void liberar_arvore(No* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    char comando[20];
    char chave;
    No* raiz = NULL;

    while (scanf("%19s", comando) == 1) {
        if (strcmp(comando, "I") == 0) {
            if (scanf(" %c", &chave) == 1) {
                raiz = inserir_chave(raiz, chave);
            }
        } else if (strcmp(comando, "P") == 0) {
            if (scanf(" %c", &chave) == 1) {
                if (buscar_chave(raiz, chave)) {
                    printf("%c existe\n", chave);
                } else {
                    printf("%c nao existe\n", chave);
                }
            }
        } else if (strcmp(comando, "INFIXA") == 0) {
            int primeiro = 1;
            imprimir_infixa(raiz, &primeiro);
            printf("\n");
        } else if (strcmp(comando, "PREFIXA") == 0) {
            int primeiro = 1;
            imprimir_prefixa(raiz, &primeiro);
            printf("\n");
        } else if (strcmp(comando, "POSFIXA") == 0) {
            int primeiro = 1;
            imprimir_posfixa(raiz, &primeiro);
            printf("\n");
        }
    }

    liberar_arvore(raiz);
    return 0;
}
