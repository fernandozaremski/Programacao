#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limites do sistema
#define MAX_OBRAS 10
#define MAX_ESTRUTURAS 20
#define MAX_PECAS 100
#define TAM_STR 100

// Estrutura para Peça
typedef struct {
    char codigo[TAM_STR]; // ex: P123
    char posicao[TAM_STR]; // ex: A1, B2
    int quantidade;
    char status[TAM_STR]; // ex: "enviada", "pendente"
} Peca;

// Estrutura para Estrutura
typedef struct {
    char codigo[TAM_STR]; // ex: E123
    Peca pecas[MAX_PECAS];
    int totalPecas;
} Estrutura;

// Estrutura para Obra
typedef struct {
    char nome[TAM_STR];
    Estrutura estruturas[MAX_ESTRUTURAS];
    int totalEstruturas;
} Obra;

// Banco de dados simulado
Obra bancoObras[MAX_OBRAS];
int totalObras = 0;

// Protótipos
void exibirMenu();
void cadastrarObra();
void adicionarEstrutura();
void adicionarPeca();
void listarObras();
void editarObra();
void editarEstrutura();
void editarPeca();
void excluirObra();
void excluirEstrutura();
void excluirPeca();

int main() {
    int opcao;

    while (1) {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n'

        switch(opcao) {
            case 1:
                cadastrarObra();
                break;
            case 2:
                adicionarEstrutura();
                break;
            case 3:
                adicionarPeca();
                break;
            case 4:
                listarObras();
                break;
            case 5:
                editarObra();
                break;
            case 6:
                editarEstrutura();
                break;
            case 7:
                editarPeca();
                break;
            case 8:
                excluirObra();
                break;
            case 9:
                excluirEstrutura();
                break;
            case 10:
                excluirPeca();
                break;
            case 11:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

// Mostra o menu principal
void exibirMenu() {
    printf("\n=== Sistema de Controle de Terceirizações Industriais ===\n");
    printf("1. Cadastrar Obra\n");
    printf("2. Adicionar Estrutura a Obra\n");
    printf("3. Adicionar Peça a Estrutura\n");
    printf("4. Listar Todas as Obras\n");
    printf("5. Editar Obra\n");
    printf("6. Editar Estrutura\n");
    printf("7. Editar Peça\n");
    printf("8. Excluir Obra\n");
    printf("9. Excluir Estrutura\n");
    printf("10. Excluir Peça\n");
    printf("11. Sair\n");
}

// Cadastra uma nova obra
void cadastrarObra() {
    if (totalObras >= MAX_OBRAS) {
        printf("Limite de obras atingido.\n");
        return;
    }

    Obra o;
    o.totalEstruturas = 0;

    printf("Nome da Obra: ");
    fgets(o.nome, TAM_STR, stdin);
    o.nome[strcspn(o.nome, "\n")] = '\0';

    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, o.nome) == 0) {
            printf("Já existe uma obra com esse nome.\n");
            return;
        }
    }

    bancoObras[totalObras++] = o;
    printf("Obra '%s' cadastrada com sucesso!\n", o.nome);
}

// Adiciona uma estrutura a uma obra existente
void adicionarEstrutura() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR];
    printf("Nome da obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura e;
    e.totalPecas = 0;

    printf("Código da Estrutura (ex: E123): ");
    fgets(e.codigo, TAM_STR, stdin);
    e.codigo[strcspn(e.codigo, "\n")] = '\0';

    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, e.codigo) == 0) {
            printf("Estrutura com código '%s' já existe nessa obra.\n", e.codigo);
            return;
        }
    }

    bancoObras[idxObra].estruturas[bancoObras[idxObra].totalEstruturas++] = e;
    printf("Estrutura '%s' adicionada à obra '%s'.\n", e.codigo, nomeObra);
}

