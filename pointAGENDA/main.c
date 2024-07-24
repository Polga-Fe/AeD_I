#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER ((sizeof(int) * 3) + (sizeof(char) * 20) + (sizeof(void*)))
#define PESSOA ((sizeof(char) * 20) + (sizeof(int)) + (sizeof(char) * 32) + (sizeof(void*) * 2))

void *addPessoa(void *pBuffer);
void removePessoa(void *pBuffer);
void searchPessoa(void *pBuffer);
void showPessoas(void *pBuffer);

int main(void) {
    void *pBuffer;

    // Atribuir pBuffer com HEADER
    pBuffer = malloc(HEADER);
    if (pBuffer == NULL) {
        printf("Erro em alocação de memória!");
        return 1;
    }

    int *options = (int*)pBuffer; // Opção selecionada
    int *tam = (int*)(pBuffer + sizeof(int)); // Tamanho da lista
    int *loop = (int*)(pBuffer + (sizeof(int) * 2)); // Contador para loops
    char *busca = (char*)(pBuffer + (sizeof(int) * 3)); // Busca
    void **header = (void**)(pBuffer + (sizeof(int) * 3) + (sizeof(char) * 20)); // Cabeça

    *options = 0;
    *tam = 0;
    *loop = 0;
    *header = NULL;

    while (1) {
        // Menu de opções
        printf("BEM VINDO A AGENDINHA'S AeD\n");
        printf("1. ADICIONAR PESSOA\n");
        printf("2. REMOVER PESSOA\n");
        printf("3. PROCURAR PESSOA\n");
        printf("4. MOSTRAR AGENDA\n");
        printf("0. SAIR\n");
        scanf("%d", options);

        printf("\nOPTION: %d\n", *options);
        printf("TAM: %d\n", *tam);

        switch (*options) {
            case 0:
                printf("SAINDO . . . \n");
                free(pBuffer);
                return 0;
            case 1:
                pBuffer = addPessoa(pBuffer);
                break;
            case 2:
                removePessoa(pBuffer);
                break;
            case 3:
                searchPessoa(pBuffer);
                break;
            case 4:
                showPessoas(pBuffer);
                break;
            default:
                printf("OPÇÃO INVÁLIDA. TENTA UMA DAS QUE PODE AÍ Ô MEU.\n");
                break;
        }
    }

    free(pBuffer);
    return 0;
}

void *addPessoa(void *pBuffer) {
    void *pPessoa = malloc(PESSOA);
    if (pPessoa == NULL) {
        printf("Erro em alocação de memória para nova pessoa!");
        return pBuffer;
    }

    int *tam = (int*)(pBuffer + sizeof(int));
    void **header = (void**)(pBuffer + (sizeof(int) * 3) + (sizeof(char) * 20));

    void **pPrev = (void**)pPessoa;
    char *pNome  = (char*)pPessoa + sizeof(void*);
    int  *pIdade = (int*)(pPessoa + (sizeof(char) * 20) + sizeof(void*));
    char *pEmail = (char*)(pPessoa + (sizeof(char) * 20) + sizeof(int) + sizeof(void*));
    void **pNext = (void**)(pPessoa + (sizeof(char) * 20) + (sizeof(int)) + (sizeof(char) * 32) + sizeof(void*));

    *pPrev = NULL;
    *pNext = NULL;

    printf("NOME: ");
    scanf("%s", pNome);
    printf("IDADE: ");
    scanf("%d", pIdade);
    printf("EMAIL: ");
    scanf("%s", pEmail);

    if (*tam == 0) {
        *header = pPessoa;
    } else {
        void *toto = *header;
        void *pAnterior = NULL;

        while (toto != NULL && strcmp((char*)toto + sizeof(void*), pNome) < 0) {
            pAnterior = toto;
            toto = *(void**)((char*)toto + PESSOA - sizeof(void*));
        }

        if (pAnterior == NULL) {
            *header = pPessoa;
        } else {
            *(void**)((char*)pAnterior + PESSOA - sizeof(void*)) = pPessoa;
            *pPrev = pAnterior;
        }

        if (toto != NULL) {
            *pNext = toto;
            *(void**)((char*)toto) = pPessoa;
        }
    }

    (*tam)++;
    return pBuffer;
}

void removePessoa(void *pBuffer) {
    printf("Digite o nome a ser removido: ");
    scanf("%s", (char*)(pBuffer + sizeof(int) * 3));

    int *tam = (int*)(pBuffer + sizeof(int));
    void **header = (void**)(pBuffer + (sizeof(int) * 3) + (sizeof(char) * 20));

    void *toto = *header;
    void *pAnterior = NULL;

    while (toto != NULL && strcmp((char*)toto + sizeof(void*), (char*)(pBuffer + sizeof(int) * 3)) != 0) {
        pAnterior = toto;
        toto = *(void**)((char*)toto + PESSOA - sizeof(void*));
    }

    if (toto == NULL) {
        printf("CONTATO NÃO ENCONTRADO!\n");
        return;
    }

    if (pAnterior == NULL) {
        *header = *(void**)((char*)toto + PESSOA - sizeof(void*));
    } else {
        *(void**)((char*)pAnterior + PESSOA - sizeof(void*)) = *(void**)((char*)toto + PESSOA - sizeof(void*));
    }

    if (*(void**)((char*)toto + PESSOA - sizeof(void*)) != NULL) {
        *(void**)((char*)*(void**)((char*)toto + PESSOA - sizeof(void*)) + sizeof(void*)) = pAnterior;
    }

    free(toto);
    (*tam)--;
    printf("CONTATO REMOVIDO COM SUCESSO!\n");
}

void searchPessoa(void *pBuffer) {
    printf("DIGITE O NOME A SER BUSCADO: ");
    scanf("%s", (char*)(pBuffer + sizeof(int) * 3));

    int *tam = (int*)(pBuffer + sizeof(int));
    void **header = (void**)(pBuffer + (sizeof(int) * 3) + (sizeof(char) * 20));
    void *toto = *header;

    while (toto != NULL) {
        if (strcmp((char*)toto + sizeof(void*), (char*)(pBuffer + sizeof(int) * 3)) == 0) {
            printf("NOME: %s\n", (char*)toto + sizeof(void*));
            printf("IDADE: %d\n", *(int*)((char*)toto + sizeof(void*) + sizeof(char) * 20));
            printf("EMAIL: %s\n", (char*)((char*)toto + sizeof(void*) + 20 + sizeof(int)));
            return;
        }
        toto = *(void**)((char*)toto + PESSOA - sizeof(void*));
    }
    printf("CONTATO NÃO ENCONTRADO!\n");
}

void showPessoas(void *pBuffer) {
    int *tam = (int*)(pBuffer + sizeof(int));
    int *count = (int*)(pBuffer + sizeof(int) * 2);
    void **header = (void**)(pBuffer + (sizeof(int) * 3) + (sizeof(char) * 20));
    void *toto = *header;

    printf("\nAGENDA: \n");

    if (*tam == 0) {
        printf("VAZIA. TENTE ADICIONAR UM CONTATO NOVO\n");
    } else {
        while (toto != NULL) {
            printf("NOME: %s\n", (char*)toto + sizeof(void*));
            printf("IDADE: %d\n", *(int*)((char*)toto + sizeof(void*) + 20));
            printf("EMAIL: %s\n", (char*)((char*)toto + sizeof(void*) + 20 + sizeof(int)));
            toto = *(void**)((char*)toto + PESSOA - sizeof(void*));
        }
        printf("\n--------------------------------------------------------------------------------\n");
    }
}
