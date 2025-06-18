// Funções utilitárias de coleta e salvamento de métricas
#include "metrics.h"

Metrics initMetrics(const std::string& structure) {
    Metrics m;
    m.structure = structure;
    m.numDocuments = 0;
    m.totalWords = 0;
    m.distinctWords = 0;
    m.totalInsertTime = 0.0;
    m.avgInsertTime = 0.0;
    m.maxSearchTime = 0.0;
    m.avgSearchTime = 0.0;
    m.height = 0;
    m.minBranch = 0;
    m.maxBranch = 0;
    m.totalInsertComparisons = 0;
    m.totalSearchComparisons = 0;
    m.numRotations = 0;
    return m;
}

std::string generateCSVHeader() {
    return "Estrutura,Documentos,NumeroPalavrasTotais,NumeroPalavrasDistintas,TempoTotalInsercao,TempoMedioInsercao,TempoMaxBusca,TempoMedioBusca,Altura,MenorGalho,MaiorGalho,ComparacoesInsercao,ComparacoesBusca,NumeroRotacao\n";
}

std::string generateCSVRow(const Metrics& m) {
    return m.structure + "," +
           std::to_string(m.numDocuments) + "," +
           std::to_string(m.totalWords) + "," +
           std::to_string(m.distinctWords) + "," +
           std::to_string(m.totalInsertTime) + "," +
           std::to_string(m.avgInsertTime) + "," +
           std::to_string(m.maxSearchTime) + "," +
           std::to_string(m.avgSearchTime) + "," +
           std::to_string(m.height) + "," +
           std::to_string(m.minBranch) + "," +
           std::to_string(m.maxBranch) + "," +
           std::to_string(m.totalInsertComparisons) + "," +
           std::to_string(m.totalSearchComparisons) + "," +
           std::to_string(m.numRotations);
}
