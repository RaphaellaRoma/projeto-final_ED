// Leitura do diretório e carregamento dos arquivos

#include "data.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

vector<string> ler_palavras(const string& caminho) {
    ifstream arquivo(caminho);
    vector<string> palavras;
    string palavra;

    
    while (arquivo >> palavra) {
        palavras.push_back(palavra);
    }

    return palavras;
}



vector<doc> read_documents(const string& dir, int n) {
    vector<doc> documentos;

    for (int i = 0; i <= n; ++i) {
        string nome_arquivo = dir + "/" + to_string(i) + ".txt";
        ifstream teste(nome_arquivo);
        if (!teste.is_open()) {
            cerr << "Nao consegui abrir " << nome_arquivo << ". Pulando.\n";
            continue;
        }

        doc doc;
        doc.id = i; 
        doc.words = ler_palavras(nome_arquivo);
        documentos.push_back(doc);
    }

/*
    for (const auto& doc : documentos) {
        cout << "Arquivo " << doc.id << ": " << doc.words.size() << " palavras\n";
    }
*/
    return documentos;
}
