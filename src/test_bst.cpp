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
    printTest("T1: Insercao basica com multiplos documentos para mesma palavra");
    {
        BinaryTree* tree = BST::create();

        BST::insert(tree, "palavra1", 1);
        BST::insert(tree, "palavra2", 2);
        BST::insert(tree, "palavra1", 3);

        auto res = BST::search(tree, "palavra1");
        if (res.found && res.documentIds.size() == 2) {
            ok("Insercao e atualizacao de documentos funcionando.");
            passed++;
        } else {
            error("Falha ao adicionar multiplos documentos para mesma palavra.");
            failed++;
        }

        BST::destroy(tree);
    }

    // T2
    printTest("T2: Insercao em arvore nula");
    {
        BinaryTree* nullTree = nullptr;
        try {
            BST::insert(nullTree, "erro", 1);
            error("Insercao em arvore nula nao lancou excecao.");
            failed++;
        } catch (...) {
            ok("Excecao lancada corretamente para arvore nula.");
            passed++;
        }
        BST::destroy(nullTree);
    }

    // T3
    printTest("T3: Insercao de palavra vazia");
    {
        BinaryTree* tree = BST::create();
        try {
            BST::insert(tree, "", 1);
            error("Palavra vazia foi inserida, o que nao deveria.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para palavra vazia.");
            passed++;
        }
        BST::destroy(tree);
    }

    // T4
    printTest("T4: Insercao com indice de documento invalido");
    {
        BinaryTree* tree = BST::create();
        try {
            BST::insert(tree, "palavra", -1);
            error("Indice invalido nao gerou excecao.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para indice invalido.");
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
        BinaryTree* tree = BST::create();
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
        BinaryTree* tree = BST::create();
        auto res = BST::search(tree, "palavra_inexistente");
        if (!res.found) {
            ok("Palavra inexistente nao foi encontrada (como esperado).");
            passed++;
        } else {
            error("Busca retornou resultado incorreto para palavra inexistente.");
            failed++;
        }
        BST::destroy(tree);
    }

    // T3
    printTest("T3: Busca em arvore vazia");
    {
        BinaryTree* emptyTree = BST::create();
        auto res = BST::search(emptyTree, "qualquer");
        if (!res.found) {
            ok("Busca em arvore vazia falhou como esperado.");
            passed++;
        } else {
            error("Busca retornou resultado em arvore vazia.");
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