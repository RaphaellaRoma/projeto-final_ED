#include <iostream>
#include "bst.h"
#include "tree_utils.h"

void printHeader(const std::string& title) {
    std::cout << "\n======== " << title << " ========\n";
}

void printTest(const std::string& description) {
    std::cout << ">> " << description << "\n";
}

void ok(const std::string& msg) {
    std::cout << "[OK] " << msg << "\n";
}

void error(const std::string& msg) {
    std::cerr << "[ERRO] " << msg << "\n";
}

void test_insert(int& passed, int& failed) {
    printHeader("TESTES: BST::insert");

    // T1
    printTest("T1: Inserção básica com múltiplos documentos para mesma palavra");
    {
        BST::BinaryTree* tree = BST::create();

        BST::insert(tree, "palavra1", 1);
        BST::insert(tree, "palavra2", 2);
        BST::insert(tree, "palavra1", 3);

        auto res = BST::search(tree, "palavra1");
        if (res.found && res.documentIds.size() == 2) {
            ok("Inserção e atualização de documentos funcionando.");
            passed++;
        } else {
            error("Falha ao adicionar múltiplos documentos para mesma palavra.");
            failed++;
        }

        BST::destroy(tree);
    }

    // T2
    printTest("T2: Inserção em árvore nula");
    {
        BST::BinaryTree* nullTree = nullptr;
        try {
            BST::insert(nullTree, "erro", 1);
            error("Inserção em árvore nula não lançou exceção.");
            failed++;
        } catch (...) {
            ok("Exceção lançada corretamente para árvore nula.");
            passed++;
        }
        BST::destroy(nullTree);
    }

    // T3
    printTest("T3: Inserção de palavra vazia");
    {
        BST::BinaryTree* tree = BST::create();
        try {
            BST::insert(tree, "", 1);
            error("Palavra vazia foi inserida, o que não deveria.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Exceção capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Exceção desconhecida capturada para palavra vazia.");
            passed++;
        }
        BST::destroy(tree);
    }

    // T4
    printTest("T4: Inserção com índice de documento inválido");
    {
        BST::BinaryTree* tree = BST::create();
        try {
            BST::insert(tree, "palavra", -1);
            error("Índice inválido não gerou exceção.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Exceção capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Exceção desconhecida capturada para índice inválido.");
            passed++;
        }
        BST::destroy(tree);
    }
}

void test_search(int& passed, int& failed) {
    printHeader("TESTES: BST::search");

    // T1
    printTest("T1: Busca por palavras existentes");
    {
        BST::BinaryTree* tree = BST::create();
        BST::insert(tree, "palavra1", 1);
        BST::insert(tree, "palavra2", 2);
        BST::insert(tree, "palavra2", 3);

        auto r1 = BST::search(tree, "palavra1");
        auto r2 = BST::search(tree, "palavra2");

        if (r1.found && r1.documentIds.size() == 1 &&
            r2.found && r2.documentIds.size() == 2) {
            ok("Busca encontrou os documentos corretos.");
            passed++;
        } else {
            error("Busca retornou resultados incorretos.");
            failed++;
        }

        BST::destroy(tree);
    }

    // T2
    printTest("T2: Busca por palavra inexistente");
    {
        BST::BinaryTree* tree = BST::create();
        auto res = BST::search(tree, "palavra_inexistente");
        if (!res.found) {
            ok("Palavra inexistente não foi encontrada (como esperado).");
            passed++;
        } else {
            error("Busca retornou resultado incorreto para palavra inexistente.");
            failed++;
        }
        BST::destroy(tree);
    }

    // T3
    printTest("T3: Busca em árvore vazia");
    {
        BST::BinaryTree* emptyTree = BST::create();
        auto res = BST::search(emptyTree, "qualquer");
        if (!res.found) {
            ok("Busca em árvore vazia falhou como esperado.");
            passed++;
        } else {
            error("Busca retornou resultado em árvore vazia.");
            failed++;
        }
        BST::destroy(emptyTree);
    }
}

int main() {
    int passed = 0, failed = 0;

    test_insert(passed, failed);
    test_search(passed, failed);

    std::cout << "\n======== RESUMO FINAL ========\n";
    std::cout << "Testes passados: " << passed << "\n";
    std::cout << "Testes falharam: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
