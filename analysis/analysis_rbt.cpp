// Gera dados de desempenho para RBT
#include <iostream>
#include "../src/rbt.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream arquivo("results/rbt_results.csv");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    arquivo << gerarCabecalhoCSV();
    std::vector<doc> documentos = read_documents("../data_new/", 10000);
    BinaryTree* tree = RBT::create();
    Metrics m = iniciarMetrics("rbt");

    for (int qtdDocs = 100; qtdDocs <= 10000; qtdDocs+=100) {
        m.qtdDocumentos = qtdDocs;

        for (int i = qtdDocs - 100; i < qtdDocs; i++) {
            const doc& documento = documentos[i];
            for (size_t j = 0; j < documento.words.size(); j++) {
                const std::string& palavra = documento.words[j];
                InsertResult resInsert = RBT::insert(tree, palavra, documento.id);
                SearchResult resSearch = RBT::search(tree, palavra);
                m.totalComparacoesInsercao += resInsert.numComparisons;
                m.tempoTotalInsercao += resInsert.executionTime;
                m.numRotacoes += resInsert.numRotations;
                m.qtdPalavrasTotais++;
                if(resInsert.alreadyInsert == 0){
                    m.qtdPalavrasDist++;
                }
                m.totalComparacoesBusca += resSearch.numComparisons;
                m.tempoTotalBusca += resSearch.executionTime;
            }    
        }
        m.tempoMedioInsercao = (m.qtdPalavrasTotais > 0) ? m.tempoTotalInsercao / m.qtdPalavrasTotais : 0.0;
        m.tempoMedioBusca = (m.qtdPalavrasTotais > 0) ? m.tempoTotalBusca / m.qtdPalavrasTotais : 0.0;
        m.altura = getHeight(tree->root, tree->NIL);
        m.menorGalho = minDeph(tree->root, tree->NIL);
        m.maiorGalho = m.altura;

        arquivo << gerarLinhaCSV(m) << "\n";
        std::cout << "Processado: " << qtdDocs << " documentos\n";
    }
    
    RBT::destroy(tree);
    arquivo.close();
    std::cout << "Análise concluída.\n";
    return 0;
}