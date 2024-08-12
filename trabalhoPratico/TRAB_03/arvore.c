#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da árvore binária
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Função para calcular a profundidade de um nó
int maxDepth(struct TreeNode* node) {
    if (node == NULL){
        return 0;
    }

    int pEsquerdo = maxDepth(node->left);
    int pDireito = maxDepth(node->right);

    if (pEsquerdo > pDireito){
        node = pEsquerdo;
    } else {
        node = pDireito;
    }

    return 1 + node;
}

// Função principal para encontrar a menor subárvore que contenha todos os nós mais profundos
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    if (root == NULL){
        return NULL;
    }
    int pEsquerdo = maxDepth(root->left);
    int pDireito = maxDepth(root->right);

    // Se as profundidades dos filhos são iguais, o nó atual é a menor subárvore
    if (pEsquerdo == pDireito) {
        return root;
    }
    // Se a subárvore esquerda for mais profunda
    else if (pEsquerdo > pDireito) {
        return subtreeWithAllDeepest(root->left);
    }
    // Se a subárvore direita for mais profunda
    else {
        return subtreeWithAllDeepest(root->right);
    }
}
