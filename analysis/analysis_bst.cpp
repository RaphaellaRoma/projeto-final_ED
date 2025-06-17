// Gera dados de desempenho para BST
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "../src/bst.h"
#include "metrics.h"
#include "../src/data_new.h"

int main() {
    std::ofstream arquivo("results/bst_results.csv");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    arquivo << gerarCabecalhoCSV();
    std::vector<doc> documentos = read_documents("../data_new/", 10000);

    for (int qtdDocs = 100; qtdDocs <= 10000; qtdDocs+=100) {
        BinaryTree* arvore = BST::create();

        Metrics m;
        m.estrutura = "bst";
        m.qtdDocumentos = qtdDocs;
        m.qtdPalavras = 0;
        m.totalComparacoesInsercao = 0;
        m.totalComparacoesBusca = 0;
        m.tempoTotalInsercao = 0.0;
        m.tempoTotalBusca = 0.0;
        m.numRotacoes = 0;

        // Inserção e busca - medir tempo e comparações
        for (int i = 0; i < qtdDocs; i++) {
            const doc& documento = documentos[i];
            for (size_t j = 0; j < documento.words.size(); j++) {
                const std::string& palavra = documento.words[j];
                InsertResult res = BST::insert(arvore, palavra, documento.id);
                SearchResult res = BST::search(arvore, palavra);
                m.totalComparacoesInsercao += res.numComparisons;
                m.tempoTotalInsercao += res.executionTime;
                m.numRotacoes += res.numRotations;
                m.qtdpalavras++;
                m.totalComparacoesBusca += res.numComparisons;
                m.tempoTotalBusca += res.executionTime;
            }    
        }
        m.tempoMedioInsercao = (m.qtdpalavras > 0) ? m.tempoTotalInsercao / m.qtdpalavras : 0.0;
        m.altura = getHeight(arvore->root);
        m.menorGalho = minDeph(arvore->root);
        m.maiorGalho = m.altura;
        m.tempoMedioBusca = (m.qtdpalavras > 0) ? m.tempoTotalBusca / m.qtdpalavras : 0.0;

        arquivo << gerarLinhaCSV(m) << "\n";

        BST::destroy(arvore);

        if (qtdDocs % 1000 == 0) {
            std::cout << "Processado: " << qtdDocs << " documentos\n";
        }
    }

    arquivo.close();
    std::cout << "Análise concluída.\n";
    return 0;
}