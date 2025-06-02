// testes unitários e exemplos para implementação da Árvore Binária de Busca

#include <iostream>
#include "bst.h"
#include "tree_utils.h"

void test_insert() {
    std::cout << "TESTES: BST::insert \n";

    std::cout << "T1: Caso básico \n"; // Caso básico
    BinaryTree* tree = BST::create();

    BST::insert(tree, "palavra1", 1);
    BST::insert(tree, "palavra2", 2);
    BST::insert(tree, "palavra1", 3); 

    SearchResult result = BST::search(tree, "palavra1");
    if (result.found && result.documentIds.size() == 2) {
        std::cout << "[OK] Inserção e atualização de vetor de documentos funcionando.\n";
    } else {
        std::cerr << "[ERRO] Inserção falhou em adicionar múltiplos documentos para mesma palavra.\n";
    }

    BST::delete_tree(tree);

    std::cout << "T2: Teste árvore nula \n"; // Teste com árvore nula
    BinaryTree* nullTree = nullptr;
    try {
        BST::insert(nullTree, "erro", 1);
        std::cerr << "[ERRO] Inserção em árvore nula não causou falha.\n";
    } catch (...) {
        std::cout << "[OK] Inserção em árvore nula detectada com erro (esperado).\n";
    }

    std::cout << "T3: Teste com palavra vazia \n"; // Teste com palavra vazia
    BST::InsertResult result = BST::insert(tree, "", 1);
    if (result.numComparisons == 0) {
        std::cout << "[OK] Palavra vazia foi ignorada corretamente.\n";
    } else {
        std::cerr << "[ERRO] Palavra vazia foi inserida, o que não deveria.\n";
    }

    BST::delete_tree(tree);
}

void test_search() {
    std::cout << "TESTES: BST::search \n";

    std::cout << "T1: Caso básico \n";
    BinaryTree* tree = BST::create();

    BST::insert(tree, "palavra1", 1);
    BST::insert(tree, "palavra2", 2);
    BST::insert(tree, "palavra2", 3);

    SearchResult r1 = BST::search(tree, "palavra1");
    SearchResult r2 = BST::search(tree, "palavra2");

    if (r1.found && r1.documentIds.size() == 1 &&
        r2.found && r2.documentIds.size() == 2) {
        std::cout << "[OK] Buscas encontraram documentos corretos.\n";
    } else {
        std::cerr << "[ERRO] Busca retornou resultados incorretos.\n";
    }

    std::cout << "T2: Palavra não existente \n";
    SearchResult res = BST::search(tree, "palavra3");
    if (!res.found) {
        std::cout << "[OK] Palavra inexistente não encontrada.\n";
    } else {
        std::cerr << "[ERRO] Busca retornou resultado para palavra inexistente.\n";
    }

    std::cout << "T3: Busca em árvore vazia \n";
    BinaryTree* empty = BST::create();
    SearchResult r2 = BST::search(empty, "teste");
    if (!r2.found) {
        std::cout << "[OK] Busca em árvore vazia falhou como esperado.\n";
    } else {
        std::cerr << "[ERRO] Busca retornou resultado numa árvore vazia.\n";
    }

    BST::delete_tree(tree);
    BST::delete_tree(empty);
}

int main() {
    test_insert();
    test_search();
    return 0;
}

