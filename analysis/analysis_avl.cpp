// Gera dados de desempenho para AVL
#include <iostream>
#include "../src/avl.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream file("results/avl_results.csv");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    file << generateCSVHeader();
    std::vector<doc> documents = read_documents("../data_new/", 10000);
    BinaryTree* tree = AVL::create();
    Metrics metrics = initMetrics("avl");
    double totalSearchTime = 0.0;
    double maxSearchTime = 0.0;

    for (int numDocs = 100; numDocs <= 10000; numDocs += 100) {
        metrics.numDocuments = numDocs;

        for (int i = numDocs - 100; i < numDocs; i++) {
            const doc& document = documents[i];
            for (size_t j = 0; j < document.words.size(); j++) {
                const std::string& word = document.words[j];
                InsertResult insertRes = AVL::insert(tree, word, document.id);
                SearchResult searchRes = AVL::search(tree, word);
                metrics.totalInsertTime += insertRes.executionTime;
                totalSearchTime += searchRes.executionTime;
                maxSearchTime = searchRes.executionTime;

                if (metrics.maxSearchTime < maxSearchTime) {
                    metrics.maxSearchTime = maxSearchTime;
                }

                metrics.totalWords++;
                if (insertRes.alreadyInsert == 0) {
                    metrics.distinctWords++;
                }

                metrics.numRotations += insertRes.numRotations;
                metrics.totalSearchComparisons += searchRes.numComparisons;
            }
        }

        metrics.avgInsertTime = (metrics.totalWords > 0) ? metrics.totalInsertTime / metrics.totalWords : 0.0;
        metrics.avgSearchTime = (metrics.totalWords > 0) ? totalSearchTime / metrics.totalWords : 0.0;
        metrics.height = getHeight(tree->root, tree->NIL);
        metrics.minBranch = minDeph(tree->root, tree->NIL);
        metrics.maxBranch = metrics.height;

        file << generateCSVRow(metrics) << "\n";
        std::cout << "Processado: " << numDocs << " documentos\n";
    }

    AVL::destroy(tree);
    file.close();
    std::cout << "Análise concluída.\n";
    return 0;
}


