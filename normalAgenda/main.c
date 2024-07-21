#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50 // Comprimento máximo do nome
#define MAX_PESSOAS 100  // Máximo de pessoas na agenda

typedef struct Pessoa {
    char nome[NAME_LEN];
    int idade;
    struct Pessoa *prev;
    struct Pessoa *next;
} Pessoa;

Pessoa *head = NULL;
Pessoa *tail = NULL;

// Função para criar uma nova pessoa
Pessoa* criarPessoa(const char* nome, int idade) {
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (novaPessoa == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strncpy(novaPessoa->nome, nome, NAME_LEN);
    novaPessoa->idade = idade;
    novaPessoa->prev = NULL;
    novaPessoa->next = NULL;
    return novaPessoa;
}

// Função para adicionar uma pessoa na lista em ordem alfabética
void adicionarPessoa() {
    char nome[NAME_LEN];
    int idade;

    printf("Digite o nome da pessoa: ");
    scanf("%49s", nome);
    printf("Digite a idade da pessoa: ");
    scanf("%d", &idade);

    Pessoa *novaPessoa = criarPessoa(nome, idade);

    if (head == NULL) {
        head = tail = novaPessoa;
        return;
    }

    Pessoa *atual = head;
    while (atual != NULL && strcmp(atual->nome, nome) < 0) {
        atual = atual->next;
    }

    if (atual == NULL) {
        tail->next = novaPessoa;
        novaPessoa->prev = tail;
        tail = novaPessoa;
    } else if (atual == head) {
        novaPessoa->next = head;
        head->prev = novaPessoa;
        head = novaPessoa;
    } else {
        novaPessoa->next = atual;
        novaPessoa->prev = atual->prev;
        atual->prev->next = novaPessoa;
        atual->prev = novaPessoa;
    }
}

// Função para mostrar todas as pessoas na agenda
void mostrarPessoas() {
    if (head == NULL) {
        printf("A agenda está vazia!\n");
        return;
    }

    Pessoa *atual = head;
    while (atual != NULL) {
        printf("Nome: %s, Idade: %d\n", atual->nome, atual->idade);
        atual = atual->next;
    }
}

// Função para procurar uma pessoa pelo nome
void procurarPessoa() {
    char nome[NAME_LEN];
    printf("Digite o nome da pessoa que deseja procurar: ");
    scanf("%49s", nome);

    Pessoa *atual = head;
    while (atual != NULL) {
        if (strcmp(nome, atual->nome) == 0) {
            printf("Pessoa encontrada: Nome: %s, Idade: %d\n", atual->nome, atual->idade);
            return;
        }
        atual = atual->next;
    }
    printf("Pessoa não encontrada!\n");
}

// Função para remover uma pessoa pelo nome
void removerPessoa() {
    char nome[NAME_LEN];
    printf("Digite o nome da pessoa que deseja remover: ");
    scanf("%49s", nome);

    Pessoa *atual = head;
    while (atual != NULL) {
        if (strcmp(nome, atual->nome) == 0) {
            if (atual->prev != NULL) {
                atual->prev->next = atual->next;
            } else {
                head = atual->next;
            }
            if (atual->next != NULL) {
                atual->next->prev = atual->prev;
            } else {
                tail = atual->prev;
            }
            free(atual);
            printf("Pessoa removida com sucesso!\n");
            return;
        }
        atual = atual->next;
    }
    printf("Pessoa não encontrada!\n");
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar pessoa\n");
        printf("2. Mostrar pessoas\n");
        printf("3. Procurar pessoa\n");
        printf("4. Remover pessoa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                adicionarPessoa();
                break;
            case 2:
                mostrarPessoas();
                break;
            case 3:
                procurarPessoa();
                break;
            case 4:
                removerPessoa();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Libera a memória da lista
    while (head != NULL) {
        Pessoa *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
