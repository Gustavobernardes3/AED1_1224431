/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/2448
Data        : 24/09/2026
Objetivo    : Calcular o tempo total para entregar as encomendas
Dificuldade : Média (Requer busca binária por causa do tempo limite)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs() e alocação dinâmica

/* Função de Busca Binária
 * Retorna o índice no vetor 'v' onde o elemento 'x' se encontra.
 * Como o vetor está ordenado crescentemente e é garantido que a encomenda
 * existe nas casas, essa busca garante complexidade O(log n).
 */
int buscabinaria(int x, int n, int v[]){
    int e, m, d;
    e = -1; 
    d = n;
    
    while(e < d - 1){
        m = (e + d) / 2;
        if(v[m] < x){
            e = m; // Se o valor do meio for menor, a busca continua na metade direita
        }
        else{
            d = m; // Caso contrário, continua na metade esquerda
        }
    }
    // 'd' terminará exatamente no índice onde o valor 'x' está armazenado
    return d; 
}

int main() {
    int n, m;
    
    // Leitura da quantidade de casas (n) e quantidade de encomendas (m)
    scanf("%d %d", &n, &m);

    // Alocação dinâmica para o vetor de casas
    // Utilizando malloc para armazenar os números das 'n' casas
    int *casas = (int*) malloc(n * sizeof(int));
    
    // Leitura dos números das casas (já vêm ordenados de forma crescente da entrada)
    for(int i = 0; i < n; i++) {
        scanf("%d", &casas[i]);
    }

    long long tempo_total = 0; // Armazena o tempo total gasto (usando long long previne overflow)
    int posicao_atual = 0;     // O carteiro sempre começa na primeira casa do vetor (índice 0)
    int encomenda;

    // Processamento da entrega de cada encomenda
    for(int i = 0; i < m; i++) {
        scanf("%d", &encomenda);
        
        // Busca qual é o índice da casa de destino usando a busca binária
        int destino = buscabinaria(encomenda, n, casas);
        
        // O tempo que o carteiro leva para se mover é a distância absoluta entre os índices
        tempo_total += abs(posicao_atual - destino);
        
        // Atualiza a posição do carteiro para a casa onde ele acabou de realizar a entrega
        posicao_atual = destino;
    }

    // Imprime o resultado final
    printf("%lld\n", tempo_total);

    // Libera a memória alocada para evitar vazamentos
    free(casas);

    return 0;
}
