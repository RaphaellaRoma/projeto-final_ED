// Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc
#include "tree_utils.h"

void printIndexHelper(Node* node, int& index) {
    // Se o ponteiro for nullptr não faz nada 
    if (!node) return;

    // Chamada recursiva para o filho à esquerda 
    printIndexHelper(node->left, index);

    // Imprime palavra e os IDs dos documentos 
    std::cout << index << ". " << node->word << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        std::cout << node->documentIds[i];
        if (i != node->documentIds.size() - 1)
            std::cout << ", ";
    }
    std::cout << "\n";
 
    ++index;

    // Chamada recursiva para o filho à direita
    printIndexHelper(node->right, index);
}

void printIndex(BinaryTree* tree) {
    int index = 1;
    // Inicia chamando a função recursiva a partir do nó raiz 
    printIndexHelper(tree->root, index);
}

void printTreeHelper(Node* node, const std::string& prefix, bool isLeft) {
    // Se o nó for nulo não faz nada 
    if (!node) return;

    std::cout << prefix;

    // Se o nó não tem pai, então ele é a raiz e imprime apenas a palavra 
    if (!node->parent) {
        std::cout << node->word << "\n";
    } else {  // Se tem pai: "|__" para filho da esquerda; "\__" para filho à direita 
        std::cout << (isLeft ? "/__" : " \\__") << node->word << "\n";
    }

    // Nova string prefixo para os filhos do nó atual 
    std::string newPrefix = prefix;
    if (node->parent)
        // "|   " se o nó atual for da esquerda; "    " se for da direita 
        newPrefix += (isLeft ? ":   " : "    ");

    // Se o nó tiver pelo menos um filho, chama recursivamente nos filhos 
    if (node->left || node->right) {
        if (node->left)
            printTreeHelper(node->left, newPrefix, true);
        if (node->right)
            printTreeHelper(node->right, newPrefix, false);
    }
}

void printTree(BinaryTree* tree) {
    // Se a árvore estiver vazia retorna 
    if (!tree->root) return;
    // Inicia chamando a função recursiva a partir do nó raiz
    printTreeHelper(tree->root, "", false);
}
