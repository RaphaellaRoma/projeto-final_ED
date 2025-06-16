// testes unitários e exemplos para implementação da Rubro-Negra
#include <iostream>
#include "rbt.h"
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
    printHeader("TESTES: RBT::insert");

    // T1
    printTest("T1: Insercao basica com multiplos documentos para mesma palavra");
    {
        BinaryTree* tree = RBT::create();

        RBT::insert(tree, "palavra1", 1);
        RBT::insert(tree, "palavra2", 2);
        RBT::insert(tree, "palavra1", 3);

        auto res = RBT::search(tree, "palavra1");
        if (res.found && res.documentIds.size() == 2) {
            ok("Insercao e atualizacao de documentos funcionando.");
            passed++;
        } else {
            error("Falha ao adicionar multiplos documentos para mesma palavra.");
            failed++;
        }
        std::cout<< "passou"<<std::endl;
        RBT::destroy(tree);
        std::cout<< "passou 2"<<std::endl;
    }

    // T2
    printTest("T2: Insercao em arvore nula");
    {
        BinaryTree* nullTree = nullptr;
        try {
            RBT::insert(nullTree, "erro", 1);
            error("Insercao em arvore nula nao lancou excecao.");
            failed++;
        } catch (...) {
            ok("Excecao lancada corretamente para arvore nula.");
            passed++;
        }
        RBT::destroy(nullTree);
    }

    // T3
    printTest("T3: Insercao de palavra vazia");
    {
        BinaryTree* tree = RBT::create();
        try {
            RBT::insert(tree, "", 1);
            error("Palavra vazia foi inserida, o que nao deveria.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para palavra vazia.");
            passed++;
        }
        RBT::destroy(tree);
    }

    // T4
    printTest("T4: Insercao com indice de documento invalido");
    {
        BinaryTree* tree = RBT::create();
        try {
            RBT::insert(tree, "palavra", -1);
            error("Indice invalido nao gerou excecao.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para indice invalido.");
            passed++;
        }
        RBT::destroy(tree);
    }
}

void test_search(int& passed, int& failed) {
    printHeader("TESTES: RBT::search");

    // T1
    printTest("T1: Busca por palavras existentes");
    {
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "palavra1", 1);
        RBT::insert(tree, "palavra2", 2);
        RBT::insert(tree, "palavra2", 3);

        auto r1 = RBT::search(tree, "palavra1");
        auto r2 = RBT::search(tree, "palavra2");

        if (r1.found && r1.documentIds.size() == 1 &&
            r2.found && r2.documentIds.size() == 2) {
            ok("Busca encontrou os documentos corretos.");
            passed++;
        } else {
            error("Busca retornou resultados incorretos.");
            failed++;
        }

        RBT::destroy(tree);
    }

    // T2
    printTest("T2: Busca por palavra inexistente");
    {
        BinaryTree* tree = RBT::create();
        auto res = RBT::search(tree, "palavra_inexistente");
        if (!res.found) {
            ok("Palavra inexistente nao foi encontrada (como esperado).");
            passed++;
        } else {
            error("Busca retornou resultado incorreto para palavra inexistente.");
            failed++;
        }
        RBT::destroy(tree);
    }

    // T3
    printTest("T3: Busca em arvore vazia");
    {
        BinaryTree* emptyTree = RBT::create();
        auto res = RBT::search(emptyTree, "qualquer");
        if (!res.found) {
            ok("Busca em arvore vazia falhou como esperado.");
            passed++;
        } else {
            error("Busca retornou resultado em arvore vazia.");
            failed++;
        }
        RBT::destroy(emptyTree);
    }
}

void test_rotation(int& passed, int& failed) {
    printHeader("TESTES: RBT::rotacoes");

    // T1
    printTest("T1: Rotacao simples a direita");
    {
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "c", 1);
        RBT::insert(tree, "b", 1);
        RBT::insert(tree, "a", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao simples a direita executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao simples a direita.");
            failed++;
        }

        RBT::destroy(tree);
    }

    // T2
    printTest("T2: Rotacao simples a esquerda");
    {
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "a", 1);
        RBT::insert(tree, "b", 1);
        RBT::insert(tree, "c", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao simples a esquerda executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao simples a esquerda.");
            failed++;
        }

        RBT::destroy(tree);
    }

    // T3
    printTest("T3: Rotacao dupla a direita (Left-Right)");
    {
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "c", 1);
        RBT::insert(tree, "a", 1);
        RBT::insert(tree, "b", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao dupla a direita executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao dupla a direita.");
            failed++;
        }

        RBT::destroy(tree);
    }

    // T4
    printTest("T4: Rotacao dupla a esquerda (Right-Left)");
    {
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "a", 1);
        RBT::insert(tree, "c", 1);
        RBT::insert(tree, "b", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao dupla a esquerda executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao dupla a esquerda.");
            failed++;
        }

        RBT::destroy(tree);
    }
}

void test_root_color(int& passed, int& failed) {
    printHeader("TESTES: RBT::root_color");

    BinaryTree* tree = RBT::create();

    RBT::insert(tree, "b", 1);
    RBT::insert(tree, "a", 1);
    RBT::insert(tree, "c", 1);

    if (tree->root->isRed == 0) {
        ok("Raiz e preta apos insercoes.");
        passed++;
    } else {
        error("Falha: Raiz nao esta preta apos insercoes.");
        failed++;
    }

    RBT::destroy(tree);
}

void test_red_violation(int& passed, int& failed) {
    printHeader("TESTE: RBT::red_violation");

    BinaryTree* tree = RBT::create();

    RBT::insert(tree, "d", 1);
    RBT::insert(tree, "b", 1);
    RBT::insert(tree, "f", 1);
    RBT::insert(tree, "a", 1);
    RBT::insert(tree, "c", 1);
    RBT::insert(tree, "e", 1);
    RBT::insert(tree, "g", 1);

    if (check_no_red_red(tree->root, tree->NIL)) {
        ok("Nenhum no vermelho com filho vermelho.");
        passed++;
    } else {
        error("Falha: No vermelho com filho vermelho encontrado.");
        failed++;
    }

    RBT::destroy(tree);
}

void test_black_height(int& passed, int& failed) {
    printHeader("TESTE: RBT::black_height");

    BinaryTree* tree = RBT::create();

    RBT::insert(tree, "h", 1);
    RBT::insert(tree, "d", 1);
    RBT::insert(tree, "l", 1);
    RBT::insert(tree, "b", 1);
    RBT::insert(tree, "f", 1);
    RBT::insert(tree, "j", 1);
    RBT::insert(tree, "n", 1);

    int blackHeight = -1;
    if (check_black_height(tree->root, tree->NIL, blackHeight)) {
        ok("Altura negra uniforme verificada com sucesso.");
        passed++;
    } else {
        error("Altura negra não e uniforme.");
        failed++;
    }

    RBT::destroy(tree);
}

int main() {
    int passed = 0, failed = 0;

    test_insert(passed, failed);
    test_search(passed, failed);
    test_rotation(passed, failed);
    test_root_color(passed, failed);
    test_red_violation(passed, failed);
    test_black_height(passed, failed);

    std::cout << "\n======== RESUMO FINAL ========\n";
    std::cout << "Testes passados: " << passed << "\n";
    std::cout << "Testes falharam: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
