#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da pilha (lista encadeada)
typedef struct no{
    int conteudo;
    struct no* proximo;
} no;

// Cria o nó cabeça da pilha
no* inicializar(){
    no* cabeca = (no*) malloc(sizeof(no));
    cabeca->proximo = NULL;
    return cabeca;
}

// Função de empilhar (Push) - Insere um novo vagão no topo da pilha
void inserir(no* cabeca, int valor){
    no* novo = (no*) malloc(sizeof(no));
    novo->conteudo = valor;
    novo->proximo = cabeca->proximo;
    cabeca->proximo = novo;
}

// Função de desempilhar (Pop) - Retira o vagão do topo da pilha
int retirar(no* cabeca){
    if(cabeca->proximo == NULL){
        return -1; // Retorna -1 se a pilha estiver vazia (sem print para evitar Presentation Error)
    }
    no* auxiliar = cabeca->proximo;
    cabeca->proximo = auxiliar->proximo;
    int valorretirado = auxiliar->conteudo;
    free(auxiliar);
    return valorretirado;
}

int main(){
    int n, i, vagao, saida;

    // Loop infinito principal: controla os blocos de testes (lê o N)
    while(1) {
        scanf("%d", &n);
        
        // A condição de parada geral do problema: se N for 0, o programa acaba.
        if(n == 0) break; 

        // Aloca dinamicamente o vetor com o tamanho exato de vagões (N)
        int* v = (int*) malloc(n * sizeof(int));

        // Loop infinito secundário: testa várias permutações para o mesmo N
        while(1) {
            // Lê o primeiro número da permutação
            scanf("%d", &v[0]);
            
            // Se o primeiro número lido for 0, acabou o teste para esse N
            if(v[0] == 0) {
                printf("\n"); // O problema exige uma linha em branco separando os blocos
                break;        // Quebra o loop interno e volta para ler o próximo N
            }

            // Lê os vagões restantes da permutação (do índice 1 até n-1)
            for(i = 1; i < n; i++) {
                scanf("%d", &v[i]);
            }

            // Prepara a pilha e o índice para iniciar a simulação
            no* pilha = inicializar();
            saida = 0; // 'saida' é o índice do vetor 'v' (qual vagão estamos esperando sair agora)

            // Simulação: os vagões chegam da direção A na ordem 1, 2, 3... até n
            for(vagao = 1; vagao <= n; vagao++) {
                inserir(pilha, vagao); // O vagão entra na estação (empilha)

                // Verifica se o vagão no topo da pilha é o que estamos esperando sair
                // 1º: A pilha não pode estar vazia (pilha->proximo != NULL)
                // 2º: O conteúdo do topo deve ser igual ao vetor na posição 'saida'
                while(pilha->proximo != NULL && pilha->proximo->conteudo == v[saida]) {
                    retirar(pilha); // O vagão sai da estação em direção a B (desempilha)
                    saida++;        // Avançamos para olhar o próximo vagão da sequência
                }
            }

            // Terminada a simulação, avaliamos o resultado:
            // Se a pilha ficou vazia, significa que a organização deu certo
            if(pilha->proximo == NULL) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }

            // Limpeza de memória: esvazia qualquer vagão que tenha ficado travado na pilha
            while(pilha->proximo != NULL) {
                retirar(pilha);
            }
            free(pilha); // Libera o nó cabeça da pilha antes do próximo teste
        }
        
        // Libera o vetor de permutações antes de alocar um novo tamanho N
        free(v);
    }
    
    return 0;
}
