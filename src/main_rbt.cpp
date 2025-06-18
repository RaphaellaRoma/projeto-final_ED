// Interface via linha de comando (indexação e busca) da Árvore Rubro Negra
#include "rbt.h"
#include "data.h"

using namespace RBT;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Uso: " << argv[0] << " <search|stats|view> <n_docs> <diretorio>" << std::endl;
        return 1;
    }

    std::string comando = argv[1];
    int n_docs = std::stoi(argv[2]);
    if (n_docs < 0) {
        std::cout << "Comando invalido: " << comando << std::endl;
        std::cout << "<n_docs> = " << argv[2] << " precisa ser nao negativo " << std::endl;
        return 1;
    }
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
        int numPalavras = 0;
        int numNos = 0;
        double searchtime = 0.0;
        double searchtimemax = 0.0;
        int numRotations = 0;

        for (int i = 0; i < n_docs; ++i) {
            doc document_i = documentos[i];
            for(size_t p = 0; p < document_i.words.size(); ++p){
                string word = document_i.words[p];
                int id = document_i.id;
                InsertResult insercao_p = insert(tree, word, id);   // inserir os n_docs documentos do diretorio
                SearchResult search_p = search(tree, word);
                searchtime += search_p.executionTime;
                comparisons += insercao_p.numComparisons;
                insertiontime += insercao_p.executionTime;
                numRotations += insercao_p.numRotations;
                numPalavras += 1;
                if (search_p.executionTime>searchtimemax){
                    searchtimemax = search_p.executionTime;
                }
                if (insercao_p.alreadyInsert == 0){
                    numNos += 1;
                }
            }
        }
        int height = getHeight(tree->root, tree->NIL);
        int min_deph = minDeph(tree->root, tree->NIL);
        
        std::cout << "Tempo de insercao total: " << insertiontime * 1000 << " ms" << std::endl; // em milisegundos
        if (numPalavras == 0) {
            std::cout << "Tempo de insercao medio: 0 ms" << std::endl; // em milisegundos
            std::cout << "Tempo de busca medio: 0 ms" << std::endl; // em milisegundos
        } else {
            std::cout << "Tempo de insercao medio: " << insertiontime * 1000 / numPalavras << " ms" << std::endl; // em milisegundos
            std::cout << "Tempo de busca medio: " << searchtime * 1000 / numPalavras << " ms" << std::endl; // em milisegundos
        }
        std::cout << "Tempo de busca maximo: " << searchtimemax * 1000 << " ms" << std::endl; // em milisegundos
        std::cout << "Numero de comparacoes: " << comparisons << std::endl;
        std::cout << "Altura da arvore: " << height << std::endl;
        std::cout << "Menor caminho: " << min_deph << std::endl;
        std::cout << "Maior caminho: " << height << std::endl;
        std::cout << "Numero de rotacoes: " << numRotations << std::endl;
        std::cout << "Numero de nos na arvore: " << numNos << std::endl;
        std::cout << "Numero total de palavras nos " << n_docs << " documentos: " << numPalavras << std::endl;
    
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
        std::cout << "Selecione o tipo de visualizacao: " << std::endl;
        std::cout << "1 - Estrutura da arvore" << std::endl;
        std::cout << "2 - Indice invertido" << std::endl;
        int chooseView;
        std::cin >> chooseView;
        if (chooseView == 1){
            printTree(tree);
        }
        else if (chooseView == 2) {
            printIndex(tree);
        }
        else{
            std::cout << "Comando invalido. Digite o tipo de visualizacao (1 ou 2)" << std::endl;
            return 1;
        }  
            
    } else {
        std::cout << "Comando invalido: " << comando << std::endl;
        std::cout << "Use: search, stats ou view" << std::endl;
        return 1;
    }

    return 0;
}