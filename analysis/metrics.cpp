// Funções utilitárias de coleta e salvamento de métricas
#include "metrics.h"

Metrics iniciarMetrics(const std::string& estrutura) {
    Metrics m;
    m.estrutura = estrutura;
    m.qtdDocumentos = 0;
    m.qtdPalavras = 0;
    m.tempoTotalInsercao = 0.0;
    m.tempoMedioInsercao = 0.0;
    m.tempoTotalBusca = 0.0;
    m.tempoMedioBusca = 0.0;
    m.altura = 0;
    m.menorGalho = 0;
    m.maiorGalho = 0;
    m.totalComparacoesInsercao = 0;
    m.totalComparacoesBusca = 0;
    m.numRotacoes = 0;
    return m;
}

std::string gerarCabecalhoCSV() {
    return "Estrutura,Documentos,NumeroPalavras,TempoTotalInsercao,TempoMedioInsercao,TempoTotalBusca,TempoMedioBusca,Altura,MenorGalho,MaiorGalho,ComparacoesInsercao,ComparacoesBusca,NumeroRotacao\n";
}

std::string gerarLinhaCSV(const Metrics& m) {
    return m.estrutura + "," +
           std::to_string(m.qtdDocumentos) + "," +
            std::to_string(m.qtdPalavras) + "," +
           std::to_string(m.tempoTotalInsercao) + "," +
           std::to_string(m.tempoMedioInsercao) + "," +
           std::to_string(m.tempoTotalBusca) + "," +
           std::to_string(m.tempoMedioBusca) + "," +
           std::to_string(m.altura) + "," +
           std::to_string(m.menorGalho) + "," +
           std::to_string(m.maiorGalho) + "," +
           std::to_string(m.totalComparacoesInsercao) + "," +
           std::to_string(m.totalComparacoesBusca) + "," +
           std::to_string(m.numRotacoes);
}
