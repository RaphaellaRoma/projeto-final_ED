// Leitura do diretório e carregamento dos arquivos
#ifndef DATA_H
#define DATA_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

struct doc{
int id = 0;
vector<string> words;
};

/**
 * @brief Insere cada palavra de um arquivo em um vetor.
 * @param caminho O endereço do arquivo
 * @return Vetor com as palavras (string) contidas no arquivo.
 */
vector<string> ler_palavras(const string& caminho);




/**
 * @brief Para cada documento contido em um diretório, cria um doc(struct) e adiciona em um vetor.
 * @param caminho O endereço do diretório.
 * @param n Inteiro com a quantidade de diretórios a serem lidos.
 * @return Vetor de docs (struct) que contém o id e o vetor de palavras do documento.
 */
vector<doc> read_documents(const string& dir, int n);

#endif