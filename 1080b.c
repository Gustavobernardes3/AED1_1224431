/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 18/09/2026
Objetivo    : Escrever maior valor de um vetor e posição.
Dificuldade : Resolver de forma recursiva
Uso de IA   : ajuda para colocar comentarios no código
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h> /* Necessario para malloc e free */

/* Retorna o maior valor; o ponteiro *v atua de forma identica a um vetor */
int maximo(int *v, int n) {
    /* Caso base: um subvetor de tamanho 1 tem seu unico elemento como maximo */
    if (n == 1) {
        return v[0];
    }
    else {
        /* Encontra recursivamente o maior valor nos primeiros n-1 elementos */
        int x = maximo(v, n - 1);
        
        /* Compara o maior valor encontrado (x) com o ultimo elemento atual (v[n-1]) */
        if (x > v[n - 1]) {
            return x;
        }
        else {
            return v[n - 1];
        }
    }
}

int main() {
    /* Ponteiro na Stack para armazenar o endereco do bloco na Heap */
    int *v;
    int maior, posicao;

    /* Aloca espaco contiguo para 100 inteiros na memoria Heap */
    v = (int *)malloc(100 * sizeof(int));

    /* Verifica se a memoria foi alocada com sucesso */
    if (v == NULL) {
        return 1; 
    }

    /* Acesso aos elementos dinamicos ocorre normalmente via indice */
    for (int i = 0; i < 100; i++) {
        scanf("%d", &v[i]);
    }

    maior = maximo(v, 100);

    for (int i = 0; i < 100; i++) {
        if (v[i] == maior) {
            posicao = i + 1;
            break;
        }
    }

    printf("%d\n", maior);
    printf("%d\n", posicao);

    /* Libera a memoria trancada na Heap (previne memory leak) */
    free(v);

    return 0;
}