// Adiciona uma peça a uma estrutura de uma obra
void adicionarPeca() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR], codEstrutura[TAM_STR];
    printf("Nome da Obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    printf("Código da Estrutura: ");
    fgets(codEstrutura, TAM_STR, stdin);
    codEstrutura[strcspn(codEstrutura, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura *estrutura = NULL;
    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, codEstrutura) == 0) {
            estrutura = &bancoObras[idxObra].estruturas[j];
            break;
        }
    }

    if (!estrutura) {
        printf("Estrutura '%s' não encontrada.\n", codEstrutura);
        return;
    }

    Peca p;

    printf("Código da Peça (ex: P123): ");
    fgets(p.codigo, TAM_STR, stdin);
    p.codigo[strcspn(p.codigo, "\n")] = '\0';

    for (int k = 0; k < estrutura->totalPecas; k++) {
        if (strcmp(estrutura->pecas[k].codigo, p.codigo) == 0) {
            printf("Peça com código '%s' já existe nessa estrutura.\n", p.codigo);
            return;
        }
    }

    printf("Posição (ex: A1, B2): ");
    fgets(p.posicao, TAM_STR, stdin);
    p.posicao[strcspn(p.posicao, "\n")] = '\0';

    printf("Quantidade Enviada: ");
    scanf("%d", &p.quantidade);
    getchar();

    strcpy(p.status, "enviada");

    estrutura->pecas[estrutura->totalPecas++] = p;
    printf("Peça '%s' adicionada à estrutura '%s' da obra '%s'.\n",
           p.codigo, codEstrutura, nomeObra);
}

// Lista todas as obras, estruturas e peças
void listarObras() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalObras; i++) {
        printf("\n--- Obra: %s ---\n", bancoObras[i].nome);

        for (int j = 0; j < bancoObras[i].totalEstruturas; j++) {
            printf("  |- Estrutura: %s\n", bancoObras[i].estruturas[j].codigo);

            for (int k = 0; k < bancoObras[i].estruturas[j].totalPecas; k++) {
                Peca p = bancoObras[i].estruturas[j].pecas[k];
                printf("     |- Peça: %s | Posição: %s | Qtde: %d | Status: %s\n",
                       p.codigo, p.posicao, p.quantidade, p.status);
            }
        }
    }
}

// Edita o nome de uma obra
void editarObra() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR];
    printf("Nome da obra a ser editada: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            printf("Novo nome para a obra: ");
            fgets(bancoObras[i].nome, TAM_STR, stdin);
            bancoObras[i].nome[strcspn(bancoObras[i].nome, "\n")] = '\0';
            printf("Obra atualizada com sucesso!\n");
            return;
        }
    }

    printf("Obra '%s' não encontrada.\n", nomeObra);
}

// Edita o código de uma estrutura
void editarEstrutura() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR], codEstrutura[TAM_STR];
    printf("Nome da obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    printf("Código da estrutura a ser editada: ");
    fgets(codEstrutura, TAM_STR, stdin);
    codEstrutura[strcspn(codEstrutura, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura *estrutura = NULL;
    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, codEstrutura) == 0) {
            estrutura = &bancoObras[idxObra].estruturas[j];
            break;
        }
    }

    if (!estrutura) {
        printf("Estrutura '%s' não encontrada.\n", codEstrutura);
        return;
    }

    printf("Novo código para a estrutura: ");
    fgets(estrutura->codigo, TAM_STR, stdin);
    estrutura->codigo[strcspn(estrutura->codigo, "\n")] = '\0';

    printf("Estrutura atualizada com sucesso!\n");
}

// Edita posição ou quantidade de uma peça
void editarPeca() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR], codEstrutura[TAM_STR], codPeca[TAM_STR];
    printf("Nome da obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    printf("Código da estrutura: ");
    fgets(codEstrutura, TAM_STR, stdin);
    codEstrutura[strcspn(codEstrutura, "\n")] = '\0';

    printf("Código da peça a ser editada: ");
    fgets(codPeca, TAM_STR, stdin);
    codPeca[strcspn(codPeca, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura *estrutura = NULL;
    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, codEstrutura) == 0) {
            estrutura = &bancoObras[idxObra].estruturas[j];
            break;
        }
    }

    if (!estrutura) {
        printf("Estrutura '%s' não encontrada.\n", codEstrutura);
        return;
    }

    Peca *peca = NULL;
    for (int k = 0; k < estrutura->totalPecas; k++) {
        if (strcmp(estrutura->pecas[k].codigo, codPeca) == 0) {
            peca = &estrutura->pecas[k];
            break;
        }
    }

    if (!peca) {
        printf("Peça '%s' não encontrada.\n", codPeca);
        return;
    }

    printf("Nova posição (atual: %s): ", peca->posicao);
    fgets(peca->posicao, TAM_STR, stdin);
    peca->posicao[strcspn(peca->posicao, "\n")] = '\0';

    printf("Nova quantidade (atual: %d): ", peca->quantidade);
    scanf("%d", &peca->quantidade);
    getchar();

    printf("Peça atualizada com sucesso!\n");
}

