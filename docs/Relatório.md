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

## 3. Metodologia

### 3.1. Leitura dos Documentos

Para a leitura dos dados dos documentos, utilizamos a classe ifstream, fornecida pela biblioteca fstream. Essa classe permite a manipulação de arquivos de entrada de forma eficiente e estruturada. Para o armazenamento dos dados, optamos por criar uma struct chamada docs, que contém o ID do documento e um vetor com todos os termos extraídos da leitura.

### 3.2. Estruturas Implementadas

Breve descrição das três estruturas utilizadas: 

- **BST**: Para a estrutura BST, foi necessário implementar as funções insert, search, create e destroy. Utilizamos o bloco try-catch na função create para lidar com possíveis exceções de alocação de memória.
- **AVL**: Para a operação de inserção na AVL, foi necessário implementar as funções de rotação (`rotateLeft` e `rotateRight`). Essas rotações são fundamentais para manter o balanceamento da árvore após cada inserção. A lógica de balanceamento foi centralizada na função `rebalance`, que precisou das auxiliares `transplant`, `getHeight`, `recomputeHeight`, `getBalance`.
As demais funções, como create, search e destroy, seguem estrutura semelhante à da BST.
- **RBT**: ...

## 4. Implementação

### 4.1. Interface de Linha de Comando (CLI)

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

### 4.2. Funcionalidades Mínimas

- Inserção e busca de palavras
- Coleta de estatísticas de desempenho
- Impressão do índice invertido

Explicação **aqui**

## 5. Resultados

### 5.1. Tabelas de Desempenho

| Estrutura | Tempo Total de Inserção (ms) | Tempo Médio de Busca (ms) | Comparações (Inserção) | Comparações (Busca) | Altura Média |
|-----------|------------------------------|---------------------------|------------------------|---------------------|--------------|
| BST       |                              |                           |                        |                     |              |
| AVL       |                              |                           |                        |                     |              |
| RBT       |                              |                           |                        |                     |              |

Pequeno texto adicional **aqui**
### 5.2. Gráficos

Inserir **aqui** os gráficos comparativos (tempo, altura, comparações, etc.).

## 6. Análise Comparativa

- **BST**: [vantagens e limitações observadas]
- **AVL**: [vantagens e limitações observadas]
- **RBT**: [vantagens e limitações observadas]

Discussão sobre **aqui**:
- Eficiência nas operações
- Comportamento com diferentes volumes de dados
- Impacto da altura da árvore
- Outros critérios relevantes

## 7. Dificuldades Encontradas

Inicialmente, nossa maior dificuldade foi decidir como armazenar as palavras provenientes da leitura dos documentos. Optamos, ao final, por criar uma struct que contém o ID do documento e um vetor com todos os termos extraídos da leitura.
Para a BST encontramos um pouco de dificuldade em calcular a aultura que foi resolvida pela criação da função

## 8. Conclusão

**aqui**

## 9. Referências

**aqui****

---

> **Data de Entrega:** 18/06/2025  
> **Professor:** Matheus Werner 
> **Disciplina:** Estrutura de dados
