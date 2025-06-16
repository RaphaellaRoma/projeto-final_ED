// Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc
#include "tree_utils.h"


Node* createNode(const std::string& word, int documentId, Node* parent) {
    Node* newNode = new Node;
    newNode->word = word;
    newNode->documentIds = {documentId};
    newNode->parent = parent;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 0;
    newNode->isRed = 1;
    return newNode;
}

void deleteNode(Node* node) {
    if (node == nullptr) return;
    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

void deleteNodeRBT(Node* node, Node* NIL) {
    if (node == nullptr || node == NIL) return;

    deleteNodeRBT(node->left, NIL);
    deleteNodeRBT(node->right, NIL);

    delete node;
}

Node* searchNode(BinaryTree* tree, const std::string& word) {
    if (tree == nullptr || tree->root == tree->NIL) {
        return tree->NIL;
    }

    Node* current = tree->root;

    while (current != tree->NIL) {
        int cmp = word.compare(current->word);
        if (cmp == 0) {
            return current;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return tree->NIL; // não encontrado
}

bool check_no_red_red(Node* node, Node* NIL) {
    if (node == NIL) return true;
    if (node->isRed == 1) {
        if (node->left->isRed == 1 || node->right->isRed == 1) {
            return false;
        }
    }
    return check_no_red_red(node->left, NIL) && check_no_red_red(node->right, NIL);
}

bool check_black_height(Node* node, Node* NIL, int& blackHeight, int currentHeight) {
    if (node == NIL) {
        if (blackHeight == -1) {
            blackHeight = currentHeight;
            return true;
        }
        return currentHeight == blackHeight;
    }

    if (node->isRed == 0) currentHeight++;

    return check_black_height(node->left, NIL, blackHeight, currentHeight) &&
           check_black_height(node->right, NIL, blackHeight, currentHeight);
}

int minDeph(Node* root) {
    if (!root) return -1;

    std::vector<NodeDepth> queue;
    queue.push_back({root, 0}); // começa com profundidade 0

    while (!queue.empty()) {
        NodeDepth nd = queue.front();
        queue.erase(queue.begin()); // remove o primeiro elemento

        Node* node = nd.node;
        int deph = nd.depth;

        if (!node->left && !node->right)
            return deph;

        if (node->left)
            queue.push_back({node->left, deph + 1});
        if (node->right)
            queue.push_back({node->right, deph + 1});
    }

    return 0;
}

int getHeight(Node* n) {
    if (n == nullptr) {
        return -1; // Se o nó não existe, a altura é -1
    } else {
        return n->height; 
    }
}

void recomputeHeight(Node* n) {
    if (n == nullptr) return; 

    int alturaEsquerda = getHeight(n->left);
    int alturaDireita = getHeight(n->right);
    n->height = 1 + std::max(alturaEsquerda, alturaDireita);
}

void recomputeHeightTree(Node* n) {
    while (n!=nullptr){
        recomputeHeight(n);
        n = n->parent;
    }
}

int getBalance(Node* n) {
    if (n == nullptr) {
        return 0;
    }

    int alturaEsquerda = getHeight(n->left);
    int alturaDireita = getHeight(n->right);
    int balance = alturaEsquerda - alturaDireita;

    return balance;
}

bool isBalanced(Node* node) {
    if (node == nullptr) {
        return true; // Um nó nulo é sempre balanceado
    }

    int balance = getBalance(node);
    if (balance < -1 || balance > 1) {
        return false;
    }

    // Verifica recursivamente as subárvores esquerda e direita
    bool leftBalanced = isBalanced(node->left);
    bool rightBalanced = isBalanced(node->right);

    return leftBalanced && rightBalanced;
}

void transplant(BinaryTree* tree, Node* u, Node* v) {
    if (u->parent == nullptr) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

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
        newPrefix += (isLeft ? "|   " : "    ");

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
