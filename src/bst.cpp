// Implementação da Árvore Binária de Busca
#include "bst.h"

namespace BST{
    BinaryTree* create(){
    try {
        BinaryTree* tree = new BinaryTree{nullptr,nullptr};
        return tree;
        } 
    catch (const std::bad_alloc&){
        std::cout << "Erro: Nao foi possivel alocar memoria para BinaryTree" << std::endl;
        return nullptr;
        }
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
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

        Node* parent = nullptr;
        Node* current = tree->root;

        while (current != nullptr){
            result.numComparisons ++;
            parent = current;

            int cmp = word.compare(current->word);
            if(cmp < 0 ){
                current = current->left;
            }
            else if(cmp > 0){
                current = current->right;
            }
            else{
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
        
        // Cria e insere novo nó na árvore
        Node* newNode = new Node{word, {documentId}, parent, nullptr, nullptr, 0, 0};
        if(parent == nullptr){
            tree->root = newNode;
        }
        else if(word < parent->word){
            parent->left = newNode;
        }
        else if(word > parent->word){
            parent->right = newNode;
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    SearchResult search(BinaryTree* tree, const std::string& word){
        if (tree == nullptr) {
            throw std::invalid_argument("Erro: ponteiro para BinaryTree e nulo.");
        }
        if (word.empty()) {
            throw std::invalid_argument("Erro: palavra vazia nao pode ser inserida na arvore.");
        }
        SearchResult result;
        result.found = false;
        result.documentIds = {};
        result.executionTime = 0.0;
        result.numComparisons = 0;

        auto start = std::chrono::high_resolution_clock::now();
        Node* current = tree->root;

        while (current != nullptr){
            result.numComparisons ++;
            int cmp = word.compare(current->word);
            if(cmp < 0){
                current = current->left;
            }
            else if(cmp > 0){
                current = current->right;
            }
            else{
                result.found = true;
                result.documentIds = current->documentIds;
                auto end = std::chrono::high_resolution_clock::now();
                result.executionTime = std::chrono::duration<double>(end - start).count();
                return result;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        result.executionTime = std::chrono::duration<double>(end - start).count();
        return result;
    }

    void deleteNode(Node* node) {
        if (node == nullptr) return;
        deleteNode(node->left);
        deleteNode(node->right);

        delete node;
    }

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;

        deleteNode(tree->root);
        tree->root = nullptr;
    }
}
