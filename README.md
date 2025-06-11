# Projeto A2 – Índice Invertido com BST, AVL e RBT

Trabalho da disciplina de Estrutura de Dados: implementação de um índice invertido em C/C++, utilizando três estruturas de árvores:

- Árvore Binária de Busca (BST)  
- Árvore AVL  
- Árvore Rubro-Negra (RBT)  

## Integrantes do Grupo:

- Beatriz Marques
- Elisa Soares
- Raphaella Roma
- Samyra Mara
- Stephany Casali

## Estrutura do repositório:

```
projeto-final_ED/
│
├── src/
│   ├── main_bst.cpp                  # Interface via linha de comando (indexação e busca) da Árvore Binária de Busca
│   ├── main_avl.cpp                  # Interface via linha de comando (indexação e busca) da Árvore AVL
│   ├── main_rbt.cpp                  # Interface via linha de comando (indexação e busca) da Árvore Rubro Negra
│   ├── bst.cpp / bst.h               # Implementação da Árvore Binária de Busca
│   ├── avl.cpp / avl.h               # Implementação da Árvore AVL
│   ├── rbt.cpp / rbt.h               # Implementação da Árvore Rubro-Negra
│   ├── tree_utils.cpp / tree_util.h  # Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc
│   ├── data.cpp / data.h             # Leitura do diretório e carregamento dos arquivos 
│   ├── test_bst.cpp                  # testes unitários e exemplos para implementação da Árvore Binária de Busca
│   ├── test_avl.cpp                  # testes unitários e exemplos para implementação da Árvore AVL
│   ├── test_rbt.cpp                  # testes unitários e exemplos para implementação da Rubro-Negra
│
└── analysis/
    ├── analysis_avl.cpp              # Código que executa os testes e coleta dados da AVL
    ├── analysis_bst.cpp              # Código que executa os testes e coleta dados da BST
    ├── analysis_rbt.cpp              # Código que executa os testes e coleta dados da RBT
    ├── metrics.cpp /metrics.h        # Funções auxiliares para coletar métricas (tempos, comparações, altura etc.)
    ├── metrics.h
    ├── Makefile                      # Para compilar os arquivos da pasta analysis
    ├── results/                 
    │   ├── CSVs gerados com os dados brutos (.csv)
    └── plots/                        # Scripts e imagens de gráficos gerados
        ├── plot_analysis.py          # Código Python para ler os CSVs e gerar gráficos
├── docs/
│   ├── Relatório (PDF ou .md)
│
├── data/
│   ├── Base de dados de documentos (.txt)
│
├── README.md # Descrição, instruções de compilação e execução do Projeto
```

## Instruções para compilar:

> **Importante:** Execute os comandos `make` a partir da raiz do projeto.

> Os executáveis são gerados na pasta `build/` após a compilação.

- Compilar BST  
  ```bash
  make bst

- Compilar AVL
  ```bash
  make avl

- Compilar RBT
  ```bash
  make rbt
Observação: A implementação da Árvore Rubro-Negra (RBT) ainda não está completa.

## Testes:
- BST
  ```bash
  make test_bst

- AVL
  ```bash
  make test_avl

- RBT
  ```bash
  make test_rbt
Observação: Testes para a Árvore Rubro-Negra (RBT) ainda não estão disponíveis.

