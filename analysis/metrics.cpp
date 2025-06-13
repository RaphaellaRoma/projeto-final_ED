//Funções utilitárias de coleta e salvamento de métricas para medir tempo, comparações, altura, etc.
#include "metrics.h"

std::string gerarCabecalhoCSV() {
    return "Estrutura,Documentos,TempoTotalInsercao,TempoMedioInsercao,TempoTotalBusca,TempoMedioBusca,Altura,MenorGalho,MaiorGalho,ComparacoesInsercao,ComparacoesBusca\n";
}

std::string gerarLinhaCSV(const Metrics& m) {
    return m.estrutura + "," +
           std::to_string(m.qtdDocumentos) + "," +
           std::to_string(m.tempoTotalInsercao) + "," +
           std::to_string(m.tempoMedioInsercao) + "," +
           std::to_string(m.tempoTotalBusca) + "," +
           std::to_string(m.tempoMedioBusca) + "," +
           std::to_string(m.altura) + "," +
           std::to_string(m.menorGalho) + "," +
           std::to_string(m.maiorGalho) + "," +
           std::to_string(m.totalComparacoesInsercao) + "," +
           std::to_string(m.totalComparacoesBusca);
}
