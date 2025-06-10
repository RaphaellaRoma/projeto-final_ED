// Implementação da Árvore AVL
#include "avl.h"

// falta mexer no tree_ultils e usar namespace da forma correta em algumas.
namespace AVL {

    // colocar no tree_ultils
    int getHeight(Node* n) {
        if (n == nullptr) {
            return -1; // Se o nó não existe, a altura é -1
        } else {
            return n->height; 
        }
    }

    // colocar no tree_utils 
    void recomputeHeight(Node* n) {
        if (n == nullptr) return; 

        int alturaEsquerda = getHeight(n->left);
        int alturaDireita = getHeight(n->right);
        n->height = 1 + std::max(alturaEsquerda, alturaDireita);
    }

    // criei essa função pra ver o balanceamento acho que é boa no tree_utils talvez mover para lá dps
    int getBalance(Node* n) {
        if (n == nullptr) {
            return 0;
        }

        int alturaEsquerda = getHeight(n->left);
        int alturaDireita = getHeight(n->right);
        int balance = alturaEsquerda - alturaDireita;

        return balance;
    }

    // mover para tree_utils
    void rotateLeft(BinaryTree* tree, Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }

        transplant(tree, x, y);

        y->left = x;
        x->parent = y;

        recomputeHeight(x);
        recomputeHeight(y);
    }

    // mover para o tree_utils
    void rotateRight(BinaryTree* tree, Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr){
            x->right->parent = y;
        } 

        transplant(tree, y, x);

        x->right = y;
        y->parent = x;

        recomputeHeight(y);
        recomputeHeight(x);
    }

    // tentar otimizar para não precisar percorer isso colocando mais uma condição pro while talvez
    void rebalance(BinaryTree* tree, Node* node) {
        while (node != nullptr) {
            recomputeHeight(node);
            int balance = getBalance(node);

            if (balance > 1) {
                if (getBalance(node->left) < 0) {
                    rotateLeft(tree, node->left);
                }
                rotateRight(tree, node);
            } else if (balance < -1) {
                if (getBalance(node->right) > 0) {
                    rotateRight(tree, node->right);
                }
                rotateLeft(tree, node);
            }

            node = node->parent;
        }
    }

    // provalvemente mover para o tree_utils e talvez replicar para a BST tbm usar nela
    Node* createNode(const std::string& word, int documentId, Node* parent) {
        Node* newNode = new Node;
        newNode->word = word;
        newNode->documentIds = {documentId};
        newNode->parent = parent;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0;
        newNode->isRed = 0;
        return newNode;
    }

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

    // Aqui ainda está com a implemetação antiga da BST verificar se a deleteNode também precisa preservar o balanceamento
    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;

        deleteNode(tree->root);
        tree->root = nullptr;
    }
}
