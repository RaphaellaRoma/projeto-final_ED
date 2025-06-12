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

## Instruções para compilar programa principal:

> **Importante:** Execute os comandos `make` a partir da **raiz do projeto**.

> Os executáveis são gerados na pasta `build/` após a compilação.

- Para compilar **todos os programas da pasta `src/`** de uma vez (BST, AVL, RBT e os testes):
  ```bash
  make
  ```
  
### Para compilar individualmente:

#### Compilar árvores principais:

- Compilar BST  
  ```bash
  make bst
  ```

- Compilar AVL
  ```bash
  make avl
  ```

- Compilar RBT
  ```bash
  make rbt
  ```
Observação: A implementação da Árvore Rubro-Negra (RBT) ainda não está completa.

### Compilar Testes:

- BST
  ```bash
  make test_bst
  ```

- AVL
  ```bash
  make test_avl
  ```

- RBT
  ```bash
  make test_rbt
  ```
Observação: Testes para a Árvore Rubro-Negra (RBT) ainda não estão disponíveis.

### Limpar arquivos compilados (clean)

Para remover os executáveis e arquivos temporários gerados pela compilação, use:

```bash
make clean
```

## Instruções de Execução e Interface de Linha de Comando (CLI)

> **Importante:** Todos os comandos a seguir devem ser executados **a partir da raiz do projeto**, ou seja, da pasta `projeto-final_ED/`. Isso garante que os caminhos relativos (como `data/`, `build/` e `src/`) funcionem corretamente.  

Após compilar os programas (com `make` ou individualmente), os executáveis estarão disponíveis na pasta `build/`.  

Cada programa principal (`bst`, `avl`, `rbt`) oferece uma **interface de linha de comando (CLI)** com os seguintes modos de execução:

```bash
./build/<arvore> <modo> <n_docs> <diretorio>
```

- `<arvore>`: escolha entre `bst`, `avl` ou `rbt`
- `<modo>`: tipo de operação que deseja realizar:
  - `search`: permite indexar os documentos e buscar palavras interativamente
  - `stats`: exibe estatísticas da estrutura gerada (tempo, comparações, altura, etc.)
  - `view`: imprime visualmente a árvore construída 
- `<n_docs>`: quantidade de documentos a serem lidos (ex: `10`, `50`, `100`, etc.)
- `<diretorio>`: caminho para a pasta onde estão os arquivos `.txt` (ex: `data/`)

### Exemplos de uso:

#### 1. **Buscar palavras após indexação** (`search`)
```bash
./build/avl search 10 data/
```
Será exibido:
```
Digite . para sair. Palavra buscada:
```

#### 2. **Exibir estatísticas da árvore** (`stats`)
```bash
./build/bst stats 50 data/
```
Mostra métricas como número de comparações, altura da árvore, tempo médio de inserção e busca, etc.

#### 3. **Visualizar a árvore gerada** (`view`)
```bash
./build/avl view 20 data/
```
Imprime no terminal uma representação visual da árvore.

## Execução dos Testes

>  **Importante:** Os testes também devem ser executados a partir da **raiz do projeto**, pois os arquivos de entrada e caminhos relativos são esperados neste contexto.

Execute os testes unitários diretamente pelos executáveis gerados na pasta `build/`:

```bash
./build/test_bst
./build/test_avl
./build/test_rbt
```
> Observação: os testes da RBT ainda não estão implementados.

## Observações Adicionais sobre a Análise Comparativa

A pasta [`analysis/`](analysis/) contém um conjunto separado de códigos voltados para a **análise comparativa** das estruturas (BST, AVL, RBT).

### Makefile independente

> O arquivo `Makefile` dentro da pasta `analysis/` é **independente** do `Makefile` principal da raiz.  
> Ele foi projetado exclusivamente para compilar os arquivos de análise (`analysis_bst.cpp`, `analysis_avl.cpp`, `analysis_rbt.cpp`).

Para compilar todos os programas de análise:

```bash
cd analysis/
make
```

Assim como no Makefile principal, os executáveis também são gerados na pasta `build/`.

### Execução da Análise

Para executar os programas gerados, é necessário estar dentro da pasta `analysis/` e rodar os comandos utilizando o caminho relativo para os executáveis na pasta `build/`. Por exemplo:

```bash
cd analysis/
../build/analysis_bst
../build/analysis_avl
../build/analysis_rbt
```
Essa forma garante que os arquivos de entrada e saída sejam corretamente localizados e criados na estrutura de pastas esperada pelo programa.

### Geração de CSVs

Cada programa de análise gera automaticamente arquivos `.csv` na pasta `analysis/results/`, contendo os dados brutos coletados por estrutura. Esses arquivos servem como base para a criação dos gráficos e tabelas.

### Visualização dos Resultados

A pasta `analysis/plots/` contém o script `plot_analysis.py`, escrito em Python, que é utilizado para:

- Ler os CSVs gerados
- Criar gráficos de comparação entre as árvores
- Exportar imagens e tabelas para uso em relatórios

> Os gráficos gerados são salvos na pasta `docs/graphs_tables/` para inclusão no relatório final.

## Relatório Final

O relatório completo do projeto está disponível na pasta [`docs/`](docs/), no arquivo:

- [Relatório.md](docs/Relatório.md)

Você pode abrir diretamente este arquivo para consultar toda a documentação detalhada do projeto.




