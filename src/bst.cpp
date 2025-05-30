// Implementação da Árvore Binária de Busca

#include <iostream> //import do python
#include <vector>
#include <string>
#include <bst.h>

namespace bst{
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree{};
        tree->root = nullptr;
        tree->NIL = nullptr;

        return tree;
    };

    void deleteNode(Node* node) {
        if (node == nullptr) return;
        deleteNode(node->left);
        deleteNode(node->right);

        delete node;
    }

    void deleteTree(BinaryTree* tree) {
        if (tree == nullptr) return;

        deleteNode(tree->root);
        tree->root = nullptr;
    }
}