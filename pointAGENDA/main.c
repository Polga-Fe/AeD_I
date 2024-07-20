#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME sizeof(char) * 20    // Tamanho da variável nome
#define AGE sizeof(int)           // Tamanho da variável idade
#define EMAIL sizeof(char) * 20   // Tamanho da variável email

#define PESSOA (NAME + AGE + EMAIL)  // Tamanho de uma pessoa (nome, idade, email)

#define OPTIONS sizeof(int)
#define BUSCA sizeof(char) * 20
#define CONTADOR sizeof(int)
#define TAMANHO sizeof(int)

#define HEAD (OPTIONS + TAMANHO + CONTADOR + BUSCA)  // Tamanho do cabeçalho (opções, tamanho, contador, busca)
#define BUFFER (HEAD + PESSOA)

void *addPessoa(void *pBuffer);
void removePessoa();
void searchPessoa();
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
        printf("Digite sua opção: ");
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
                removePessoa();
                break;
            case 3:
                searchPessoa();
                break;
            case 4:
                showPessoas(pBuffer);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }

    free(pBuffer);
    return 0;
}

void *addPessoa(void *pBuffer) {
    void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + TAMANHO)));
    void *pNome = pPessoa;
    void *pIdade = (char*)pPessoa + NAME;
    void *pEmail = (char*)pPessoa + NAME + AGE;

    // Adiciona a pessoa ao buffer
    printf("NOME: ");
    scanf("%s", (char*)pNome);
    printf("IDADE: ");
    scanf("%d", (int*)pIdade);
    getchar(); // Limpa o buffer de entrada
    printf("EMAIL: ");
    scanf("%s", (char*)pEmail);

    // Incrementa o contador de pessoas
    (*(int*)(pBuffer + TAMANHO))++;

    return pBuffer;
}

void removePessoa() {
    printf("EM BREVE: REMOVE.\n");
}

void searchPessoa() {
    printf("EM BREVE: BUSCA.\n");
}

void showPessoas(void *pBuffer) {
    printf("\t\tAGENDA: \n");

    if (*(int*)(pBuffer + OPTIONS) > 0) {
        for (*(int*)(pBuffer + OPTIONS + TAMANHO) = 0; *(int*)(pBuffer + OPTIONS + TAMANHO) < *(int*)(pBuffer + OPTIONS); (*(int*)(pBuffer + OPTIONS + TAMANHO))++) {
            void *pPessoa = (char*)pBuffer + HEAD + (PESSOA * (*(int*)(pBuffer + OPTIONS + TAMANHO)));
            printf("\nNome: %s\n", (char*)pPessoa);
            printf("Idade: %d\n", *(int*)((char*)pPessoa + NAME));
            printf("Email: %s\n", (char*)((char*)pPessoa + NAME + AGE));
        }
        } else {
        printf("\nA lista está vazia!\n");
    }

    printf("\n");
}
