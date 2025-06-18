#ifndef METRICS_H
#define METRICS_H

#include <iostream>
#include <string>

struct Metrics {
    std::string structure;               // Nome da estrutura (ex: "avl", "bst", "rbt")
    int numDocuments;                    // Quantidade de documentos processados
    int totalWords;                      // Número total de palavras (considerando repetições)
    int distinctWords;                   // Número total de palavras inseridas (sem repetição)
    double totalInsertTime;              // Tempo total gasto em inserções (em milisegundos)
    double avgInsertTime;                // Tempo médio por inserção (em milisegundos)
    double maxSearchTime;                // Tempo máximo gasto em buscas (em milisegundos)
    double avgSearchTime;                // Tempo médio por busca (em milisegundos)
    int height;                          // Altura da árvore ao final da execução
    int minBranch;                       // Menor profundidade entre a raiz e uma folha
    int maxBranch;                       // Maior profundidade (igual à altura)
    int totalInsertComparisons;          // Número total de comparações realizadas em inserções
    int totalSearchComparisons;          // Número total de comparações realizadas em buscas
    int numRotations;                    // Número total de rotações realizadas (específico da AVL)
};


/**
 * @brief Inicializa uma estrutura Metrics com valores padrão para uma dada estrutura.
 * 
 * @param estrutura Nome da estrutura sendo analisada (ex: "avl").
 * @return Estrutura Metrics inicializada.
 */
Metrics initMetrics(const std::string& structure);


/**
 * @brief Gera a primeira linha (cabeçalho) do arquivo CSV com os nomes das colunas.
 * 
 * @return Uma string contendo os nomes das métricas separadas por vírgula.
 */
std::string generateCSVHeader();


/**
 * @brief Converte os dados de uma estrutura Metrics em uma linha CSV formatada.
 * 
 * @param m Estrutura Metrics preenchida.
 * @return Uma string com os valores das métricas separados por vírgula.
 */
std::string generateCSVRow(const Metrics& m);

#endif



