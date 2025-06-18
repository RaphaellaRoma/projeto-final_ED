// Gera dados de desempenho para BST
#include <iostream>
#include "../src/bst.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream file("results/bst_results.csv");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    file << generateCSVHeader();
    std::vector<doc> documents = read_documents("../data_new/", 10000);
    BinaryTree* tree = BST::create();
    Metrics metrics = initMetrics("bst");
    double totalSearchTime = 0.0;
    double maxSearchTime = 0.0;

    for (int numDocs = 100; numDocs <= 10000; numDocs += 100) {
        metrics.numDocuments = numDocs;

        for (int i = numDocs - 100; i < numDocs; i++) {
            const doc& document = documents[i];
            for (size_t j = 0; j < document.words.size(); j++) {
                const std::string& word = document.words[j];
                InsertResult insertRes = BST::insert(tree, word, document.id);
                SearchResult searchRes = BST::search(tree, word);
                metrics.totalInsertTime += insertRes.executionTime * 1000;
                totalSearchTime += searchRes.executionTime * 1000;
                maxSearchTime = searchRes.executionTime * 1000;

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

    BST::destroy(tree);
    file.close();
    std::cout << "Análise concluída.\n";
    return 0;
}
