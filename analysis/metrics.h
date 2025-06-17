//Este módulo define a estrutura de dados usada para armazenar estatísticas como tempo de inserção e busca, número de comparações, altura da árvore, entre outros, durante a análise de desempenho de estruturas como AVL, BST e RBT.

#ifndef METRICS_H
#define METRICS_H

#include <iostream>
#include <string>

struct Metrics {
    std::string estrutura;              // Nome da estrutura (ex: "avl", "bst", "rbt")
    int qtdDocumentos;                  // Quantidade de documentos processados
    int qtdPalavras;                    // Número total de palavras inseridas (sem repetição)
    double tempoTotalInsercao;          // Tempo total gasto em inserções (em segundos)
    double tempoMedioInsercao;          // Tempo médio por inserção (em segundos)
    double tempoTotalBusca;             // Tempo total gasto em buscas (em segundos)
    double tempoMedioBusca;             // Tempo médio por busca (em segundos)
    int altura;                         // Altura da árvore ao final da execução
    int menorGalho;                     // Menor profundidade entre a raiz e uma folha
    int maiorGalho;                     // Maior profundidade (igual à altura)
    int totalComparacoesInsercao;       // Número total de comparações realizadas em inserções
    int totalComparacoesBusca;          // Número total de comparações realizadas em buscas
    int numRotacoes;                    // Número total de rotações realizadas (específico da AVL)
};


/**
 * @brief Inicializa uma estrutura Metrics com valores padrão para uma dada estrutura.
 * 
 * @param estrutura Nome da estrutura sendo analisada (ex: "avl").
 * @return Estrutura Metrics inicializada.
 */
Metrics iniciarMetrics(const std::string& estrutura);


/**
 * @brief Gera a primeira linha (cabeçalho) do arquivo CSV com os nomes das colunas.
 * 
 * @return Uma string contendo os nomes das métricas separadas por vírgula.
 */
std::string gerarCabecalhoCSV();


/**
 * @brief Converte os dados de uma estrutura Metrics em uma linha CSV formatada.
 * 
 * @param m Estrutura Metrics preenchida.
 * @return Uma string com os valores das métricas separados por vírgula.
 */
std::string gerarLinhaCSV(const Metrics& m);

#endif




