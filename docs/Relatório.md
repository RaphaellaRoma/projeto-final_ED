# Trabalho A2: Índice Invertido e Análise Comparativa de Estruturas de Dados

## 1. Introdução

Um **índice invertido** é uma estrutura de dados fundamental em sistemas de recuperação de informação, sendo amplamente utilizada em mecanismos de busca, bancos de dados e aplicações que lidam com grandes volumes de texto. Sua principal finalidade é possibilitar a recuperação eficiente de documentos ou registros que contenham um determinado termo ou conjunto de termos. Nessa estrutura, os dados são organizados por termos (palavras), e cada termo aponta para uma lista de documentos ou páginas da web em que ocorre.

Essa abordagem é especialmente vantajosa em coleções extensas de documentos, onde realizar buscas sequenciais em todos os arquivos seria inviável do ponto de vista computacional. Para além do domínio textual, os índices invertidos também têm aplicações relevantes em áreas como a bioinformática, sendo empregados, especialmente na montagem de sequências de DNA.

Essa estrutura de dados armazena um mapeamento entre conteúdos (como palavras ou números) e suas localizações em um documento ou em um conjunto de documentos. Em outras palavras, isso significa que a estrutura permite responder, perguntas do tipo: “quais documentos contêm o termo X?”, e até mesmo “em quais posições, dentro desses documentos, esse termo aparece?”, dependendo do nível de detalhe adotado.

Existem dois tipos principais de índices invertidos:

**Índice Invertido de Nível de Registro**: associa cada termo a uma lista de documentos nos quais ele aparece, sem indicar a posição exata dentro de cada documento. É mais simples e eficiente em termos de espaço e tempo de processamento, sendo ideal para buscas que não exigem contexto posicional.

**Índice Invertido em Nível de Palavra**: além de listar os documentos em que o termo ocorre, esse tipo de índice também registra as posições exatas de cada ocorrência dentro dos documentos. Embora proporcione funcionalidades adicionais, também demanda uma maior capacidade de armazenamento e processamento para ser criado.

**Vantagens**:

* Maior eficiencia em buscas textuais: permite pesquisas rápidas de texto completo, mesmo em grandes volumes de dados, o que o torna ideal para aplicações como mecanismos de busca, ao custo de maior processamento quando um documento é adicionado ao banco de dados.
* Implementação relativamente simples.
* Ampla adoção: é uma das estruturas de dados mais popular em sistemas de recuperação de informação, com aplicações em larga escala em mecanismos de busca.

**Desvantagens**:

* Sobrecarga de armazenamento: especialmente quando se armazenam informações detalhadas como posições das palavras (índice de nível de palavra).
* Custos de manutenção: operações como inserção, exclusão ou atualização de documentos exigem a reconstrução parcial ou completa de listas associadas, o que pode ser computacionalmente caro.
* Ordenação limitada por relevância: os registros são, por padrão, retornados na ordem de ocorrência nas listas invertidas, o que pode não refletir sua relevância ou utilidade esperada exigindo técnicas adicionais de ranqueamento para resultados mais úteis.

O presente relatório apresenta a implementação em C++ de um índice invertido utilizando três diferentes estruturas de dados: Árvore Binária de Busca (BST), Árvore AVL (AVL) e Árvore Rubro-Negra (RBT). O objetivo principal é avaliar e comparar o desempenho dessas estruturas nas operações de inserção e busca de palavras em um corpus textual real.

## 2. Conceitos basicos

1. Uma **Árvore Binária de Busca (Binary Search Tree - BST)** é uma estrutura de dados em forma de árvore binária que mantém uma propriedade especial de ordenação, permitindo a realização de buscas, inserções e remoções de forma eficiente.

Propriedade fundamental da BST:
Para cada nó da árvore, que armazena uma chave, aplicam-se as seguintes condições:

* Todas as chaves presentes na subárvore esquerda são menores que a chave do nó atual.
* Todas as chaves presentes na subárvore direita são maiores que a chave do nó atual.

2. As **Árvores AVL** são uma variação das Árvores Binárias de Busca (BSTs) que buscam resolver o problema do desequilíbrio estrutural que pode surgir em inserções ou remoções repetidas. Em uma BST convencional, a árvore pode se tornar degenerada (muito inclinada para um dos lados), o que compromete a eficiência das operações.

A proposta das árvores AVL é manter a árvore **balanceada** automaticamente após cada operação, garantindo que as operações de busca, inserção e remoção mantenham uma complexidade próxima a `O(log n)`.

