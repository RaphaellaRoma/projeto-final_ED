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

void deleteNode(Node* node, Node* NIL) {
    if (node == nullptr || node == NIL) return;
    deleteNode(node->left, NIL);
    deleteNode(node->right, NIL);

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


int minDeph(Node* root, Node* NIL) {
    if (root == NIL) return -1;

    std::vector<NodeDepth> queue;
    queue.push_back({root, 0}); // começa com profundidade 0

    while (!queue.empty()) {
        NodeDepth nd = queue.front();
        queue.erase(queue.begin()); // remove o primeiro elemento

        Node* node = nd.node;
        int depth = nd.depth;

        // Verifica se é folha: seus filhos são NIL
        if (node->left == NIL && node->right == NIL)
            return depth;

        if (node->left != NIL)
            queue.push_back({node->left, depth + 1});
        if (node->right != NIL)
            queue.push_back({node->right, depth + 1});
    }

    return -1; // Se árvore vazia ou algo errado
}

int computeNodeHeight(Node* n, Node* NIL) {
    if (n == NIL) return -1;
    return 1 + std::max(computeNodeHeight(n->left, NIL), 
                   computeNodeHeight(n->right, NIL));
}

int getHeight(Node* n, Node* NIL) {
    if (n == NIL) {
        return -1;  // Se o nó não existe, a altura é -1
    } else {
        return n->height;
    }
}    

void recomputeHeight(Node* n, Node* NIL) {
    if (n == NIL) return;

    int alturaEsquerda = getHeight(n->left, NIL);
    int alturaDireita = getHeight(n->right, NIL);
    n->height = 1 + std::max(alturaEsquerda, alturaDireita);
}

void recomputeHeightTree(Node* n, Node* NIL) {
    while (n != NIL) {
        recomputeHeight(n, NIL);
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
    if (u->parent == tree->NIL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != tree->NIL) {
        v->parent = u->parent;
    }
}

void rotateLeft(BinaryTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL) {
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
    if (x->right != tree->NIL){
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

void printIndexHelper(Node* node, int& index, Node* NIL) {
    // Se o ponteiro for NIL ou nullptr não faz nada 
    if (node == NIL) return;

    // Chamada recursiva para o filho à esquerda 
    printIndexHelper(node->left, index, NIL);


    // Imprime palavra e os IDs dos documentos 
        std::cout << index << ". " << node->word;
    // Verifica se é RBT (NIL é um nó especial, não nullptr)
    if (NIL != nullptr) { std::cout << " (" << (node->isRed ? "R" : "B") << ")";
    } std::cout << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        std::cout << node->documentIds[i];
        if (i != node->documentIds.size() - 1)
            std::cout << ", ";
    }
    std::cout << "\n"; 
    ++index;

    // Chamada recursiva para o filho à direita
    printIndexHelper(node->right, index, NIL);
}

void printIndex(BinaryTree* tree) {
    int index = 1;
    // Inicia chamando a função recursiva a partir do nó raiz 
    printIndexHelper(tree->root, index, tree->NIL);
}

void printTreeHelper(Node* node, const std::string& prefix, bool isLeft, Node* NIL) {
    // Se o nó for nulo não faz nada 
    if (node == NIL) return;

    std::cout << prefix;

    // Se o nó não tem pai, então ele é a raiz e imprime apenas a palavra 
    if (node->parent == NIL) {
        std::cout << node->word;
        if (NIL != nullptr) std::cout << " (" << (node->isRed ? "R" : "B") << ")";
        std::cout << "\n";
    } else {
        std::cout << (isLeft ? "/__" : " \\__") << node->word;
        if (NIL != nullptr) std::cout << " (" << (node->isRed ? "R" : "B") << ")";
        std::cout << "\n";
    }
    // Nova string prefixo para os filhos do nó atual 
    std::string newPrefix = prefix;
    if (node->parent != NIL){
        // Verifica se há irmãos. Em caso afirmativo, "|   " se o nó atual for da esquerda; "    " se for da direita 
        bool hasSibling = (isLeft && node->parent->right != NIL) || (!isLeft && node->parent->left != NIL);
        
        newPrefix += (isLeft ? (hasSibling ? "|   " : "    ") : "    ");
}

    // Se o nó tiver pelo menos um filho, chama recursivamente nos filhos 
    if (node->left != NIL|| node->right != NIL) {
        if (node->left)
            printTreeHelper(node->left, newPrefix, true, NIL);
        if (node->right)
            printTreeHelper(node->right, newPrefix, false, NIL);
    }
}

void printTree(BinaryTree* tree) {
    // Se a árvore estiver vazia retorna 
    if (tree->root == tree->NIL) return;
    // Inicia chamando a função recursiva a partir do nó raiz
    printTreeHelper(tree->root, "", false, tree->NIL);
}
