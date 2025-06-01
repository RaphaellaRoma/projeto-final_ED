// Implementação da Árvore Binária de Busca
#ifndef BST_H
#define BST_H

namespace BST{
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
    * @brief Cria e inicializa uma árvore binária vazia.
    * 
    * @return BinaryTree* Ponteiro para a nova árvore criada. Retorna nullptr em caso de falha na alocação de memória.
    */
    BinaryTree* create();

    /**
    * @brief Insere uma palavra na árvore binária, associando-a a um ID de documento.
    * 
    * Se a palavra já existir na árvore, adiciona o ID do documento na lista de IDs, caso ainda não esteja presente.
    * Mede o tempo de execução da operação e conta o número de comparações realizadas durante a inserção.
    * 
    * @param tree Ponteiro para a árvore binária onde a palavra será inserida.
    * @param word Palavra a ser inserida.
    * @param documentId ID do documento associado à palavra.
    * @return InsertResult Estrutura contendo informações sobre a inserção:
    *         - numComparisons: número de comparações realizadas;
    *         - executionTime: tempo gasto na operação, em segundos.
    */ 
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
    * @brief Busca uma palavra na árvore binária.
    * 
    * Retorna se a palavra foi encontrada, a lista de IDs de documentos associados, o tempo de execução da busca e o número de comparações realizadas.
    * 
    * @param tree Ponteiro para a árvore binária onde será feita a busca.
    * @param word Palavra a ser buscada.
    * @return SearchResult Estrutura contendo informações sobre a busca:
    *         - found: indica se a palavra foi encontrada (true/false);
    *         - documentIds: vetor com os IDs dos documentos associados à palavra;
    *         - executionTime: tempo gasto na busca, em segundos;
    *         - numComparisons: número de comparações realizadas durante a busca.
    */
    SearchResult search(BinaryTree* tree, const std::string& word);

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