Para cada nó `n` da árvore, define-se o **fator de balanceamento** (*Balance Factor – BF*) como:
BF(n) = altura(subárvore direita) - altura(subárvore esquerda)

A árvore é considerada balanceada no estilo AVL se, e somente se:
-1 ≤ BF(n) ≤ 1, para todo nó n

Sempre que uma operação causar violação dessa condição, a estrutura da árvore é ajustada automaticamente por meio de **rotações simples ou duplas**, de forma a restaurar o balanceamento.

3. Uma **árvore rubro-negra** é uma árvore binária de busca que incorpora uma informação adicional em cada nó: sua cor, que pode ser vermelha ou preta. Essa coloração é utilizada para impor regras estruturais que garantem que a árvore permaneça aproximadamente balanceada, mantendo a eficiência das operações básicas (busca, inserção, remoção) com complexidade `O(log n)`.

Uma árvore rubro-negra deve obedecer às seguintes restrições estruturais:

* Todo nó é vermelho ou preto.
* A raiz é sempre preta.
* Todas as folhas (nós NIL) são pretas.
* Se um nó é vermelho, então seus dois filhos (caso existam) são obrigatoriamente pretos.
* Todo caminho simples de um nó até uma folha descendente contém o mesmo número de nós pretos.

Essas propriedades garantem que a árvore tenha uma altura limitada em relação ao número de elementos, mantendo seu desempenho eficiente mesmo após várias operações.

Alguns termos fundamentais que seram abordados ao longo desse relatorio:

* Nó: Unidade básica da árvore. Cada nó armazena um valor (ou dado) e ponteiros para seus filhos (outros nós ligados a ele). 
* Raiz: É o nó mais alto da hierarquia, o único que não tem pai. Toda árvore tem exatamente uma raiz. 
* Folha: Nó que não possui filhos.
* Subárvore: Qualquer nó da árvore, junto com seus descendentes. Cada nó define uma subárvore. 

Conceitos estruturais
* Profundidade de um nó: Número de arestas da raiz até esse nó.
* Altura de um nó: Número de arestas no caminho mais longo entre esse nó e uma de suas folhas.

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

