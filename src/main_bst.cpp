// Interface via linha de comando (indexação e busca) da Árvore Binária de Busca
#include "bst.h"
#include "data.h"

using namespace BST;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Uso: " << argv[0] << " <search|stats> <n_docs> <diretorio>" << std::endl;
        return 1;
    }

    std::string comando = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string diretorio = argv[3];

    BinaryTree* tree = create(); // criar a arvore

    vector<doc> documentos = read_documents(diretorio, n_docs);
    for (int i = 0; i < n_docs; ++i) {
        doc document_i = documentos[i];
        for(size_t p = 0; p < document_i.words.size(); ++p){
            string word = document_i.words[p];
            int id = document_i.id;
            insert(tree, word, id);   // inserir os n_docs documentos do diretorio
        }
    }

    if (comando == "search") {
        std::string palavra;

        while (true) {
            std::cout << "Digite . para sair. Palavra buscada: ";
            std::cin >> palavra;

            if (palavra == ".") {
                break;  // Sai do loop se digitou "."
            }

            SearchResult resultado = search(tree, palavra);  
            
            if (resultado.found == 1){
                std::cout << palavra << " esta presente em: ";
                for (int docId : resultado.documentIds) {
                    std::cout << docId << " ";
                }
                std::cout << std::endl;
                std::cout << "Tempo de execucao: "<< resultado.executionTime << std::endl;
                std::cout << "Numero de comparacoes realizadas durante a busca: "<< resultado.numComparisons << std::endl;
            } else {
                std::cout << palavra << " nao esta presente em nenhum documento." << std::endl;
            }

        };
    } else if (comando == "stats") {
        std::cout << "Comando stats ainda nao foi implementado" << std::endl;
        return 1;
    } else {
        std::cout << "Comando invalido: " << comando << std::endl;
        std::cout << "Use: search ou stats" << std::endl;
        return 1;
    }

    return 0;
}