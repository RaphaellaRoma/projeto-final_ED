// Implementação da Árvore AVL
#include "avl.h"

namespace AVL {

    BinaryTree* create() {
    try {
        BinaryTree* tree = new BinaryTree{nullptr,nullptr};
        return tree;
        } 
    catch (const std::bad_alloc&) {
        std::cout << "Erro: Nao foi possivel alocar memoria para BinaryTree" << std::endl;
        return nullptr;
        }
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

        InsertResult result{0, 0.0, 0, 0};
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
            for (size_t i = 0; i < current->documentIds.size(); i++) {
                if (current->documentIds[i] == documentId) {
                    alreadyExists = true;
                    break;
                }
            }
            if (!alreadyExists) {
                current->documentIds.push_back(documentId);
            }
            result.alreadyInsert = 1;
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

        result.numRotations = rebalance(tree, newNode);
        result.alreadyInsert = 0;
        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word) {
        if (tree == nullptr) {
            throw std::invalid_argument("Erro: ponteiro para BinaryTree e nulo.");
        }
        if (word.empty()) {
            throw std::invalid_argument("Erro: palavra vazia nao pode ser inserida na arvore.");
        }
        
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
