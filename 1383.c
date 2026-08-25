/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 25/06/2026
Objetivo    : Validar matriz 9x9 como resolução de sudoku
Dificuldade : Fazer a função para validar a matriz
Uso de IA   : ajuda para colocar comentarios no código
-------------------------------------------------------------------------- */
#include <stdio.h> 

int x[9][9]; 

// Verifica se os 9 números são válidos e não se repetem
int valido(int a[9]){ 
    
    // Cria um vetor para marcar os números que já apareceram
    // Todas as posições começam com 0
    int visto[10] = {0}; 

    for(int i = 0; i < 9; i++){ 
        int v = a[i]; 

        // Se não estiver entre 1 e 9 ou já apareceu, é inválido
        if(v < 1 || v > 9 || visto[v]){ 
            return 0; 
        } 

        // Marca o número como já encontrado
        visto[v] = 1; 
    } 

    // Se chegou aqui, os 9 números são válidos e diferentes
    return 1; 
} 
 
int main(){ 
    int n; 

    // Lê a quantidade de Sudokus que serão testados
    if (scanf("%d", &n) != 1) return 0; 
 
    // Repete o processo para cada Sudoku
    for(int f = 0; f < n; f++){ 
        int ok = 1; 
         
        // Lê os 81 números da matriz 9x9
        for(int i = 0; i < 9; i++){ 
            for(int j = 0; j < 9; j++){ 
                scanf("%d", &x[i][j]); 
            } 
        } 
     
        // Verifica as 9 linhas
        for(int i = 0; i < 9; i++){ 
            int linha[9]; 

            // Copia uma linha da matriz para um vetor
            for(int j = 0; j < 9; j++){ 
                linha[j] = x[i][j]; 
            } 

            // Se a linha for inválida, o Sudoku também é
            if (!valido(linha)) ok = 0; 
        } 
 
        // Verifica as 9 colunas
        for(int j = 0; j < 9; j++){ 
            int coluna[9]; 

            // Copia uma coluna da matriz para um vetor
            for(int i = 0; i < 9; i++){ 
                coluna[i] = x[i][j]; 
            } 

            // Se a coluna for inválida, o Sudoku também é
            if (!valido(coluna)) ok = 0; 
        } 
 
        // Percorre os blocos 3x3
        // bi e bj indicam onde cada bloco começa
        for(int bi = 0; bi < 9; bi += 3){ 
            for(int bj = 0; bj < 9; bj += 3){ 
                
                int bloco[9], r = 0; 

                // Copia os 9 números do bloco para um vetor
                for(int l = 0; l < 3; l++){ 
                    for(int k = 0; k < 3; k++){ 
                        bloco[r++] = x[l + bi][k + bj]; 
                    } 
                } 

                // Verifica se o bloco 3x3 é válido
                if (!valido(bloco)) ok = 0; 
            } 
        } 
 
        // Mostra qual Sudoku está sendo analisado
        printf("Instancia %d\n", f + 1); 

        // Se linhas, colunas e blocos forem válidos
        if (ok) { 
            printf("SIM\n"); 
        } else { 
            printf("NAO\n"); 
        } 

        printf("\n"); 
    }    

    return 0;  
}
