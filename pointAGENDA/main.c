#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME                sizeof(char) * 20       // Tamanho da variável nome
#define AGE                 sizeof(int)             // Tamanho da variável idade
#define EMAIL               sizeof(char) * 20       // Tamanho da variável email

#define PESSOA (NAME + AGE + EMAIL + sizeof(void*)*2)   // Tamanho de uma pessoa (nome, idade, email)
                                                        // + 2 ponteiros vazios (pPrev e pNext)

#define OPTIONS             sizeof(int)          // variável para escolha no menu
#define BUSCA               sizeof(char) * 20    // nome a ser buscado
#define CONTADOR            sizeof(int)         // variável vazia para loop no for
#define TAMANHO             sizeof(int)         // contador para o numero de ctts na agenda

#define HEAD (OPTIONS + TAMANHO + CONTADOR + BUSCA)  // Tamanho do cabeçalho (opções, tamanho, contador, busca)
#define BUFFER (HEAD + PESSOA)

void *addPessoa(void *pBuffer);
void removePessoa(void *pBuffer);
void searchPessoa(void *pBuffer);
void showPessoas(void *pBuffer);

int main(void) {
    void *pBuffer;

    // Atribuir pBuffer com HEAD e PESSOA
    pBuffer = malloc(BUFFER);
    if (pBuffer == NULL) {
        printf("Erro em alocação de memória!");
        return 1;
    }

    // Inicializar as variáveis de controle
    *(int*)(pBuffer + OPTIONS) = 0; // Opção selecionada
    *(int*)(pBuffer + TAMANHO) = 0; // Tamanho da lista (número de pessoas)
    *(int*)(pBuffer + CONTADOR) = 0; // Contador para loops
    memset(pBuffer + BUSCA, 0, 20); // Busca

    while (1) {
        // Menu de opções
        printf("BEM VINDO A AGENDINHA'S AeD\n");
        printf("1. ADICIONAR PESSOA\n");
        printf("2. REMOVER PESSOA\n");
        printf("3. PROCURAR PESSOA\n");
        printf("4. MOSTRAR AGENDA\n");
        printf("0. SAIR\n");
        scanf("%d", (int*)pBuffer);

        switch (*(int*)pBuffer) {
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
    // realloc p/ nova pessoa
    pBuffer = realloc(pBuffer, HEAD + PESSOA *(*(int*)(pBuffer + TAMANHO) + 1));
    if (pBuffer == NULL) {
        printf("Erro em alocação de memória!\n");
        exit(1);
    }

    // inicializa os ponteiros de pessoa
    void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + TAMANHO)));
    void **pPrev = (void*)pPessoa;
    void *pNome = (char*)pPessoa + sizeof(void*);
    void *pIdade = (char*)pPessoa + sizeof(void*) + NAME;
    void *pEmail = (char*)pPessoa + sizeof(void*) + NAME + AGE;
    void **pNext = (void*)pPessoa + sizeof(void*) + NAME + AGE + EMAIL;

    // Inicializa ponteiros prev e next vazios
    *pPrev = NULL;
    *pNext = NULL;

    // Adiciona a pessoa ao buffer
    printf("NOME: ");
    scanf("%s", (char*)pNome);
    printf("IDADE: ");
    scanf("%d", (int*)pIdade);
    getchar(); // Limpa o buffer de entrada
    printf("EMAIL: ");
    scanf("%s", (char*)pEmail);

    // Ordena do fim para o inicio

    // Ponteiro pCorrente recebe o ponteiro pPessoa para comparação e ordenação


    // Incrementa o contador de pessoas
    (*(int*)(pBuffer + TAMANHO))++;

    return pBuffer;
}

void removePessoa(void *pBuffer) {
    printf("Digite o nome a ser removido: ");
    scanf("%s", (char*)(pBuffer + BUSCA));

    void *pPrev = NULL; // Ponteiro para o contato anterior
    void *pPessoa = *(void**)(pBuffer + OPTIONS); // Ponteiro para o início da lista

    // Percorre a lista de pessoas
    for (*(int*)(pBuffer + OPTIONS + TAMANHO) = 0; *(int*)(pBuffer + OPTIONS + TAMANHO) < *(int*)(pBuffer + OPTIONS); (*(int*)(pBuffer + OPTIONS + TAMANHO))++) {
            void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)));
            // Verifica se a pessoa foi encontrada
            // Se pessoa nao está vazio e a busca realizada por BUSCA não retorna vazia, então retorna os dados da pessoa
            if (pPessoa != NULL && strcmp((char*)(pBuffer + BUSCA), (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)))) != 0){
                void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)));
                // pessoa é atribuida a posição anterior
                pPrev = pPessoa;
                // check se nome buscado foi atribuído de pPessoa p/ a pPrev
                printf("\nNOME: %s\n", (char*)pPrev + sizeof(void*));
                printf("IDADE: %d\n", *(int*)((char*)pPrev + sizeof(void*) + NAME));
                printf("EMAIL: %s\n", (char*)((char*)pPrev + sizeof(void*) + NAME + AGE));

                // levar pPrev ao inicio da agenda

                //eliminar pPrev e atribuir pPessoa ao slot

                // ligar os ponteiros pPrev e pNext para "tapar o buraco" do pPessoa removido

            } else {
                printf("CONTATO NÃO ENCONTRADO!\n");
            }
        }
}

void searchPessoa(void *pBuffer) {
    printf("\nDIGITE O NOME A SER BUSCADO: ");
    scanf("%s", (char*)(pBuffer + BUSCA));
    // contador percorre lista completa
    for (*(int*)(pBuffer + OPTIONS + TAMANHO) = 0; *(int*)(pBuffer + OPTIONS + TAMANHO) < *(int*)(pBuffer + OPTIONS); (*(int*)(pBuffer + OPTIONS + TAMANHO))++) {
            void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)));
            // Verifica se a pessoa foi encontrada
            // Se pessoa nao está vazio e a busca realizada por BUSCA não retorna vazia, então retorna os dados da pessoa
            if (pPessoa != NULL && strcmp((char*)(pBuffer + BUSCA), (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)))) != 0){
                printf("\nNOME: %s\n", (char*)pPessoa + sizeof(void*));
                printf("IDADE: %d\n", *(int*)((char*)pPessoa + sizeof(void*) + NAME));
                printf("EMAIL: %s\n", (char*)((char*)pPessoa + sizeof(void*) + NAME + AGE));
            } else {
                printf("CONTATO NÃO ENCONTRADO!\n");
            }
    }
}

void showPessoas(void *pBuffer) {
    printf("\t\tAGENDA: \n");
    if (*(int*)(pBuffer + OPTIONS) > 0) {
        for (*(int*)(pBuffer + OPTIONS + TAMANHO) = 0; *(int*)(pBuffer + OPTIONS + TAMANHO) < *(int*)(pBuffer + OPTIONS); (*(int*)(pBuffer + OPTIONS + TAMANHO))++) {
            void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)));
            printf("\nNOME: %s\n", (char*)pPessoa + sizeof(void*));
            printf("IDADE: %d\n", *(int*)((char*)pPessoa + sizeof(void*) + NAME));
            printf("EMAIL: %s\n", (char*)((char*)pPessoa + sizeof(void*) + NAME + AGE));
        }
        } else {
        printf("\nLISTA VAZIA!\n");
    }

    printf("\n");
}