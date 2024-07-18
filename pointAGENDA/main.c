#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições para alocação dinâmica
#define NOME (malloc(sizeof(char) * 20))
#define IDADE (malloc(sizeof(int)))
#define EMAIL (malloc(sizeof(char) * 30)) // 20 caracteres + 10 caracteres para "@hotmail.com"

// Declarações das funções e variáveis globais
void *pBuffer;
void *pPessoa;
void *pNome;
void *pIdade;
void *pEmail;

int getCadPessoas();
int sizeHead();
int sizePessoa();
void nextPessoa();
void primeiraPessoa();
char *getNome();
int *getIdade();
char *getMail();

void addPessoa();
void removePessoa();
void searchPessoa();
void showPessoas();

int main() {
    // Alocação inicial do pBuffer
    pBuffer = malloc(sizeHead());
    *(int *)(pBuffer) = 0; // Inicializa o número de operações
    *(int *)(pBuffer + 2 * sizeof(int)) = 0;

    int *pOp = malloc(sizeof(int));

    // Loop principal do programa
    do {
        printf("\n\tBienVennido a AeD's *Buffers");
        printf("\n1- Adicionar Pessoa\n2- Remover Pessoa\n3- Buscar Pessoa\n4- Listar todos\n0- Sair\n");
        scanf("%d", pOp);

        switch (*pOp) {
            case 0:
                printf("\nSAINDO . . .\n");
                break;
            case 1:
                addPessoa();
                break;
            case 2:
                removePessoa();
                break;
            case 3:
                searchPessoa();
                break;
            case 4:
                showPessoas();
                break;
            default:
                printf("\nTENTE UMA ALTERNATIVA VÁLIDA\n");
                break;
        }
    } while (*pOp != 0);

    free(pOp);
    free(pBuffer);

    return 0;
}

// Implementações das funções
int getCadPessoas() {
    return *(int *)(pBuffer + 2 * sizeof(int));
}

int sizeHead() {
    return (sizeof(int) * 3 + sizeof(char) * 20);
}

int sizePessoa() {
    return (sizeof(char) * 20 + sizeof(int) + sizeof(char) * 30);
}

void nextPessoa() {
    pPessoa += sizePessoa();
}

void primeiraPessoa() {
    pPessoa = pBuffer + sizeHead();
}

char *getNome() {
    return (char *)(pPessoa);
}

int *getIdade() {
    return (int *)(pPessoa + sizeof(char) * 20);
}

char *getMail() {
    return (char *)(pPessoa + sizeof(char) * 20 + sizeof(int));
}

void addPessoa() {
    int *nPessoas = (int *)(pBuffer + 2 * sizeof(int));
    (*nPessoas)++;

    pBuffer = realloc(pBuffer, sizeHead() + sizePessoa() * (*nPessoas));
    primeiraPessoa();

    for (int i = 0; i < (*nPessoas) - 1; i++) {
        nextPessoa();
    }

    pNome = NOME;
    pIdade = IDADE;
    pEmail = EMAIL;

    printf("Insira o nome: ");
    scanf("%s", (char *)pNome);
    memcpy(getNome(), pNome, sizeof(char) * 20);

    printf("Insira a idade: ");
    scanf("%d", (int *)pIdade);
    memcpy(getIdade(), pIdade, sizeof(int));

    printf("Insira o email: ");
    scanf("%s", (char *)pEmail);
    memcpy(getMail(), pEmail, sizeof(char) * 30);

    free(pNome);
    free(pIdade);
    free(pEmail);
    printf("CONTATO ADICIONADO!\n");
}

void removePessoa() {
    char *nome = (char *)malloc(sizeof(char) * 20);
    printf("Insira o nome que deseja remover: ");
    scanf("%s", nome);

    int *nPessoas = (int *)(pBuffer + 2 * sizeof(int));
    primeiraPessoa();

    for (int i = 0; i < (*nPessoas); i++) {
        if (strcmp(getNome(), nome) == 0) {
            (*nPessoas)--;

            if (i != (*nPessoas)) {
                memcpy(pPessoa, pPessoa + sizePessoa(), sizePessoa() * ((*nPessoas) - i));
            }

            pBuffer = realloc(pBuffer, sizeHead() + sizePessoa() * (*nPessoas));
            printf("CONTATO REMOVIDO!\n");
            free(nome);
            return;
        }
        nextPessoa();
    }

    printf("CONTATO NÃO ENCONTRADO.\n");
    free(nome);
}

void searchPessoa() {
    char *nome = (char *)malloc(sizeof(char) * 20);
    printf("Insira o nome que deseja buscar: ");
    scanf("%s", nome);

    int *nPessoas = (int *)(pBuffer + 2 * sizeof(int));
    primeiraPessoa();

    for (int i = 0; i < (*nPessoas); i++) {
        if (strcmp(getNome(), nome) == 0) {
            printf("Nome: %s | Idade: %d | Email: %s\n", getNome(), *getIdade(), getMail());
            free(nome);
            return;
        }
        nextPessoa();
    }

    printf("CONTATO NÃO ENCONTRADO.\n");
    free(nome);
}

void showPessoas() {
    int *nPessoas = (int *)(pBuffer + 2 * sizeof(int));
    primeiraPessoa();

    if (*nPessoas == 0) {
        printf("SEM CONTATOS AGENDADOS.\n");
        return;
    }

    for (int i = 0; i < (*nPessoas); i++) {
        printf("NOME: %s \t| IDADE: %d \t| EMAIL: %s\n", getNome(), *getIdade(), getMail());
        nextPessoa();
    }
}
