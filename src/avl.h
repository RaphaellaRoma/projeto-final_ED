// Implementação da Árvore AVL
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "tree_utils.h"


namespace AVL {

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
    * @brief Deleta toda a árvore e libera a memória.
    * @param tree É a árvore a ser deletada.
    */
    void destroy(BinaryTree* tree);

}
#endif
