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
    Node* NIL;  // usado na RBT 
};

struct InsertResult {
    int numComparisons;
    double executionTime;
    bool alreadyInsert; // 1 se a palavra já existia, 0 se foi criada
    int numRotations;
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

struct NodeDepth {
    Node* node;
    int depth;
};


/**
 * @brief Cria e inicializa um novo nó com a palavra e o ID do documento.
 *
 * @param word Palavra a ser inserida no nó.
 * @param documentId ID do documento onde a palavra aparece.
 * @param parent Ponteiro para o nó pai (pode ser nullptr).
 * @return Ponteiro para o novo nó criado.
 */
Node* createNode(const std::string& word, int documentId, Node* parent);


/**
 * @brief Função auxiliar para deletar a árvore, é chamada recursivamente para eliminar cada nó.
 * @param node É o nó a ser deletado.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 */
void deleteNode(Node* node, Node* NIL = nullptr);


/**
 * @brief Função auxilar para buscar um nó na árvore.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param word Palavra buscada.
 */
Node* searchNode(BinaryTree* tree, const std::string& word);

/**
 * @brief Função auxiliar para verificar se a Rubro-Negra possui alguma violação da propriedade de nós vermelhos.
 *
 * @param node Ponteiro para o nó atual sendo verificado.
 * @param NIL Ponteiro para o nó sentinela NIL da árvore (nó folha padrão da RBT).
 */
bool check_no_red_red(Node* node, Node* NIL);

/**
 * @brief Função auxiliar para verificar se a Rubro-Negra possui altura preta consistente.
 *
 * @param node Ponteiro para o nó atual sendo verificado.
 * @param NIL Ponteiro para o nó sentinela NIL da árvore.
 * @param blackHeight Referência para armazenar a altura preta encontrada no primeiro caminho até uma folha.
 * @param currentHeight Contador acumulado de nós pretos no caminho atual.
 */
bool check_black_height(Node* node, Node* NIL, int& blackHeight, int currentHeight = 0);

/**
 * @brief Retorna a menor profundidade.
 *
 * @param root Ponteiro para a raiz.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 * @return Profundidade do nó, ou -1 se for nullptr.
 */

int minDeph(Node* root, Node* NIL = nullptr);


/**
 * @brief Retorna a altura de um nó.
 *
 * @param n Ponteiro para o nó.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 * @return Altura do nó, ou -1 se for nullptr.
 */
int getHeight(Node* n, Node* NIL = nullptr);


/**
 * @brief Recalcula a altura de um nó com base nas alturas dos filhos.
 *
 * @param n Ponteiro para o nó cuja altura será atualizada.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 */
void recomputeHeight(Node* n, Node* NIL = nullptr);

/**
 * @brief Recalcula a altura de todos os nós da árvore, de baixo para cima.
 *
 * @param n nó que foi inserido.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 */
void recomputeHeightTree(Node* n, Node* NIL = nullptr);

/**
 * @brief Recalcula a altura apenas se for necessário.
 *
 * @param n nó que foi inserido.
 * @param NIL Ponteiro para o NIL, caso ele exista.
 */
void recomputeHeightTreeIfNeeded(Node* n, Node* NIL);

/**
 * @brief Calcula o fator de balanceamento de um nó.
 *
 * O fator de balanceamento é a diferença entre a altura da subárvore esquerda e direita.
 *
 * @param n Ponteiro para o nó.
 * @return Valor do balanceamento. Pode ser negativo, positivo ou zero.
 */
int getBalance(Node* n);

/**
 * @brief Função auxilar que confere se a árvore está balanceada.
 *
 * @param node Ponteiro para a o nó atual da árvore binária.
 */
bool isBalanced(Node* node);


/**
 * @brief Função auxilar que troca um nó u por um nó v.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param u Ponteiro para o nó que queremos trocar por v.
 * @param v Nó que queremos colocar no lugar de u.
 */
void transplant(BinaryTree* tree, Node* u, Node* v);


/**
 * @brief Realiza uma rotação à esquerda na subárvore com raiz em x.
 *
 * Utilizada nas operações de balanceamento da AVL e da RBT.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param x Nó a partir do qual a rotação será feita.
 */
void rotateLeft(BinaryTree* tree, Node* x);


/**
 * @brief Realiza uma rotação à direita na subárvore com raiz em y.
 *
 * Utilizada nas operações de balanceamento da AVL e da RBT.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param y Nó a partir do qual a rotação será feita.
 */
void rotateRight(BinaryTree* tree, Node* y);


/**
 * @brief Rebalanceia a árvore AVL a partir de um nó inserido ou deletado.
 *
 * Realiza rotações e atualiza alturas conforme necessário.
 *
 * @param tree Ponteiro para a árvore binária.
 * @param node Ponteiro para o nó onde o rebalanceamento começará.
 * @return Número de rotações.
 */
int rebalance(BinaryTree* tree, Node* node);


/**
 * @brief Função recursiva auxilar para imprimir o índice invertido.
 *
 * @param node Ponteiro para o nó atual na árvore binária.
 * @param index Número de ordem da palavra (usado para numerar a saída).
 * @param NIL Ponteiro para o NIL, caso ele exista.
 */
void printIndexHelper(Node* node, int& index, Node* NIL = nullptr);


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
 * @param NIL Ponteiro para o NIL, caso ele exista.
 * @param isLeft Indica se o nó atual é filho à esquerda.
 */
void printTreeHelper(Node* node, const std::string& prefix, bool isLeft, Node* NIL = nullptr);


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