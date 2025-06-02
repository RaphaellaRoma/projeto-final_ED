#include <iostream>
#include "bst.h"
#include "tree_utils.h"

void test_insert() {
    std::cout << "TESTES: BST::insert\n";

    // T1: Inserção básica com atualização de documento
    std::cout << "T1: Inserção básica com múltiplos documentos para mesma palavra\n";
    {
        BST::BinaryTree* tree = BST::create();

        BST::insert(tree, "palavra1", 1);
        BST::insert(tree, "palavra2", 2);
        BST::insert(tree, "palavra1", 3);

        BST::SearchResult resultadoBusca = BST::search(tree, "palavra1");
        if (resultadoBusca.found && resultadoBusca.documentIds.size() == 2) {
            std::cout << "[OK] Inserção e atualização de vetor de documentos funcionando.\n";
        } else {
            std::cerr << "[ERRO] Falha ao adicionar múltiplos documentos para mesma palavra.\n";
        }

        BST::destroy(tree);
    }

    // T2: Inserção em árvore nula deve lançar exceção
    std::cout << "T2: Inserção em árvore nula\n";
    {
        BST::BinaryTree* nullTree = nullptr;

        try {
            BST::insert(nullTree, "erro", 1);
            std::cerr << "[ERRO] Inserção em árvore nula não lançou exceção.\n";
        } catch (...) {
            std::cout << "[OK] Exceção lançada para inserção em árvore nula (esperado).\n";
        }

        BST::destroy(nullTree);  // Seguro, mesmo sendo nullptr
    }

    // T3: Inserção de palavra vazia deve lançar exceção
    std::cout << "T3: Inserção de palavra vazia\n";
    {
        BST::BinaryTree* tree = BST::create();

        try {
            BST::InsertResult res = BST::insert(tree, "", 1);
            std::cerr << "[ERRO] Inserção de palavra vazia não lançou exceção.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "[OK] Exceção capturada para palavra vazia: " << e.what() << "\n";
        } catch (...) {
            std::cout << "[OK] Exceção desconhecida capturada para palavra vazia.\n";
        }

        BST::destroy(tree);
    }

    // T4: Inserção com índice de documento inválido (negativo)
    std::cout << "T4: Inserção com índice de documento inválido\n";
    {
        BST::BinaryTree* tree = BST::create();

        try {
            BST::insert(tree, "palavra", -1);
            std::cerr << "[ERRO] Inserção com índice inválido não lançou exceção.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "[OK] Exceção capturada para índice inválido: " << e.what() << "\n";
        } catch (...) {
            std::cout << "[OK] Exceção desconhecida capturada para índice inválido.\n";
        }

        BST::destroy(tree);
    }
}

void test_search() {
    std::cout << "TESTES: BST::search\n";

    // T1: Busca básica
    std::cout << "T1: Busca por palavras existentes\n";
    {
        BST::BinaryTree* tree = BST::create();

        BST::insert(tree, "palavra1", 1);
        BST::insert(tree, "palavra2", 2);
        BST::insert(tree, "palavra2", 3);

        BST::SearchResult r1 = BST::search(tree, "palavra1");
        BST::SearchResult r2 = BST::search(tree, "palavra2");

        if (r1.found && r1.documentIds.size() == 1 &&
            r2.found && r2.documentIds.size() == 2) {
            std::cout << "[OK] Busca encontrou documentos corretos.\n";
        } else {
            std::cerr << "[ERRO] Busca retornou resultados incorretos.\n";
        }

        BST::destroy(tree);
    }

    // T2: Busca por palavra inexistente
    std::cout << "T2: Busca por palavra inexistente\n";
    {
        BST::BinaryTree* tree = BST::create();

        BST::SearchResult res = BST::search(tree, "palavra_inexistente");
        if (!res.found) {
            std::cout << "[OK] Palavra inexistente não encontrada (como esperado).\n";
        } else {
            std::cerr << "[ERRO] Busca retornou resultado para palavra inexistente.\n";
        }

        BST::destroy(tree);
    }

    // T3: Busca em árvore vazia
    std::cout << "T3: Busca em árvore vazia\n";
    {
        BST::BinaryTree* emptyTree = BST::create();

        BST::SearchResult res = BST::search(emptyTree, "qualquer");
        if (!res.found) {
            std::cout << "[OK] Busca em árvore vazia não encontrou resultado.\n";
        } else {
            std::cerr << "[ERRO] Busca retornou resultado em árvore vazia.\n";
        }

        BST::destroy(emptyTree);
    }
}

int main() {
    test_insert();
    test_search();
    return 0;
}
