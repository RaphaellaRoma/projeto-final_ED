// Implementação da Árvore Rubro-Negra
#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "tree_utils.h"

namespace RBT{

    /**
    * @brief Cria e inicializa uma árvore binária vazia.
    * 
    * @return BinaryTree* Ponteiro para a nova árvore criada. Retorna nullptr em caso de falha na alocação de memória.
    */
    BinaryTree* create();


    /**
    * @brief Corrige a árvore para manter as propriedades da RBT.
    * 
    * Se a palavra já existir na árvore, adiciona o ID do documento na lista de IDs, caso ainda não esteja presente.
    * Mede o tempo de execução da operação e conta o número de comparações realizadas durante a inserção.
    * 
    * @param tree Ponteiro para a árvore binária onde a palavra será inserida.
    * @param node Nó inserido.
    */ 
    void fixUp(BinaryTree* tree, Node* node);


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

}

#endif