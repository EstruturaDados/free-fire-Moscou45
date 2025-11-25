#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/** @brief Estrutura que representa um item na mochila do jogador.
  Contém os campos nome, tipo e quantidade.*/

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// definindo global (Requisito Funcional: Cadastro de itens)
#define MAX_ITENS 10

Item mochila[MAX_ITENS];
int contador_itens = 0; // Armazena quantos itens estão realmente ocupados

// criando funções 
void inserirItem();
void removerItem();
void listarItens();
int buscarItem(const char *nomeBusca);
void exibirMenu();

/**
 * @brief Realiza uma busca sequencial por um item na mochila.
 * * @param nomeBusca O nome do item a ser procurado.
 * @return O índice (posição) do item na mochila se encontrado; -1 caso contrário.
 * * (Requisito Funcional: Busca sequencial)
 */

 int buscarItem(const char *nomeBusca) {
    for (int i = 0; i < contador_itens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Adiciona um novo item à mochila, se houver espaço.
 * * (Requisito Funcional: Cadastro de itens)
 */
void inserirItem() {
    // Verifica se a mochila está cheia
    if (contador_itens >= MAX_ITENS) {
        printf("\n🛑 Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- CADASTRO DE NOVO ITEM ---\n");
    
    // Leitura do nome (usando scanf e ignorando lixo do buffer para simplicidade)
    printf("Nome do Item (max 29 caracteres): ");
    scanf("%29s", mochila[contador_itens].nome);

    // Verifica se o item já existe para evitar duplicatas simples (Opcional, mas útil)
    if (buscarItem(mochila[contador_itens].nome) != -1) {
        printf("⚠️ Item ja existente na mochila. Cadastro cancelado.\n");
        return;
    }

    // Leitura do tipo
    printf("Tipo do Item (ex: arma, municao, cura): ");
    scanf("%19s", mochila[contador_itens].tipo);

    // Leitura da quantidade
    printf("Quantidade: ");
    // O scanf para int é seguro neste contexto
    if (scanf("%d", &mochila[contador_itens].quantidade) != 1 || mochila[contador_itens].quantidade <= 0) {
        printf("❌ Entrada invalida para quantidade. Cadastro cancelado.\n");
        return;
    }

    contador_itens++; // Incrementa o contador
    printf("\n✅ Item '%s' cadastrado com sucesso!\n", mochila[contador_itens - 1].nome);
}

