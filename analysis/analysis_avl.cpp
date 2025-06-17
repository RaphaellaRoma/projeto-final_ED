// Gera dados de desempenho para AVL
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "../src/avl.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream arquivo("results/avl_results.csv");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    arquivo << gerarCabecalhoCSV();
    std::vector<doc> documentos = read_documents("../data_new/", 10000);

    for (int qtdDocs = 100; qtdDocs <= 10000; qtdDocs+=100) {
        BinaryTree* arvore = AVL::create();

        Metrics m;
        m.estrutura = "avl";
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
                InsertResult resInsert = AVL::insert(arvore, palavra, documento.id);
                SearchResult resSearch = AVL::search(arvore, palavra);
                m.totalComparacoesInsercao += resInsert.numComparisons;
                m.tempoTotalInsercao += resInsert.executionTime;
                m.numRotacoes += resInsert.numRotations;
                m.qtdPalavras++;
                m.totalComparacoesBusca += resSearch.numComparisons;
                m.tempoTotalBusca += resSearch.executionTime;
            }    
        }
        m.tempoMedioInsercao = (m.qtdPalavras > 0) ? m.tempoTotalInsercao / m.qtdPalavras : 0.0;
        m.altura = getHeight(arvore->root);
        m.menorGalho = minDeph(arvore->root);
        m.maiorGalho = m.altura;
        m.tempoMedioBusca = (m.qtdPalavras > 0) ? m.tempoTotalBusca / m.qtdPalavras : 0.0;

        arquivo << gerarLinhaCSV(m) << "\n";

        AVL::destroy(arvore);

        if (qtdDocs % 1000 == 0) {
            std::cout << "Processado: " << qtdDocs << " documentos\n";
        }
    }

    arquivo.close();
    std::cout << "Análise concluída.\n";
    return 0;
}


