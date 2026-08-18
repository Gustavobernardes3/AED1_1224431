#include <stdio.h>

int maximo(int v[], int n) {

    if (n == 1) {
        return v[0];
    }
    else {
        int x;
        x = maximo(v, n - 1);

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

    return 0;
}
