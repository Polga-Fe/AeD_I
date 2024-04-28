#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
    char nome[30];
    int idade;
    int altura;
    struct Pessoa *prox;
}Pessoa;

typedef struct Agenda {
    Pessoa *inicio;
    int tam;
} Agenda;

void criarAgenda(Agenda *agenda){
    agenda->inicio = NULL;
    agenda->tam = 0;
}

void adicionarPessoa(Agenda *agenda, Pessoa *novaPessoa){
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (pessoa == NULL){
        printf("Erro ao alocar memória na agenda.\n");
        exit(1);
    }

    strcpy(pessoa->nome, novaPessoa->nome);
    pessoa->idade = novaPessoa->idade;
    pessoa->altura = novaPessoa->altura;
    pessoa->prox = NULL;

    if (agenda->inicio == NULL){
        agenda->inicio = pessoa;
    } else{
        Pessoa *atual = agenda->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = pessoa;
    }
    agenda->tam++;
}

void mostrarAgenda(Agenda *agenda){
    if (agenda->inicio == NULL){
        printf("AGENDA VAZIA.\n");
        return;
    }

    Pessoa *atual = agenda->inicio;
    while (atual != NULL) {
        printf("NOME: %s\n", atual->nome);
        printf("IDADE: %d\n", atual->idade);
        printf("ALTURA: %d\n", atual->altura);
        atual = atual->prox;
    }
    printf("\n");
}

int main(){
    Agenda agenda;
    criarAgenda(&agenda);

    int escolha;
    
    do {
        printf("\t\tBEM VINDO A AGENDA\n");
        printf("SELECIONE O QUE DESEJA FAZER: \n");
        printf("1. ADICIONAR PESSOA\n");
        printf("2. MOSTRAR LISTA\n");
        printf("0. SAIR DA AGENDA\n");
        scanf("%d", &escolha);

        switch (escolha){
            case 0:
            printf("SAINDO . . .\n");
            break;
            case 1:
            Pessoa novo;
            printf("NOME: \n");
            scanf("%29s", novo.nome);
            printf("IDADE: \n");
            scanf("%d", &novo.idade);
            printf("ALTURA: \n");
            scanf("%d", &novo.altura);
            adicionarPessoa(&agenda, &novo);
            break;
            case 2:
            mostrarAgenda(&agenda);
            break;
            default:
            printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
            break;
        }
    }while (escolha != 0);
    
    system("pause");
    return 0;
}

