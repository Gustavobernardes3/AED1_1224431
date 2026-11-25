/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Gustavo Bernardes dos Santos
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1191
Data        : 25/11/2026
Objetivo    : Recuperar e imprimir o percurso posfixo a partir dos percursos prefixo e infixo
Dificuldade : Média (Reconstrução recursiva de árvore binária com leitura até EOF)
Uso de IA   : Ajuda com comentários no código e lógica
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

static void imprimir_posfixa(const char* prefixa, int ini_pre, int fim_pre,
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

    imprimir_posfixa(prefixa, ini_pre + 1, ini_pre + qtd_esq,
                     infixa, ini_in, pos_raiz - 1);

    imprimir_posfixa(prefixa, ini_pre + qtd_esq + 1, fim_pre,
                     infixa, pos_raiz + 1, fim_in);

    printf("%c", raiz);
}

int main() {
    char prefixa[30], infixa[30];

    while (scanf("%29s %29s", prefixa, infixa) == 2) {
        int tam = (int)strlen(prefixa);
        imprimir_posfixa(prefixa, 0, tam - 1, infixa, 0, tam - 1);
        printf("\n");
    }

    return 0;
}
