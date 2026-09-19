/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1068
Data        : 18/09/2026
Objetivo    : verificar se os parênteses de uma expressão matemática estão corretamente balanceados
Dificuldade : alocação dinamica
Uso de IA   : ajuda para entender a lógica
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

/* Estrutura do no da Pilha */
typedef struct no {
    char c;
    struct no *prox;
} No;

/* Insere no topo da pilha (Push) */
void push(No **topo, char c) {
    No *novo = (No *)malloc(sizeof(No));
    novo->c = c;
    novo->prox = *topo;
    *topo = novo;
}

/* Remove do topo da pilha (Pop). Retorna 1 (sucesso) ou 0 (pilha vazia) */
int pop(No **topo) {
    if (*topo == NULL) return 0;
    
    No *aux = *topo;
    *topo = aux->prox;
    
    free(aux);
    return 1;
}

/* Libera a memoria restante da pilha caso a expressao seja invalida */
void limpar_pilha(No **topo) {
    No *aux;
    while (*topo != NULL) {
        aux = *topo;
        *topo = (*topo)->prox;
        free(aux);
    }
}

int main() {
    /* Vetor para armazenar a expressao matematica (max 1000 caracteres) */
    char expressao[1005];

    /* Le a linha inteira ate o \n (incluindo espacos) ate encontrar o EOF */
    while (scanf(" %[^\n]", expressao) != EOF) {
        No *topo = NULL;
        int correto = 1;

        /* Percorre os caracteres da expressao */
        for (int i = 0; expressao[i] != '\0'; i++) {
            
            if (expressao[i] == '(') {
                push(&topo, '(');
            } 
            else if (expressao[i] == ')') {
                /* Tenta desempilhar. Se nao houver '(', a expressao é invalida */
                if (!pop(&topo)) {
                    correto = 0;
                    break;
                }
            }
        }

        /* Se a pilha nao estiver vazia no final, sobraram '(' abertos */
        if (topo != NULL) {
            correto = 0;
            limpar_pilha(&topo); /* Evita Memory Leak limpando o que sobrou */
        }

        if (correto) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}
