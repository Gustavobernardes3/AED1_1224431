/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1110
Data        : 18/09/2026
Objetivo    : Tirar cartas do monte e colocar em outras posições
Dificuldade : Uso de listas encadeadas
Uso de IA   : Auxilio na logica do código
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

/* Estrutura do no e da Fila */
typedef struct no {
    int valor;
    struct no *prox;
} No;

typedef struct {
    No *inicio, *fim;
} Fila;

/* Insere no final da fila (Push) */
void push(Fila *f, int v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = v;
    novo->prox = NULL;
    
    if (!f->inicio) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

/* Remove do inicio da fila (Pop) */
int pop(Fila *f) {
    No *aux = f->inicio;
    int v = aux->valor;
    
    f->inicio = aux->prox;
    if (!f->inicio) f->fim = NULL;
    
    free(aux);
    return v;
}

int main() {
    int n;
    
    /* Le ate encontrar o 0 */
    while (scanf("%d", &n) && n != 0) {
        Fila f = {NULL, NULL};
        
        /* Preenche o monte inicial */
        for (int i = 1; i <= n; i++) {
            push(&f, i);
        }
        
        printf("Discarded cards:");
        int primeiro = 1;
        
        /* Enquanto houver mais de 1 carta (inicio diferente de fim) */
        while (f.inicio != f.fim) {
            if (!primeiro) printf(",");
            
            /* 1. Descarta o topo e imprime */
            printf(" %d", pop(&f));
            
            /* 2. Remove o novo topo e insere no final (rotacao) */
            push(&f, pop(&f));
            
            primeiro = 0;
        }
        
        /* A unica carta que sobrou */
        printf("\nRemaining card: %d\n", pop(&f));
    }
    
    return 0;
}
