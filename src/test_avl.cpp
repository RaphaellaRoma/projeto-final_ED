#include <iostream>
#include "avl.h"
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
    printHeader("TESTES: AVL::insert");

    // T1
    printTest("T1: Insercao basica com multiplos documentos para mesma palavra");
    {
        BinaryTree* tree = AVL::create();

        AVL::insert(tree, "palavra1", 1);
        AVL::insert(tree, "palavra2", 2);
        AVL::insert(tree, "palavra1", 3);

        auto res = AVL::search(tree, "palavra1");
        if (res.found && res.documentIds.size() == 2) {
            ok("Insercao e atualizacao de documentos funcionando.");
            passed++;
        } else {
            error("Falha ao adicionar multiplos documentos para mesma palavra.");
            failed++;
        }

        AVL::destroy(tree);
    }

    // T2
    printTest("T2: Insercao em arvore nula");
    {
        BinaryTree* nullTree = nullptr;
        try {
            AVL::insert(nullTree, "erro", 1);
            error("Insercao em arvore nula nao lancou excecao.");
            failed++;
        } catch (...) {
            ok("Excecao lancada corretamente para arvore nula.");
            passed++;
        }
        AVL::destroy(nullTree);
    }

    // T3
    printTest("T3: Insercao de palavra vazia");
    {
        BinaryTree* tree = AVL::create();
        try {
            AVL::insert(tree, "", 1);
            error("Palavra vazia foi inserida, o que nao deveria.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para palavra vazia.");
            passed++;
        }
        AVL::destroy(tree);
    }

    // T4
    printTest("T4: Insercao com indice de documento invalido");
    {
        BinaryTree* tree = AVL::create();
        try {
            AVL::insert(tree, "palavra", -1);
            error("Indice invalido nao gerou excecao.");
            failed++;
        } catch (const std::invalid_argument& e) {
            ok(std::string("Excecao capturada: ") + e.what());
            passed++;
        } catch (...) {
            ok("Excecao desconhecida capturada para indice invalido.");
            passed++;
        }
        AVL::destroy(tree);
    }
}

void test_search(int& passed, int& failed) {
    printHeader("TESTES: AVL::search");

    // T1
    printTest("T1: Busca por palavras existentes");
    {
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "palavra1", 1);
        AVL::insert(tree, "palavra2", 2);
        AVL::insert(tree, "palavra2", 3);

        auto r1 = AVL::search(tree, "palavra1");
        auto r2 = AVL::search(tree, "palavra2");

        if (r1.found && r1.documentIds.size() == 1 &&
            r2.found && r2.documentIds.size() == 2) {
            ok("Busca encontrou os documentos corretos.");
            passed++;
        } else {
            error("Busca retornou resultados incorretos.");
            failed++;
        }

        AVL::destroy(tree);
    }

    // T2
    printTest("T2: Busca por palavra inexistente");
    {
        BinaryTree* tree = AVL::create();
        auto res = AVL::search(tree, "palavra_inexistente");
        if (!res.found) {
            ok("Palavra inexistente nao foi encontrada (como esperado).");
            passed++;
        } else {
            error("Busca retornou resultado incorreto para palavra inexistente.");
            failed++;
        }
        AVL::destroy(tree);
    }

    // T3
    printTest("T3: Busca em arvore vazia");
    {
        BinaryTree* emptyTree = AVL::create();
        auto res = AVL::search(emptyTree, "qualquer");
        if (!res.found) {
            ok("Busca em arvore vazia falhou como esperado.");
            passed++;
        } else {
            error("Busca retornou resultado em arvore vazia.");
            failed++;
        }
        AVL::destroy(emptyTree);
    }
}

void test_rotation(int& passed, int& failed) {
    printHeader("TESTES: AVL::rotacoes");

    // Funções auxiliares
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return node->height;
        }
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            // Calcula a altura da subárvore esquerda
            int leftHeight = 0;
            if (node->left == nullptr) {
                leftHeight = 0;
            } else {
                leftHeight = node->left->height;
            }

            // Calcula a altura da subárvore direita
            int rightHeight = 0;
            if (node->right == nullptr) {
                rightHeight = 0;
            } else {
                rightHeight = node->right->height;
            }

            return leftHeight - rightHeight;
        }
    }

    bool isBalanced(Node* node) {
        if (node == nullptr) {
            return true; // Um nó nulo é sempre balanceado
        }

        int balance = getBalance(node);
        if (balance < -1 || balance > 1) {
            return false;
        }

        // Verifica recursivamente as subárvores esquerda e direita
        bool leftBalanced = isBalanced(node->left);
        bool rightBalanced = isBalanced(node->right);

        return leftBalanced && rightBalanced;


    // T1
    printTest("T1: Rotacao simples a direita");
    {
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "c", 1);
        AVL::insert(tree, "b", 1);
        AVL::insert(tree, "a", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao simples a direita executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao simples a direita.");
            failed++;
        }

        AVL::destroy(tree);
    }

    // T2
    printTest("T2: Rotacao simples a esquerda");
    {
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "a", 1);
        AVL::insert(tree, "b", 1);
        AVL::insert(tree, "c", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao simples a esquerda executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao simples a esquerda.");
            failed++;
        }

        AVL::destroy(tree);
    }

    // T3
    printTest("T3: Rotacao dupla a direita (Left-Right)");
    {
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "c", 1);
        AVL::insert(tree, "a", 1);
        AVL::insert(tree, "b", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao dupla a direita executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao dupla a direita.");
            failed++;
        }

        AVL::destroy(tree);
    }

    // T4
    printTest("T4: Rotacao dupla a esquerda (Right-Left)");
    {
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "a", 1);
        AVL::insert(tree, "c", 1);
        AVL::insert(tree, "b", 1);

        bool correctRoot = (tree->root && tree->root->word == "b");
        bool balanced = isBalanced(tree->root);

        if (correctRoot && balanced) {
            ok("Rotacao dupla a esquerda executada corretamente.");
            passed++;
        } else {
            error("Falha na rotacao dupla a esquerda.");
            failed++;
        }

        AVL::destroy(tree);
    }
}

int main() {
    int passed = 0, failed = 0;

    test_insert(passed, failed);
    test_search(passed, failed);
    test_rotation(passed, failed);

    std::cout << "\n======== RESUMO FINAL ========\n";
    std::cout << "Testes passados: " << passed << "\n";
    std::cout << "Testes falharam: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
