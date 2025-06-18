#include <iostream>
#include "../src/bst.h"
#include "../src/avl.h"
#include "../src/rbt.h"
#include "metrics.h"
#include "../src/data.h"

int main() {
    std::ofstream file("results/general_results.csv");

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de saída.\n";
        return 1;
    }

    file << generateCSVHeader();
    std::vector<doc> documents = read_documents("../data_new/", 100);


    BinaryTree* treeBST = BST::create();
    BinaryTree* treeAVL = AVL::create();
    BinaryTree* treeRBT = RBT::create();

    Metrics metricsBST = initMetrics("bst");
    Metrics metricsAVL = initMetrics("avl");
    Metrics metricsRBT = initMetrics("rbt");

    double totalSearchTimeBST = 0.0, maxSearchTimeBST = 0.0;
    double totalSearchTimeAVL = 0.0, maxSearchTimeAVL = 0.0;
    double totalSearchTimeRBT = 0.0, maxSearchTimeRBT = 0.0;

    for (int numDocs = 1; numDocs <= 100; numDocs++) {

        metricsBST.numDocuments = numDocs;
        metricsAVL.numDocuments = numDocs;
        metricsRBT.numDocuments = numDocs;

        for (int i = numDocs - 1; i < numDocs; i++) {
            const doc& document = documents[i];
            for (const std::string& word : document.words) {
                // BST
                InsertResult insertBST = BST::insert(treeBST, word, document.id);
                SearchResult searchBST = BST::search(treeBST, word);
                metricsBST.totalInsertTime += insertBST.executionTime * 1000;
                totalSearchTimeBST += searchBST.executionTime * 1000;
                maxSearchTimeBST = std::max(maxSearchTimeBST, searchBST.executionTime * 1000);
                metricsBST.totalWords++;
                if (!insertBST.alreadyInsert) metricsBST.distinctWords++;
                metricsBST.totalInsertComparisons += insertBST.numComparisons;
                metricsBST.totalSearchComparisons += searchBST.numComparisons;

                // AVL
                InsertResult insertAVL = AVL::insert(treeAVL, word, document.id);
                SearchResult searchAVL = AVL::search(treeAVL, word);
                metricsAVL.totalInsertTime += insertAVL.executionTime * 1000;
                totalSearchTimeAVL += searchAVL.executionTime * 1000;
                maxSearchTimeAVL = std::max(maxSearchTimeAVL, searchAVL.executionTime * 1000);
                metricsAVL.totalWords++;
                if (!insertAVL.alreadyInsert) metricsAVL.distinctWords++;
                metricsAVL.numRotations += insertAVL.numRotations;
                metricsAVL.totalInsertComparisons += insertAVL.numComparisons;
                metricsAVL.totalSearchComparisons += searchAVL.numComparisons;

                // RBT
                InsertResult insertRBT = RBT::insert(treeRBT, word, document.id);
                SearchResult searchRBT = RBT::search(treeRBT, word);
                metricsRBT.totalInsertTime += insertRBT.executionTime * 1000;
                totalSearchTimeRBT += searchRBT.executionTime * 1000;
                maxSearchTimeRBT = std::max(maxSearchTimeRBT, searchRBT.executionTime * 1000);
                metricsRBT.totalWords++;
                if (!insertRBT.alreadyInsert) metricsRBT.distinctWords++;
                metricsRBT.numRotations += insertRBT.numRotations;
                metricsRBT.totalInsertComparisons += insertRBT.numComparisons;
                metricsRBT.totalSearchComparisons += searchRBT.numComparisons;
            }
        }

        auto finalize_metrics = [](Metrics& m, BinaryTree* tree, double totalSearchTime, double maxSearchTime) {
            m.avgInsertTime = (m.totalWords > 0) ? m.totalInsertTime / m.totalWords : 0.0;
            m.avgSearchTime = (m.totalWords > 0) ? totalSearchTime / m.totalWords : 0.0;
            m.maxSearchTime = maxSearchTime;
            m.height = getHeight(tree->root, tree->NIL);
            m.minBranch = minDeph(tree->root, tree->NIL);
            m.maxBranch = m.height;
        };

        finalize_metrics(metricsBST, treeBST, totalSearchTimeBST, maxSearchTimeBST);
        finalize_metrics(metricsAVL, treeAVL, totalSearchTimeAVL, maxSearchTimeAVL);
        finalize_metrics(metricsRBT, treeRBT, totalSearchTimeRBT, maxSearchTimeRBT);

        file << generateCSVRow(metricsBST) << "\n";
        file << generateCSVRow(metricsAVL) << "\n";
        file << generateCSVRow(metricsRBT) << "\n";

        std::cout << "Processado: " << numDocs << " documentos\n";
    }

    BST::destroy(treeBST);
    AVL::destroy(treeAVL);
    RBT::destroy(treeRBT);
    file.close();
    std::cout << "Análise geral concluída.\n";
    return 0;
}
