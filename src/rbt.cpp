// Implementação da Árvore Rubro-Negra

#include "rbt.h"

namespace RBT{

    BinaryTree* create(){
        try {
            BinaryTree* tree = new BinaryTree;

            // Cria o nó NIL
            tree->NIL = new Node{"", {}, nullptr, nullptr, nullptr, -1, 0}; // isRed = 0
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

    int fixUp(BinaryTree* tree, Node* node) {
        int numRotations = 0;
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
                        numRotations++;
                    }
                    // Caso 3
                    node->parent->isRed = 0;
                    node->parent->parent->isRed = 1;
                    rotateRight(tree, node->parent->parent);
                    numRotations++;
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
                        numRotations++;
                    }
                    node->parent->isRed = 0;
                    node->parent->parent->isRed = 1;
                    rotateLeft(tree, node->parent->parent);
                    numRotations++;
                }
            }

            if (node == tree->root) break;
        }

        tree->root->isRed = 0;
        return numRotations;
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
        result.alreadyInsert = 0;
        result.numRotations = 0;

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
                result.alreadyInsert = 1;
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
        result.numRotations = fixUp(tree, newNode);
        recomputeHeightAll(tree->root, tree->NIL);

        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word) {
        SearchResult result{0, {}, 0.0, 0};
        // Inicia a contagem do tempo de execução
        auto start = std::chrono::high_resolution_clock::now();

        // Começa a busca a partir da raiz
        Node* current = tree->root;
        while (current != tree->NIL) {
            result.numComparisons++;
            if (word < current->word) {
                current = current->left;  // Palavra procurada está à esquerda
            } else if (word > current->word) {
                current = current->right;  // Palavra procurada está à direita
            } else {
                // Palavra encontrada
                result.found = 1;
                result.documentIds = current->documentIds;
                break;
            }
        }

        // Finaliza a contagem do tempo de execução
        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;

        // Libera todos os nós da árvore, exceto o nó NIL
        deleteNode(tree->root, tree->NIL);

        // Libera explicitamente o nó NIL, que é compartilhado
        if (tree->NIL) {
            delete tree->NIL;
        }

        delete tree;
    }

};