# Trabalho A2: Índice Invertido e Análise Comparativa de Estruturas de Dados

## 1. Introdução

O presente relatório apresenta a implementação em C++ de um índice invertido utilizando três diferentes estruturas de dados: Árvore Binária de Busca (BST), Árvore AVL (AVL) e Árvore Rubro-Negra (RBT). O objetivo principal é avaliar e comparar o desempenho dessas estruturas nas operações de inserção e busca de palavras em um corpus textual real.

## 2. Divisão de Tarefas

| Nome                        | Tarefa Principal                                                                                |
|-----------------------------|-------------------------------------------------------------------------------------------------|
| Stephany Casali Oliveira    | Implementação da BST (insert e search)  e confecção do relatorio                                |
| Samyra Mara Candido Silva   | Implementação da AVL e testes unitarios da BST                                                  |
| Raphaella Roma Mendes Alves | Implementação da RBT e Leitura de dados                                                         |
| Beatriz dos Santos Marques  | Implementação da RBT, Implementação das funções printTree e printIndex e testes unitarios da RBT|
| Elisa de Oliveira Soares    | CLI, Implementação da create e destroy e testes unitarios da AVL                                |

Além das tarefas acima citadas, cada integrante foi responsável por documentar suas próprias funções.

## 3. Estrutura do repositório:

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
│   ├── tree_utils.cpp / tree_utils.h # Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc
│   ├── data.cpp / data.h             # Leitura do diretório e carregamento dos arquivos 
│   ├── test_bst.cpp                  # testes unitários e exemplos para implementação da Árvore Binária de Busca
│   ├── test_avl.cpp                  # testes unitários e exemplos para implementação da Árvore AVL
│   ├── test_rbt.cpp                  # testes unitários e exemplos para implementação da Rubro-Negra
│
├── build/                            # Usada para armazenar todos os arquivos executáveis gerados após a compilação
│
├── analysis/
│   ├── analysis_avl.cpp              # Código que executa os testes e coleta dados da AVL
│   ├── analysis_bst.cpp              # Código que executa os testes e coleta dados da BST
│   ├── analysis_rbt.cpp              # Código que executa os testes e coleta dados da RBT
│   ├── metrics.cpp / metrics.h       # Funções auxiliares para coletar métricas (tempos, comparações, altura etc.)
│   ├── Makefile                      # Para compilar os arquivos da pasta analysis
│   ├── results/                 
│   │   ├── CSVs gerados com os dados brutos (.csv)
│   ├── plots/                        # Scripts dos gráficos gerados
│       ├── plot_analysis.py          # Código Python para ler os CSVs e gerar gráficos
│
├── docs/
│   ├── Relatório (PDF ou .md)
│   ├── graphs_tables/                # Usada para armazenar todos gráficos e tabelas gerados nas analises
│
├── data/
│   ├── Base de dados de documentos (.txt)
│
├── Makefile  # Para compilar os arquivos da pasta `src/` e gerar os executáveis na pasta `build/`
│
├── README.md # Descrição, instruções de compilação e execução do Projeto
```

## 4. Metodologia

### 4.1. Leitura dos Documentos

Para a leitura dos dados dos documentos, utilizamos a classe `ifstream`, fornecida pela biblioteca `fstream`. Essa classe permite a manipulação de arquivos de entrada de forma eficiente e estruturada. Para o armazenamento dos dados, optamos por criar uma struct chamada docs, que contém o ID do documento e um vetor com todos os termos extraídos da leitura.

### 4.2. Estruturas Implementadas

Breve descrição das três estruturas utilizadas: 

- **BST**: Para a estrutura BST, foi necessário implementar as funções `insert`, `search`, `create` e `destroy`. Utilizamos o bloco try-catch na função create para lidar com possíveis exceções de alocação de memória.
- **AVL**: Para a operação de inserção na AVL, foi necessário implementar as funções de rotação (`rotateLeft` e `rotateRight`). Essas rotações são fundamentais para manter o balanceamento da árvore após cada inserção. A lógica de balanceamento foi centralizada na função `rebalance`, que precisou das auxiliares `transplant`, `getHeight`, `recomputeHeight`, `getBalance`.
As demais funções, como create, search e destroy, seguem estrutura semelhante à da BST.
- **RBT**: Para a estrutura RBT, a maior dificuldade foi na criação da função `fixUp` utilizada na insert, responsavel por manter as propriedades da RBT. As demais funções, como create, search e destroy, seguem estrutura semelhante à da BST.

## 5. Implementação

### 5.1. Interface de Linha de Comando (CLI)

O programa foi desenvolvido com os seguintes comandos:

```bash
./<arvore> search <n_docs> <diretório>
./<arvore> stats <n_docs> <diretório>
./<arvore> view <n_docs> <diretório>
```
* `<arvore>`: nome do executável da estrutura (ex: bst, avl, rbt)
* `search`: comando que permite realizar buscas por palavras
* `stats`: comando que gera estatísticas de desempenho durante a indexação
* `view` : comando para visualizar a árvore do indice invertido
* `<n_docs>`: número de documentos a indexar
* `<diretório>`: caminho para a pasta contendo os arquivos .txt

```bash
./<arvore> search <n_docs> <diretório>:
```
Esse comando inicia o modo de busca por palavras no índice invertido criado com a estrutura de dados selecionada (bst, avl ou rbt). Após a execução, o programa exibe o seguinte prompt interativo:

```bash
Digite "." para sair.
Palavra buscada:
```
O usuário deve então digitar a palavra que deseja buscar. O sistema realiza a busca da palavra na árvore previamente construída a partir dos documentos. Se a palavra for encontrada, o programa retorna:

* Lista de documentos onde a palavra está presente.
* Tempo de busca em milissegundos.
* Número total de comparações realizadas para localizar a palavra.

Se a palavra não estiver presente em nenhum documento, o programa informa que não foi encontrada.
Esse processo se repete até que o usuário digite um ponto (.), encerrando a sessão de busca.

```bash
./<arvore> stats <n_docs> <diretório>:
```
Nesse caso, o comando constrói a árvore de índice invertido a partir dos n_docs documentos localizados no diretório especificado, e em seguida apresenta um conjunto de estatísticas de desempenho da estrutura.
As métricas exibidas incluem:

* Tempo total de leitura dos documentos.
* Tempo total e tempo médio de inserção das palavras na árvore.
* Tempo médio e tempo máximo de busca.
* Número total de comparações realizadas durante inserções e buscas.
* Altura final da árvore construída.
* Comprimento do menor e do maior caminho da raiz até uma folha.
* Número total de nós na árvore.
* Número total de palavras indexadas (com repetição).

```bash
./<arvore> view <n_docs> <diretório>:
```
chama a função printTree, e mostra a visualização da árvore com n_docs documentos

## 6. Resultados

### 6.1. Tabelas de Desempenho

| Estrutura | Tempo Total de Inserção (ms) | Tempo Médio de Busca (ms) | Comparações (Inserção) | Comparações (Busca) | Altura Média |
|-----------|------------------------------|---------------------------|------------------------|---------------------|--------------|
| BST       |                              |                           |                        |                     |              |
| AVL       |                              |                           |                        |                     |              |
| RBT       |                              |                           |                        |                     |              |

Pequeno texto adicional **aqui**
### 6.2. Gráficos

Inserir **aqui** os gráficos comparativos (tempo, altura, comparações, etc.).

## 7. Análise Comparativa

- **BST**: [vantagens e limitações observadas]
- **AVL**: [vantagens e limitações observadas]
- **RBT**: [vantagens e limitações observadas]

Discussão sobre **aqui**:
- Eficiência nas operações
- Comportamento com diferentes volumes de dados
- Impacto da altura da árvore
- Outros critérios relevantes

## 8. Dificuldades Encontradas

Inicialmente, enfrentamos desafios na definição da estrutura de dados ideal para armazenar as palavras extraídas dos documentos. Após discutir diferentes abordagens, decidimos criar uma struct chamada docs, contendo o ID do documento e um vetor com todos os termos extraídos.
Na BST, tivemos dificuldades para calcular corretamente a altura da árvore, o que foi solucionado com a implementação da função `recomputeHeightTree`.
Na RBT, a função `fixUp` representou o maior obstáculo, exigindo um bom entendimento dos casos em que rotações e trocas de cor devem ser aplicadas para preservar as propriedades da árvore rubro-negra.
Quanto à CLI, a principal dificuldade esteve na estruturação da lógica de funcionamento, principalmente no tratamento de erros e na validação de argumentos. Foi necessário implementar verificações para evitar argumentos inválidos, comandos desconhecidos ou diretórios inexistentes.

## 9. Conclusão

**aqui**

## 10. Referências

**aqui****

---

> **Data de Entrega:** 18/06/2025  
> **Professor:** Matheus Werner 
> **Disciplina:** Estrutura de dados
