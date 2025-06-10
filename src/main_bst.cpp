// Interface via linha de comando (indexação e busca) da Árvore Binária de Busca
#include "bst.h"
#include "data.h"

using namespace BST;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Uso: " << argv[0] << " <search|stats|view> <n_docs> <diretorio>" << std::endl;
        return 1;
    }

    std::string comando = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string diretorio = argv[3];

    BinaryTree* tree = create(); // criar a arvore

    if (comando == "search") {
        vector<doc> documentos = read_documents(diretorio, n_docs);
        for (int i = 0; i < n_docs; ++i) {
            doc document_i = documentos[i];
            for(size_t p = 0; p < document_i.words.size(); ++p){
                string word = document_i.words[p];
                int id = document_i.id;
                insert(tree, word, id);   // inserir os n_docs documentos do diretorio
            }
        }

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
        // Início da contagem de tempo
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<doc> documentos = read_documents(diretorio, n_docs);

        // Fim da contagem de tempo
        auto end = std::chrono::high_resolution_clock::now();

        // Cálculo da duração
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Tempo de leitura: " << duration.count() << " ms" << std::endl;

        int comparisons = 0;
        double insertiontime = 0.0;

        for (int i = 0; i < n_docs; ++i) {
            doc document_i = documentos[i];
            for(size_t p = 0; p < document_i.words.size(); ++p){
                string word = document_i.words[p];
                int id = document_i.id;
                InsertResult insercao_p = insert(tree, word, id);   // inserir os n_docs documentos do diretorio
                comparisons += insercao_p.numComparisons;
                insertiontime += insercao_p.executionTime;
            }
        }
        
        std::cout << "Tempo de insercao: " << insertiontime * 1000 << " ms" << std::endl; // em milisegundos
        std::cout << "Numero de comparacoes: " << comparisons << std::endl;
        int height = getHeight(tree->root);
        std::cout << "Altura da arvore: " << height << std::endl;

    }  else if (comando == "view") {
        vector<doc> documentos = read_documents(diretorio, n_docs);
        for (int i = 0; i < n_docs; ++i) {
            doc document_i = documentos[i];
            for(size_t p = 0; p < document_i.words.size(); ++p){
                string word = document_i.words[p];
                int id = document_i.id;
                insert(tree, word, id);   // inserir os n_docs documentos do diretorio
            }
        }
        printTree(tree);        
    }    else {
        std::cout << "Comando invalido: " << comando << std::endl;
        std::cout << "Use: search, stats ou view" << std::endl;
        return 1;
    }

    return 0;
}