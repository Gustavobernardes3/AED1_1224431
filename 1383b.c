/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 18/09/2026
Objetivo    : Validar matriz 9x9 como resolução de sudoku
Dificuldade : Fazer a função para validar a matriz
Uso de IA   : ajuda para colocar comentarios no código e no uso de calloc
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h> /* Necessario para malloc, calloc e free */

/* O parametro int a[] atua como int *a */
int valido(int *a){ 
    
    /* calloc aloca espaco para 10 inteiros na Heap e ja preenche todos com 0 */
    int *visto = (int *)calloc(10, sizeof(int));
    if (visto == NULL) return 0;

    for(int i = 0; i < 9; i++){ 
        int v = a[i]; 

        if(v < 1 || v > 9 || visto[v]){ 
            free(visto); /* Libera a memoria antes de interromper a funcao */
            return 0; 
        } 

        visto[v] = 1; 
    } 

    free(visto); /* Libera a memoria apos o uso bem-sucedido */
    return 1; 
} 
 
int main(){ 
    int n; 

    if (scanf("%d", &n) != 1) return 0; 
 
    /* 1. Alocacao da matriz 2D dinamicamente usando ponteiro duplo */
    /* Cria um vetor de ponteiros para as linhas */
    int **x = (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++) {
        /* Para cada linha, aloca espaco para 9 colunas */
        x[i] = (int *)malloc(9 * sizeof(int));
    }

    /* 2. Alocacao dos vetores auxiliares na Heap */
    int *linha = (int *)malloc(9 * sizeof(int));
    int *coluna = (int *)malloc(9 * sizeof(int));
    int *bloco = (int *)malloc(9 * sizeof(int));

    for(int f = 0; f < n; f++){ 
        int ok = 1; 
         
        /* Acesso aos elementos dinamicos x[i][j] ocorre normalmente */
        for(int i = 0; i < 9; i++){ 
            for(int j = 0; j < 9; j++){ 
                scanf("%d", &x[i][j]); 
            } 
        } 
     
        for(int i = 0; i < 9; i++){ 
            for(int j = 0; j < 9; j++){ 
                linha[j] = x[i][j]; 
            } 
            if (!valido(linha)) ok = 0; 
        } 
 
        for(int j = 0; j < 9; j++){ 
            for(int i = 0; i < 9; i++){ 
                coluna[i] = x[i][j]; 
            } 
            if (!valido(coluna)) ok = 0; 
        } 
 
        for(int bi = 0; bi < 9; bi += 3){ 
            for(int bj = 0; bj < 9; bj += 3){ 
                
                int r = 0; 

                for(int l = 0; l < 3; l++){ 
                    for(int k = 0; k < 3; k++){ 
                        bloco[r++] = x[l + bi][k + bj]; 
                    } 
                } 

                if (!valido(bloco)) ok = 0; 
            } 
        } 
 
        printf("Instancia %d\n", f + 1); 

        if (ok) { 
            printf("SIM\n"); 
        } else { 
            printf("NAO\n"); 
        } 

        printf("\n"); 
    }   

    /* 3. Liberacao de memoria (free) em ordem inversa a alocacao */
    free(linha);
    free(coluna);
    free(bloco);

    /* Libera cada linha da matriz primeiro */
    for (int i = 0; i < 9; i++) {
        free(x[i]);
    }
    /* Libera o vetor de ponteiros principal */
    free(x);

    return 0;  
}
