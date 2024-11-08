#include <stdio.h>
#include <stdlib.h>

// Estrutura da pilha
typedef struct {
    void **dados;
    int topo;
    int capacidade;
} Pilha;

// Função para criar e inicializar a pilha
Pilha* criarPilha(int capacidadeInicial) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) return NULL;

    pilha->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    if (pilha->dados == NULL) {
        free(pilha);
        return NULL;
    }

    pilha->topo = -1;
    pilha->capacidade = capacidadeInicial;

    return pilha;
}

// Função para liberar a memória da pilha
void limparPilha(Pilha *pilha) {
    if (pilha != NULL) {
        free(pilha->dados);
        free(pilha);
    }
}

// Função para dobrar a capacidade da pilha
void dobrarCapacidade(Pilha *pilha) {
    int novaCapacidade = pilha->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);

    if (novosDados == NULL) {
        printf("Erro ao alocar memória para redimensionar a pilha.\n");
        return;
    }

    for (int i = 0; i <= pilha->topo; i++) {
        novosDados[i] = pilha->dados[i];
    }

    free(pilha->dados);
    pilha->dados = novosDados;
    pilha->capacidade = novaCapacidade;
}

// Função para inserir um elemento na pilha
void empilhar(Pilha *pilha, void *item) {
    if (pilha == NULL || pilha->dados == NULL) {
        printf("Erro: Pilha não inicializada corretamente.\n");
        return;
    }

    if (pilha->topo == pilha->capacidade - 1) {
        dobrarCapacidade(pilha);
        if (pilha->dados == NULL) {
            printf("Erro ao redimensionar a pilha.\n");
            return;
        }
    }

    pilha->topo++;
    pilha->dados[pilha->topo] = item;
}

// Função para remover um elemento da pilha
void* desempilhar(Pilha *pilha) {
    if (pilha == NULL || pilha->dados == NULL || pilha->topo == -1) {
        printf("Erro: Pilha vazia ou não inicializada.\n");
        return NULL;
    }

    return pilha->dados[pilha->topo--];
}

// Função principal para teste da implementação
int main() {
    Pilha *pilha = criarPilha(2);
    if (pilha == NULL) {
        printf("Erro ao criar a pilha.\n");
        return 1;
    }

    int item1 = 15, item2 = 27, item3 = 39, item4 = 43;

    empilhar(pilha, &item1);
    empilhar(pilha, &item2);

    printf("Capacidade atual da pilha: %d\n", pilha->capacidade);

    empilhar(pilha, &item3);
    empilhar(pilha, &item4);

    printf("\nCapacidade atual da pilha: %d\n", pilha->capacidade);

    printf("\nElementos da pilha:\n");
    for (int i = 0; i <= pilha->topo; i++) {
        // A impressão dos itens deve fazer o cast para o tipo correto
        printf("%d ", *(int*)pilha->dados[i]);
    }
    printf("\n\n");

    printf("Desempilhando: %d \n", *(int*)desempilhar(pilha));
    printf("Desempilhando: %d \n", *(int*)desempilhar(pilha));
    printf("Desempilhando: %d \n", *(int*)desempilhar(pilha));
    printf("Desempilhando: %d \n", *(int*)desempilhar(pilha));

    limparPilha(pilha);
    return 0;
}
