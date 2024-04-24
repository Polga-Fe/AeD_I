#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1000

typedef struct No{
    char nome[TAM];
    struct No* prox;
}No;

typedef struct Lista{
    No* inicio;
}Lista;

Lista* criarLista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista != NULL){
        lista->inicio = NULL;
    }
    return lista;
}

void addNome(){
    
}

void removNome() {
    
}

void list(){
    
}

void freeMem(){

}

int main(){
    Lista* lista = criarLista();
    int escolha;
    
    printf("\t\tMENU:\n");
    printf("1. Adicionar nome\n");
    printf("2. Remover nome\n");
    printf("3. Listar\n");
    printf("4. Sair\n");
    scanf("%d", &escolha);
    printf("%d \n", escolha);

    switch (escolha){
    case 1:
        printf("NOME: ");
        char nome[TAM];
        scanf("%s", nome);
        addNome(lista, nome);
        break;
    case 2:
        printf("NOME A SER REMOVIDO: ");
        char nomeRemover[TAM];
        scanf("%s", nomeRemover);
        removNome(lista, nomeRemover);
        break;
    case 3:
        printf("LISTA: ");
        list(lista);
        break;
    case 4:
        printf("SAINDO . . .");
        break;
    default:
        printf("TENTE UMA OPÇÃO VÁLIDA!");
        break;
    }
    return 0;
}