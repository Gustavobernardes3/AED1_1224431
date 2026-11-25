/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1340
Data        : 25/11/2026
Objetivo    : Identificar se a estrutura de dados é pilha, fila, fila de prioridade, incerta ou impossível
Dificuldade : Média (Simulação simultânea de pilha, fila e max-heap)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

static void heap_inserir(int* heap, int* tam, int valor) {
    int idx = (*tam)++;
    heap[idx] = valor;

    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (heap[pai] >= heap[idx]) {
            break;
        }
        int temp = heap[pai];
        heap[pai] = heap[idx];
        heap[idx] = temp;
        idx = pai;
    }
}

static int heap_remover_maior(int* heap, int* tam) {
    int topo = heap[0];
    (*tam)--;

    if (*tam > 0) {
        heap[0] = heap[*tam];
        int idx = 0;

        while (1) {
            int esq = 2 * idx + 1;
            int dir = 2 * idx + 2;
            int maior = idx;

            if (esq < *tam && heap[esq] > heap[maior]) {
                maior = esq;
            }
            if (dir < *tam && heap[dir] > heap[maior]) {
                maior = dir;
            }
            if (maior == idx) {
                break;
            }

            int temp = heap[idx];
            heap[idx] = heap[maior];
            heap[maior] = temp;
            idx = maior;
        }
    }

    return topo;
}

static void resolver_caso(int qtd_operacoes) {
    int* pilha = (int*)malloc((size_t)qtd_operacoes * sizeof(int));
    int* fila = (int*)malloc((size_t)qtd_operacoes * sizeof(int));
    int* pq = (int*)malloc((size_t)qtd_operacoes * sizeof(int));

    int topo_pilha = 0;
    int ini_fila = 0, fim_fila = 0;
    int tam_pq = 0;

    int eh_pilha = 1;
    int eh_fila = 1;
    int eh_pq = 1;

    for (int i = 0; i < qtd_operacoes; i++) {
        int tipo, valor;
        scanf("%d %d", &tipo, &valor);

        if (tipo == 1) {
            pilha[topo_pilha++] = valor;
            fila[fim_fila++] = valor;
            heap_inserir(pq, &tam_pq, valor);
        } else if (tipo == 2) {
            if (topo_pilha == 0 || pilha[topo_pilha - 1] != valor) {
                eh_pilha = 0;
            } else {
                topo_pilha--;
            }

            if (ini_fila == fim_fila || fila[ini_fila] != valor) {
                eh_fila = 0;
            } else {
                ini_fila++;
            }

            if (tam_pq == 0 || heap_remover_maior(pq, &tam_pq) != valor) {
                eh_pq = 0;
            }
        }
    }

    int validas = eh_pilha + eh_fila + eh_pq;

    if (validas == 0) {
        printf("impossible\n");
    } else if (validas > 1) {
        printf("not sure\n");
    } else if (eh_pilha) {
        printf("stack\n");
    } else if (eh_fila) {
        printf("queue\n");
    } else {
        printf("priority queue\n");
    }

    free(pilha);
    free(fila);
    free(pq);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        resolver_caso(n);
    }
    return 0;
}
