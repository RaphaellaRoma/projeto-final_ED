// Implementação da Árvore Rubro-Negra

#include "rbt.h"

namespace RBT{

BinaryTree* create(){
    try {
        BinaryTree* tree = new BinaryTree;

        // Cria o nó NIL
        tree->NIL = new Node{"", {}, nullptr, nullptr, nullptr, 0, 0}; // isRed = 0
        tree->NIL->left = tree->NIL;
        tree->NIL->right = tree->NIL;
        tree->NIL->parent = tree->NIL;

        tree->root = tree->NIL;

        return tree;
        } 
    catch (const std::bad_alloc&){
        std::cout << "Erro: Nao foi possivel alocar memoria para BinaryTree" << std::endl;
        return nullptr;
        }
    }

void fixUp(BinaryTree* tree, Node* node) {
    while (node->parent->isRed == 1) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle->isRed == 1) {
                // Caso 1: tio vermelho — recolorir
                node->parent->isRed = 0;
                uncle->isRed = 0;
                node->parent->parent->isRed = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Caso 2
                    node = node->parent;
                    rotateLeft(tree, node);
                }
                // Caso 3
                node->parent->isRed = 0;
                node->parent->parent->isRed = 1;
                rotateRight(tree, node->parent->parent);
            }
        } else {
            // Espelho dos casos acima
            Node* uncle = node->parent->parent->left;

            if (uncle->isRed == 1) {
                node->parent->isRed = 0;
                uncle->isRed = 0;
                node->parent->parent->isRed = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(tree, node);
                }
                node->parent->isRed = 0;
                node->parent->parent->isRed = 1;
                rotateLeft(tree, node->parent->parent);
            }
        }

        if (node == tree->root) break;
    }

    tree->root->isRed = 0;
}


InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    if (tree == nullptr) {
            throw std::invalid_argument("Erro: ponteiro para BinaryTree e nulo.");
        }
        if (word.empty()) {
            throw std::invalid_argument("Erro: palavra vazia nao pode ser inserida na arvore.");
        }
        if (documentId < 0) {
            throw std::invalid_argument("Erro: documentId invalido.");
        }
    InsertResult result;
    result.executionTime = 0.0;
    result.numComparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Node* parent = tree->NIL;
    Node* current = tree->root;

    // Busca a posição onde o novo nó será inserido
    while (current != tree->NIL) {
        result.numComparisons++;
        parent = current;

        int cmp = word.compare(current->word);
        if (cmp < 0) {
            current = current->left;
        } else if (cmp > 0) {
            current = current->right;
        } else {
            // Palavra já existe, adiciona novo documentId se não estiver presente
            bool alreadyExists = false;
            for (size_t i = 0; i < current->documentIds.size(); i++) {
                if (current->documentIds[i] == documentId) {
                    alreadyExists = true;
                    break;
                }
            }
            if (!alreadyExists) {
                current->documentIds.push_back(documentId);
            }
            auto end = std::chrono::high_resolution_clock::now();
            result.executionTime = std::chrono::duration<double>(end - start).count();
            return result;
        }
    }

    // Criação do novo nó
    Node* newNode = new Node{word, {documentId}, parent, tree->NIL, tree->NIL, 0, 1}; // isRed = 1 (vermelho)

    // Inserção na árvore
    if (parent == tree->NIL) {
        tree->root = newNode;
    } else if (word < parent->word) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Chamada para corrigir propriedades da RBT
    fixUp(tree, newNode);

    auto end = std::chrono::high_resolution_clock::now();
    result.executionTime = std::chrono::duration<double>(end - start).count();
    return result;
}


};