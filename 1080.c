/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 25/06/2026
Objetivo    : Escrever maior valor de um vetor e posição.
Dificuldade : Resolver de forma recursiva
Uso de IA   : ajuda para colocar comentarios no código
-------------------------------------------------------------------------- */
#include <stdio.h>

/* Retorna o maior valor entre os n primeiros elementos */
int maximo(int v[], int n) {

    /* Caso base: apenas 1 elemento */
    if (n == 1) {
        return v[0];
    }
    else {

        int x;

        /* Descobre o maior dos n-1 elementos */
        x = maximo(v, n - 1);

        /* Compara o maior anterior com o último elemento */
        if (x > v[n - 1]) {
            return x;
        }
        else {
            return v[n - 1];
        }
    }
}

int main() {

    int v[100], maior, posicao;

    /* Lê os 100 valores */
    for (int i = 0; i < 100; i++) {
        scanf("%d", &v[i]);
    }

    /* Encontra o maior valor usando recursão */
    maior = maximo(v, 100);

    /* Procura a posição do maior */
    for (int i = 0; i < 100; i++) {
        if (v[i] == maior) {
            posicao = i + 1; // +1 porque posição começa em 1
            break;
        }
    }

    /* Imprime maior valor e sua posição */
    printf("%d\n", maior);
    printf("%d\n", posicao);

    return 0;
}
