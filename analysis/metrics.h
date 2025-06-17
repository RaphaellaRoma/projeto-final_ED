//Funções utilitárias de coleta e salvamento de métricas para medir tempo, comparações, altura, etc.
#ifndef METRICS_H
#define METRICS_H

#include <string>

struct Metrics {
    std::string estrutura;
    int qtdDocumentos;
    int qtdPalavras;
    double tempoTotalInsercao;
    double tempoMedioInsercao;
    double tempoTotalBusca;
    double tempoMedioBusca;
    int altura;
    int menorGalho;
    int maiorGalho;
    int totalComparacoesInsercao;
    int totalComparacoesBusca;
    int numRotacoes;
};

// Funções livres:
std::string gerarCabecalhoCSV();
std::string gerarLinhaCSV(const Metrics& m);

#endif




