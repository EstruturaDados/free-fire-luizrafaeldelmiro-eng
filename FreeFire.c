#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_STRING 50

// =======================
//     STRUCT DO ITEM
// =======================
typedef struct {
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
    int prioridade;  // 1 a 5
} Item;

// =======================
//     ENUM DE CRITÉRIO
// =======================
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// =======================
//   VARIÁVEIS GLOBAIS
// =======================
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// =======================
//     LIMPAR TELA
// =======================
void limparTela() {
    for (int i = 0; i < 20; i++)
        printf("\n");
}

// =======================
//      MENU PRINCIPAL
// =======================
void exibirMenu() {
    printf("=====================================\n");
    printf("     MOCHILA DA ILHA - FREE FIRE\n");
    printf("=====================================\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar mochila\n");
    printf("5 - Buscar item por nome (Binária)\n");
    printf("0 - Sair\n");
    printf("-------------------------------------\n");

    if (ordenadaPorNome)
        printf("[STATUS] Mochila está ORDENADA por NOME\n");
    else
        printf("[STATUS] Mochila NÃO está ordenada por NOME\n");

    printf("-------------------------------------\n");
    printf("Escolha: ");
}

// =======================
//     INSERIR ITEM
// =======================
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    scanf(" %49[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %49[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &novo.prioridade);
    } while (novo.prioridade < 1 || novo.prioridade > 5);

    mochila[numItens] = novo;
    numItens++;

    ordenadaPorNome = false;

    printf("\nItem inserido com sucesso!\n");
}

// =======================
//     REMOVER ITEM
// =======================
void removerItem() {
    char nomeBusca[TAM_STRING];
    printf("\nNome do item para remover: ");
    scanf(" %49[^\n]", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];

            numItens--;
            ordenadaPorNome = false;

            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item não encontrado!\n");
}

// =======================
//     LISTAR ITENS
// =======================
void listarItens() {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n========== ITENS DA MOCHILA ==========\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
    printf("-----------------------------------------------\n");
}

// =======================
//    INSERTION SORT
// =======================
void insertionSort(CriterioOrdenacao criterio) {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool cond = false;

            if (criterio == ORDENAR_NOME)
                cond = strcmp(chave.nome, mochila[j].nome) < 0;
            else if (criterio == ORDENAR_TIPO)
                cond = strcmp(chave.tipo, mochila[j].tipo) < 0;
            else if (criterio == ORDENAR_PRIORIDADE)
                cond = chave.prioridade > mochila[j].prioridade;

            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }
}

// =======================
//    MENU DE ORDENAÇÃO
// =======================
void menuDeOrdenacao() {
    int opc;

    printf("\n=== Ordenar por: ===\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &opc);

    if (opc < 1 || opc > 3) {
        printf("Opção inválida!\n");
        return;
    }

    insertionSort((CriterioOrdenacao)opc);

    if (opc == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    printf("Mochila ordenada com sucesso!\n");
}

// =======================
//   BUSCA BINÁRIA
// =======================
void buscaBinaria() {
    if (!ordenadaPorNome) {
        printf("\nA mochila deve estar ORDENADA POR NOME para usar busca binária!\n");
        return;
    }

    char nomeBusca[TAM_STRING];
    printf("\nNome do item para buscar: ");
    scanf(" %49[^\n]", nomeBusca);

    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nITEM ENCONTRADO:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }

        if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item não encontrado!\n");
}

// =======================
//        MAIN
// =======================
int main() {
    int opc;

    do {
        exibirMenu();
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinaria(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();
        limparTela();

    } while (opc != 0);

    return 0;
}
