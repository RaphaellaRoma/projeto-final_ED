// Implementação da Árvore Binária de Busca
#ifndef BST_H
#define BST_H

namespace bst{
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

      /**
      * @brief Cria uma nova árvore.
      * @return Uma nova árvore vazia.
      */
     BinaryTree* create() ;

    /**
    * @brief Função auxiliar para deletar a árvore, é chamada recursivamente para eliminar cada nó.
    * @param node É o nó a ser deletado.
    */
   void deleteNode(Node* node);

    /**
    * @brief Deleta toda a árvore e libera a memória.
    * @param tree É a árvore a ser deletada.
    */
     void deleteTree(BinaryTree* tree);

}

#endif