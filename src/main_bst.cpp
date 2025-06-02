// Interface via linha de comando (indexação e busca) da Árvore Binária de Busca
#include <iostream> //import do python
#include "bst.h"
#include <vector>

using namespace bst;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Uso: " << argv[0] << " <search|stats> <n_docs> <diretorio>" << std::endl;
        return 1;
    }

    std::string comando = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string diretorio = argv[3];

    BinaryTree* tree = create(); // criar a arvore
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId); // inserir os n_docs documentos do diretorio

    if (comando == "search") {
        std::string palavra;

        while (true) {
            std::cout << "Digite q para sair. Palavra buscada: ";
            std::cin >> palavra;

            if (palavra == "q") {
                break;  // Sai do loop se digitou "q"
            }

            SearchResult resultado = search(tree, palavra);  
            
            if (resultado.found == 1){
                std::cout << palavra << " está presente em: ";
                for (int docId : resultado.documentIds) {
                    std::cout << docId << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << palavra << "não está presente em nenhum documento." << std::endl;
            }

        };
    } else if (comando == "stats") {
        std::cout << "Comando stats ainda não foi implementado" << std::endl;
        return 1;
    } else {
        std::cout << "Comando inválido: " << comando << std::endl;
        std::cout << "Use: search ou stats" << std::endl;
        return 1;
    }

    return 0;
}