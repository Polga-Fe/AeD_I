#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actions.h"

int main() {

    char *pBuffer = NULL;
    int *size = malloc(sizeof(int));
    *size = 0;
    int *choice = malloc(sizeof(int));
    char *name = malloc(100 * sizeof(char));

    if (size == NULL || choice == NULL || name == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    do {
        printf("\t\tBIEN VENIDO A AeD'S AGENDAAA\n");
        printf("1. Inserir nome\n");
        printf("2. Remover nome\n");
        printf("3. Imprimir agenda\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", choice);
        getchar(); // Limpa o buffer do teclado

        switch (*choice) {
            case 1:
                printf("Digite o nome a ser inserido: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove o newline do fgets
                addCtt(&pBuffer, size, name);
                break;
            case 2:
                printf("Digite o nome a ser removido: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove o newline do fgets
                removeCtt(&pBuffer, size, name);
                break;
            case 3:
                Agenda(pBuffer);
                break;
            case 4:
                free(pBuffer);
                free(size);
                free(choice);
                free(name);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (*choice != 4);

    return 0;
}
