#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------
// 1. Definição da Struct (Requisito Funcional: Criação da struct)
// -----------------------------------------------------------
/**
 * @brief Estrutura que representa um item na mochila do jogador.
 * * Contém os campos nome, tipo e quantidade.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Constante para o tamanho máximo da mochila (Requisito Funcional: Cadastro de itens)
#define MAX_ITENS 10

// Variáveis globais para a mochila e o contador
Item mochila[MAX_ITENS];
int contador_itens = 0; // Armazena quantos itens estão realmente ocupados

// -----------------------------------------------------------
// 2. Protótipos das Funções (Instruções detalhadas)
// -----------------------------------------------------------
void inserirItem();
void removerItem();
void listarItens();
int buscarItem(const char *nomeBusca);
void exibirMenu();

// -----------------------------------------------------------
// 3. Funções Obrigatórias e Auxiliares
// -----------------------------------------------------------

/**
 * @brief Realiza uma busca sequencial por um item na mochila.
 * * @param nomeBusca O nome do item a ser procurado.
 * @return O índice (posição) do item na mochila se encontrado; -1 caso contrário.
 * * (Requisito Funcional: Busca sequencial)
 */
int buscarItem(const char *nomeBusca) {
    // Laço for para percorrer todo o vetor de itens
    for (int i = 0; i < contador_itens; i++) {
        // Compara a string de busca com o nome do item atual
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado, retorna o índice
        }
    }
    return -1; // Item não encontrado
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

/**
 * @brief Remove um item da mochila com base no nome.
 * * (Requisito Funcional: Remoção de itens)
 */
void removerItem() {
    char nome_remover[30];
    printf("\n--- REMOCAO DE ITEM ---\n");
    
    // Leitura do nome do item a ser removido
    printf("Informe o NOME do item a ser removido: ");
    scanf("%29s", nome_remover);

    // 1. Busca pelo item
    int indice = buscarItem(nome_remover);

    if (indice == -1) {
        printf("\n❌ Item '%s' nao encontrado na mochila.\n", nome_remover);
        return;
    }

    // 2. Remoção (Move o último item para a posição do item excluído)
    // Isso evita "buracos" no vetor e é eficiente para remoção.
    printf("\nItem '%s' (Quantidade: %d) sera removido.\n", mochila[indice].nome, mochila[indice].quantidade);
    
    // Se o item a ser removido não for o último, move o último para sua posição
    if (indice != contador_itens - 1) {
        // Copia a struct completa do último item para o índice de remoção
        mochila[indice] = mochila[contador_itens - 1];
    }

    contador_itens--; // Decrementa o contador de itens
    printf("✅ Remocao concluida. A mochila agora tem %d itens.\n", contador_itens);
}

/**
 * @brief Lista todos os itens atualmente registrados na mochila.
 * * (Requisito Funcional: Listagem dos itens registrados)
 */
void listarItens() {
    printf("\n============================================\n");
    printf("       📜 ITENS ATUAIS DA MOCHILA (%d/%d)      \n", contador_itens, MAX_ITENS);
    printf("============================================\n");
    
    if (contador_itens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf(" %-4s | %-28s | %-18s | %-10s\n", "ID", "NOME", "TIPO", "QTD");
    printf("-------------------------------------------------------------------\n");

    // Laço for para percorrer e imprimir os dados
    for (int i = 0; i < contador_itens; i++) {
        printf(" %-4d | %-28s | %-18s | %-10d\n", 
               i, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("-------------------------------------------------------------------\n");
}


// -----------------------------------------------------------
// 4. Interface do Usuário (Requisito Não Funcional: Usabilidade)
// -----------------------------------------------------------

/**
 * @brief Exibe o menu principal para o jogador.
 * * (Requisito Não Funcional: Usabilidade)
 */
void exibirMenu() {
    printf("\n--- MENU DA MOCHILA ---\n");
    printf("1. Inserir novo Item\n");
    printf("2. Remover Item pelo Nome\n");
    printf("3. Buscar Item pelo Nome\n");
    printf("4. Sair do Sistema\n");
    printf("-----------------------\n");
    printf("Escolha uma opcao: ");
}

// -----------------------------------------------------------
// 5. Função Principal (Fluxo de Execução)
// -----------------------------------------------------------
int main() {
    int opcao;
    char nomeBusca[30];
    int indiceEncontrado;

    // Laço principal para manter o programa em execução até que o usuário saia
    do {
        // Exibe a lista de itens antes do menu principal (Requisito Funcional: Listagem após cada operação)
        listarItens(); 
        
        exibirMenu();
        // A leitura de 'opcao' é feita diretamente, o que minimiza o delay (Desempenho)
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer em caso de entrada inválida
            while (getchar() != '\n');
            opcao = 0; // Define uma opção inválida
            printf("❌ Entrada invalida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                printf("\n--- BUSCA DE ITEM ---\n");
                printf("Informe o NOME do item para buscar: ");
                scanf("%29s", nomeBusca);
                
                indiceEncontrado = buscarItem(nomeBusca);
                
                if (indiceEncontrado != -1) {
                    Item item = mochila[indiceEncontrado];
                    printf("\n✅ Item encontrado na posicao %d:\n", indiceEncontrado);
                    printf("Nome: %s\n", item.nome);
                    printf("Tipo: %s\n", item.tipo);
                    printf("Quantidade: %d\n", item.quantidade);
                } else {
                    printf("\n❌ Item '%s' nao foi encontrado na mochila.\n", nomeBusca);
                }
                break;
            case 4:
                printf("\nSaindo do sistema. Adeus!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao entre 1 e 4.\n");
                break;
        }
        
        // Pausa breve para garantir que o usuário veja a saída antes da próxima listagem
        if (opcao != 4) {
            printf("\nPressione ENTER para continuar...\n");
            // Limpa o buffer de entrada e espera uma nova linha (Enter)
            while (getchar() != '\n'); 
            getchar(); 
        }

    } while (opcao != 4);

    return 0;
}