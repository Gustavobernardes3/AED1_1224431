/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1194
Data        : 25/11/2026
Objetivo    : Determinar o percurso posfixo a partir dos percursos prefixo e infixo
Dificuldade : Média (Reconstrução recursiva de árvore binária a partir de percursos)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>

// Imprime o percurso posfixo usando os intervalos atuais de prefixa e infixa
void imprimir_posfixa(const char* prefixa, int ini_pre, int fim_pre,
                      const char* infixa, int ini_in, int fim_in) {
    if (ini_pre > fim_pre || ini_in > fim_in) {
        return;
    }

    char raiz = prefixa[ini_pre];
    int pos_raiz = ini_in;

    while (pos_raiz <= fim_in && infixa[pos_raiz] != raiz) {
        pos_raiz++;
    }

    int qtd_esq = pos_raiz - ini_in;

    // Subárvore esquerda
    imprimir_posfixa(prefixa, ini_pre + 1, ini_pre + qtd_esq,
                     infixa, ini_in, pos_raiz - 1);

    // Subárvore direita
    imprimir_posfixa(prefixa, ini_pre + qtd_esq + 1, fim_pre,
                     infixa, pos_raiz + 1, fim_in);

    // Visita da raiz por último (pós-ordem)
    printf("%c", raiz);
}

void resolver_caso() {
    int qtd_nos;
    char prefixa[60], infixa[60];

    if (scanf("%d %59s %59s", &qtd_nos, prefixa, infixa) != 3) {
        return;
    }

    imprimir_posfixa(prefixa, 0, qtd_nos - 1, infixa, 0, qtd_nos - 1);
    printf("\n");
}

int main() {
    int casos;
    if (scanf("%d", &casos) == 1) {
        while (casos--) {
            resolver_caso();
        }
    }
    return 0;
}
