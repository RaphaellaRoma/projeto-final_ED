// Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc
#pragma once
#include <iostream>
#include <vector>
#include <string>


struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
};

struct InsertResult {
    int numComparisons;
    double executionTime;
    //<Possíveis outras variáveis>
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    //<Possíveis outras variáveis>
};

/**
* @brief Função auxiliar para deletar a árvore, é chamada recursivamente para eliminar cada nó.
* @param node É o nó a ser deletado.
*/
void deleteNode(Node* node);


/**
 * @brief Função auxilar que troca um nó u por um nó v.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param u Ponteiro para o nó que queremos trocar por v.
 * @param v Nó que queremos colocar no lugar de u.
 */
void transplant(BinaryTree* tree, Node* u, Node* v);


/**
 * @brief Função auxilar para buscar um nó na árvore.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param word Palavra buscada.
 */
Node* search(BinaryTree* tree, const std::string& word);


/**
 * @brief Função recursiva auxilar para imprimir o índice invertido.
 *
 * @param node Ponteiro para o nó atual na árvore binária.
 * @param index Número de ordem da palavra (usado para numerar a saída).
 */
void printIndexHelper(Node* node, int& index);


/**
 * @brief Imprime o índice invertido da árvore em ordem alfabética.
 * 
 * Cada linha contém uma palavra da árvore seguida pelos 
 * IDs dos documentos em que ela aparece.
 *
 * Exemplo de saída:
 * 1. Algoritmo: 2, 3, 5
 * 2. Binário: 1, 10
 * ...
 *
 * @param tree Ponteiro para a árvore binária.
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Função auxiliar recursiva para imprimir a árvore com indentação.
 *
 * @param node Ponteiro para o nó atual na árvore binária.
 * @param prefix Prefixo de indentação acumulado.
 * @param isLeft Indica se o nó atual é filho à esquerda.
 */
void printTreeHelper(Node* node, const std::string& prefix, bool isLeft);

/**
 * @brief Imprime visualmente a estrutura da árvore.
 *
 * A árvore é exibida com indentação e ramificações que indicam 
 * a hierarquia entre os nós (pai-filho).
 *
 * Exemplo de saída:
 * algoritmo
 * |__arvore
 *    \__memoria
 *
 * @param tree Ponteiro para a árvore binária.
 */
void printTree(BinaryTree* tree); 