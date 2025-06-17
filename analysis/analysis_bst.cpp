// Gera dados de desempenho para BST
#include <iostream>
#include "../src/bst.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream arquivo("results/bst_results.csv");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    arquivo << gerarCabecalhoCSV();
    std::vector<doc> documentos = read_documents("../data_new/", 10000);
    BinaryTree* tree = BST::create();
    Metrics m = iniciarMetrics("bst");

    for (int qtdDocs = 100; qtdDocs <= 10000; qtdDocs+=100) {
        m.qtdDocumentos = qtdDocs;

        for (int i = qtdDocs - 100; i < qtdDocs; i++) {
            const doc& documento = documentos[i];
            for (size_t j = 0; j < documento.words.size(); j++) {
                const std::string& palavra = documento.words[j];
                InsertResult resInsert = BST::insert(tree, palavra, documento.id);
                SearchResult resSearch = BST::search(tree, palavra);
                m.totalComparacoesInsercao += resInsert.numComparisons;
                m.tempoTotalInsercao += resInsert.executionTime;
                m.numRotacoes += resInsert.numRotations;
                if(resInsert.alreadyInsert == 0){
                    m.qtdPalavras++;
                }
                m.totalComparacoesBusca += resSearch.numComparisons;
                m.tempoTotalBusca += resSearch.executionTime;
            }    
        }
        m.tempoMedioInsercao = (m.qtdPalavras > 0) ? m.tempoTotalInsercao / m.qtdPalavras : 0.0;
        m.tempoMedioBusca = (m.qtdPalavras > 0) ? m.tempoTotalBusca / m.qtdPalavras : 0.0;
        m.altura = getHeight(tree->root);
        m.menorGalho = minDeph(tree->root);
        m.maiorGalho = m.altura;

        arquivo << gerarLinhaCSV(m) << "\n";
        std::cout << "Processado: " << qtdDocs << " documentos\n";
    }
    
    BST::destroy(tree);
    arquivo.close();
    std::cout << "Análise concluída.\n";
    return 0;
}