Este projeto está organizado de forma modular para facilitar o desenvolvimento, testes e análise de desempenho das diferentes estruturas de dados usadas na construção de um índice invertido. Abaixo segue a descrição de cada diretório e arquivo:

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
├── data_new/
│   ├── Nova base de dados de documentos (.txt)
│
├── data_test/
│   ├── Nova base de dados de documentos para analise de casos degenerados (.txt)
│
├── Makefile  # Para compilar os arquivos da pasta `src/` e gerar os executáveis na pasta `build/`
│
├── README.md # Descrição, instruções de compilação e execução do Projeto
```

### `src/`
Contém o código-fonte principal:

- `main_bst.cpp`, `main_avl.cpp`, `main_rbt.cpp`: interfaces de linha de comando para indexação e busca com BST, AVL e RBT respectivamente.
- `bst.cpp`/`bst.h`, `avl.cpp`/`avl.h`, `rbt.cpp`/`rbt.h`: implementações completas das estruturas de árvore.
- `tree_utils.cpp`/`tree_utils.h`: estruturas auxiliares e funções como criação de nós, cálculo de altura, busca, exibição da árvore etc.
- `data.cpp`/`data.h`: responsáveis pela leitura do diretório de dados e carregamento dos arquivos `.txt`.
- `test_bst.cpp`, `test_avl.cpp`, `test_rbt.cpp`: testes unitários para as implementações.

### `build/`
Armazena os executáveis gerados após a compilação. Mantém o projeto organizado ao separar os binários do código-fonte.

### `analysis/`
Scripts responsáveis pela coleta de métricas e análise de desempenho:

- `analysis_avl.cpp`, `analysis_bst.cpp`, `analysis_rbt.cpp`: scripts para testes e coleta de dados.
- `metrics.cpp` / `metrics.h`: funções auxiliares para medir tempo de execução, número de comparações, altura das árvores, entre outros.
- `Makefile`: compila os arquivos da pasta `analysis/`.
- `results/`: arquivos `.csv` contendo os dados brutos coletados durante os testes.
- `plots/`:
  - `plot_analysis.py`: script Python que gera gráficos a partir dos dados em `.csv`.

### `docs/`
Documentação do projeto:

- `Relatório (PDF ou .md)`: relatório técnico contendo explicações, metodologia, resultados e conclusões.
- `graphs_tables/`: gráficos e tabelas gerados nas análises.

### `data/`, `data_new/`, `data_test/`
Bases de dados usadas nos experimentos:

- `data/`: base de documentos principal.
- `data_new/`: nova base textual para testes complementares.
- `data_test/`: base com casos específicos (ex: degenerados, palavras repetidas, arquivos vazios).

### `Makefile`
Compila os arquivos da pasta `src/`, gerando os executáveis correspondentes na pasta `build/`.

### `README.md`
Arquivo que contém a descrição geral do projeto, instruções de compilação, execução e explicações sobre a organização do repositório.

## 4. Metodologia

Neste projeto, implementamos um índice invertido em nível de registro, no qual cada termo extraído do corpus textual é associado a uma lista de documentos que o contêm.

### 4.1. Leitura dos Documentos

Para a leitura dos dados dos documentos, utilizamos a classe `ifstream`, fornecida pela biblioteca `fstream`. Essa classe permite a manipulação de arquivos de entrada de forma eficiente e estruturada. Para o armazenamento dos dados, optamos por criar uma struct chamada docs, que contém o ID do documento e um vetor com todos os termos extraídos da leitura.

Nossa basse de dados, encontrada nos dirtorios,

- `data/`: base de documentos principal, contem 10103 arquivos `.txt`, com palavras em português sem acentuação.
- `data_new/`: nova base textual para testes complementares, contem arquivos `.txt`, com palavras em inglês.
- `data_test/`: base com casos específicos, contém .

### 4.2. Estruturas Implementadas

- **BST**: Para a estrutura BST, foi necessário implementar as funções `insert`, `search`, `create` e `destroy`. Utilizamos o bloco try-catch na função create para lidar com possíveis exceções de alocação de memória.
- **AVL**: Para a operação de inserção na AVL, foi necessário implementar as funções de rotação (`rotateLeft` e `rotateRight`). Essas rotações são fundamentais para manter o balanceamento da árvore após cada inserção. A lógica de balanceamento foi centralizada na função `rebalance`, que precisou das auxiliares `transplant`, `getHeight`, `recomputeHeight`, `getBalance`.
As demais funções, como create, search e destroy, seguem estrutura semelhante à da BST.
- **RBT**: Para a estrutura RBT, a maior dificuldade foi na criação da função `fixUp` utilizada na insert, responsável por manter as propriedades da RBT. As demais funções, como create, search e destroy, seguem estrutura semelhante à da BST.

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

Para a AVL, encontramos uma grande dificuldade em entender o comportamento do balanceamento da árvore como um todo. Em especial, nos questionamos se a diferença entre o maior e o menor galho (ou seja, entre as profundidades das folhas mais distantes) poderia ser maior do que 1. Isso, pois, a regra fundamental da AVL exige que, para todo nó, a diferença entre as alturas de suas subárvores esquerda e direita seja no máximo 1. No entanto, essa condição é local: ela se aplica a cada nó individualmente, e não à árvore inteira. Assim, é possível que a diferença entre o caminho mais curto e o mais longo da árvore exceda 1, desde que todos os nós intermediários respeitem o fator de balanceamento definido. Por exemplo,

```mathematica
          ●
        /   \
      ●       ●
     / \     /  \
   ●    ●  ●    ●
  /        / \    \
●        ●   ●    ●
          / \
        ●   ●
```

uma arvore balanciada com galho menor 3 e galho maior 5.

Na RBT, a função `fixUp` representou o maior obstáculo, exigindo um bom entendimento dos casos em que rotações e trocas de cor devem ser aplicadas para preservar as propriedades da árvore rubro-negra.

Quanto à CLI, a principal dificuldade esteve na estruturação da lógica de funcionamento, principalmente no tratamento de erros e na validação de argumentos. Foi necessário implementar verificações para evitar argumentos inválidos, comandos desconhecidos ou diretórios inexistentes.

## 9. Conclusão

**aqui**

## 10. Referências

[1] GeeksforGeeks. *Inverted Index*. Disponível em: [https://www.geeksforgeeks.org/inverted-index/](https://www.geeksforgeeks.org/inverted-index/). Acesso em: 16 jun. 2025.

[2] Wikipedia. *Inverted index*. Disponível em: [https://en.wikipedia.org/wiki/Inverted_index](https://en.wikipedia.org/wiki/Inverted_index). Acesso em: 16 jun. 2025.


---

> **Data de Entrega:** 18/06/2025  
> **Professor:** Matheus Werner 
> **Disciplina:** Estrutura de dados