// Exclui uma obra e tudo que ela contém
void excluirObra() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR];
    printf("Nome da obra a ser excluída: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            for (int j = i; j < totalObras - 1; j++) {
                bancoObras[j] = bancoObras[j + 1];
            }
            totalObras--;
            printf("Obra '%s' excluída com sucesso!\n", nomeObra);
            return;
        }
    }

    printf("Obra '%s' não encontrada.\n", nomeObra);
}

// Exclui uma estrutura e suas peças
void excluirEstrutura() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR], codEstrutura[TAM_STR];
    printf("Nome da obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    printf("Código da estrutura a ser excluída: ");
    fgets(codEstrutura, TAM_STR, stdin);
    codEstrutura[strcspn(codEstrutura, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura *estrutura = NULL;
    int idxEstrutura = -1;
    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, codEstrutura) == 0) {
            idxEstrutura = j;
            estrutura = &bancoObras[idxObra].estruturas[j];
            break;
        }
    }

    if (!estrutura) {
        printf("Estrutura '%s' não encontrada.\n", codEstrutura);
        return;
    }

    for (int j = idxEstrutura; j < bancoObras[idxObra].totalEstruturas - 1; j++) {
        bancoObras[idxObra].estruturas[j] = bancoObras[idxObra].estruturas[j + 1];
    }
    bancoObras[idxObra].totalEstruturas--;

    printf("Estrutura '%s' excluída com sucesso!\n", codEstrutura);
}

// Exclui uma peça
void excluirPeca() {
    if (totalObras == 0) {
        printf("Nenhuma obra cadastrada.\n");
        return;
    }

    char nomeObra[TAM_STR], codEstrutura[TAM_STR], codPeca[TAM_STR];
    printf("Nome da obra: ");
    fgets(nomeObra, TAM_STR, stdin);
    nomeObra[strcspn(nomeObra, "\n")] = '\0';

    printf("Código da estrutura: ");
    fgets(codEstrutura, TAM_STR, stdin);
    codEstrutura[strcspn(codEstrutura, "\n")] = '\0';

    printf("Código da peça a ser excluída: ");
    fgets(codPeca, TAM_STR, stdin);
    codPeca[strcspn(codPeca, "\n")] = '\0';

    int idxObra = -1;
    for (int i = 0; i < totalObras; i++) {
        if (strcmp(bancoObras[i].nome, nomeObra) == 0) {
            idxObra = i;
            break;
        }
    }

    if (idxObra == -1) {
        printf("Obra '%s' não encontrada.\n", nomeObra);
        return;
    }

    Estrutura *estrutura = NULL;
    for (int j = 0; j < bancoObras[idxObra].totalEstruturas; j++) {
        if (strcmp(bancoObras[idxObra].estruturas[j].codigo, codEstrutura) == 0) {
            estrutura = &bancoObras[idxObra].estruturas[j];
            break;
        }
    }

    if (!estrutura) {
        printf("Estrutura '%s' não encontrada.\n", codEstrutura);
        return;
    }

    int idxPeca = -1;
    for (int k = 0; k < estrutura->totalPecas; k++) {
        if (strcmp(estrutura->pecas[k].codigo, codPeca) == 0) {
            idxPeca = k;
            break;
        }
    }

    if (idxPeca == -1) {
        printf("Peça '%s' não encontrada.\n", codPeca);
        return;
    }

    for (int k = idxPeca; k < estrutura->totalPecas - 1; k++) {
        estrutura->pecas[k] = estrutura->pecas[k + 1];
    }
    estrutura->totalPecas--;

    printf("Peça '%s' excluída com sucesso!\n", codPeca);
}
