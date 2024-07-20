#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME sizeof(char)*20
#define AGE sizeof(int)
#define EMAIL sizeof(char)*20

#define PESSOA (NAME+AGE+EMAIL)
#define HEAD sizeof(int)*4 + sizeof(char)*20
#define OPTIONS sizeof(int)*2

int main(void) {

	void *pBuffer;
	void *pPessoa;
	void *pHead;

	void *pSwitch;
	void *pLoop;

	void *pNome;
	void *pAge;
	void *pEmail;

	pBuffer = malloc(HEAD + OPTIONS + PESSOA);
	if (pBuffer == NULL){
		printf("Erro em alocação de memória!");
		return 1;
	}
	pHead = pBuffer;
	pOptions = (char*)pHead + HEAD;
	pPessoa = (char*)pBuffer + HEAD + OPTIONS;

	pSwitch = (int*)pOptions;

	printf("BEM VENNIDO A AGENDINHA'S AeD\n");
    printf("1. ADICIONAR PESSOA\n2. REMOVER PESSOA\n3. PROCURAR PESSOA\n4. MOSTRAR AGENDA\n0. SAIR\n");
    scanf("%d", pSwitch);

	pNome = pPessoa;
	pAge = (char*)pPessoa + NAME;
	pEmail = (char*)pPessoa + NAME + AGE;

	strcpy((char*)pNome,"fenanda");
	*(int*)pAge = 10;
    strcpy((char*)pEmail, "shauhsuahu");

	// Exibe valores
    printf("Nome: %s\n", (char*)pNome);
    printf("Idade: %d\n", *(int*)pAge);
    printf("Email: %s\n", (char*)pEmail);

    // Limpa a memória alocada
    free(pBuffer);

    return 0;
}
