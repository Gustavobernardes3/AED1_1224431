/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1077
Data        : 29/09/2026
Objetivo    : passar expressões de infixa para posfixa
Dificuldade : Média
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct no {
    char c;
    struct no *prox;
} No;

// Coloca um elemento no topo da pilha
void push(No **topo, char c) {
    No *novo = (No *)malloc(sizeof(No));

    novo->c = c;
    novo->prox = *topo;
    *topo = novo;
}

// Retira e retorna o elemento do topo
char pop(No **topo) {
    No *aux = *topo;
    char c = aux->c;

    *topo = aux->prox;
    free(aux);

    return c;
}

// Retorna o elemento do topo
char top(No *topo) {
    return topo->c;
}

// Define a prioridade dos operadores
int precedencia(char c) {
    if (c == '+' || c == '-')
        return 1;

    if (c == '*' || c == '/')
        return 2;

    if (c == '^')
        return 3;

    return 0;
}

int main() {
    int n;
    char exp[310];

    scanf("%d", &n);

    while (n--) {
        scanf("%s", exp);

        No *topo = NULL; // Pilha começa vazia

        for (int i = 0; i < strlen(exp); i++) {

            // Letras e números vão direto para a saída
            if (isalnum(exp[i])) {
                printf("%c", exp[i]);
            }

            // Abre parênteses: empilha
            else if (exp[i] == '(') {
                push(&topo, exp[i]);
            }

            // Fecha parênteses: desempilha até encontrar '('
            else if (exp[i] == ')') {
                while (top(topo) != '(') {
                    printf("%c", pop(&topo));
                }

                pop(&topo); // Remove o '('
            }

            // É um operador
            else {
                // Desempilha operadores de maior ou igual prioridade
                while (topo != NULL &&
                       top(topo) != '(' &&
                       precedencia(top(topo)) >= precedencia(exp[i])) {

                    printf("%c", pop(&topo));
                }

                // Empilha o operador atual
                push(&topo, exp[i]);
            }
        }

        // Desempilha o que sobrou
        while (topo != NULL) {
            printf("%c", pop(&topo));
        }

        printf("\n");
    }

    return 0;
}
