// Implementação da Árvore AVL
#include "avl.h"

namespace AVL {

    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree{nullptr, nullptr};
        return tree;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        InsertResult result{0, 0.0};
        auto start = std::chrono::high_resolution_clock::now();

        Node* parent = nullptr;
        Node* current = tree->root;

        while (current != nullptr) {
            parent = current;
            result.numComparisons++;

            if (word < current->word) {
                current = current->left;
            } else if (word > current->word) {
                current = current->right;
            } else {
            // Palavra já existe, adiciona novo documentId se não estiver presente
            bool alreadyExists = false;
            for (int i = 0; i < current->documentIds.size(); i++) {
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

        Node* newNode = createNode(word, documentId, parent);

        if (parent == nullptr) {
            tree->root = newNode;
        } else if (word < parent->word) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        rebalance(tree, newNode);

        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word) {
        SearchResult result{0, {}, 0.0, 0};
        auto start = std::chrono::high_resolution_clock::now();

        Node* current = tree->root;
        while (current != nullptr) {
            result.numComparisons++;
            if (word < current->word) {
                current = current->left;
            } else if (word > current->word) {
                current = current->right;
            } else {
                result.found = 1;
                result.documentIds = current->documentIds;
                break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;

        deleteNode(tree->root);
        tree->root = nullptr;
    }
}
