#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "actions.h"
/*
typedef struct Agenda{
    char *nome;
    int *tell;
}Agenda;
*/

void Agenda(char *pBuffer){
    printf("\t\tAGENDA: \n");
    if (pBuffer != NULL && strlen(pBuffer) > 0) {
        printf("%s", pBuffer);
    } else {
        printf("A agenda está vazia.\n");
    }
}

void addCtt(char **pBuffer, int *size, char *name){
    *size += strlen(name) + 1; //tam do buffer cresce conforme add nomes
    *pBuffer = realloc(*pBuffer, *size); //realoca o tamanho de *pBuff para *size

    if (*pBuffer == NULL) {
        printf("ERROR!\n");
        exit(1);
    }
    strcat(*pBuffer, name); //adiciona novo nome em *pBuffer
    strcat(*pBuffer, "\n"); //adiciona nova linha em *pBuffer
}

void removeCtt(char **pBuffer, int *size, char *name){
    char *pos = strstr(*pBuffer, name);
    if (pos != NULL) {
        int len = strlen(name) + 1;
        memmove(pos, pos + len, *size - (pos - *pBuffer) - len + 1);
        *size -= len;
        *pBuffer = realloc(*pBuffer, *size);

        if (*pBuffer == NULL && *size > 0) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
    } else {
        printf("Nome não encontrado.\n");
    }
}
