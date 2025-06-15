# Codigo Python para ler os CSVs e gerar graficos
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt

bst = pd.read_csv('../results/bst_results.csv')
avl = pd.read_csv('../results/bst_results.csv')
rbt = pd.read_csv('../results/bst_results.csv')

# Filtra os documentos de 1000 em 1000
bst_filtered = bst[bst['Documentos'] % 1000 == 0]
avl_filtered = avl[avl['Documentos'] % 1000 == 0]
rbt_filtered = rbt[rbt['Documentos'] % 1000 == 0]

#####  Tempo total de inserção (barras)  #####
# Para deslocar as barras (senão sobrepõem)
x = np.array(bst_filtered['Documentos'])
width = 150  # largura de cada barra

plt.figure(figsize=(8, 5))
plt.bar(x - width, bst_filtered['TempoTotalInsercao'], width=width, label='BST', color="#1E555C")
plt.bar(x,        avl_filtered['TempoTotalInsercao'], width=width, label='AVL', color="#F15152")
plt.bar(x + width, rbt_filtered['TempoTotalInsercao'], width=width, label='RBT', color="#D39236")

plt.title('Tempo Total de Inserção por Estrutura')
plt.xlabel('Número de Documentos')
plt.ylabel('Tempo Total de Inserção (s)')
plt.xticks(x)
plt.legend()
plt.tight_layout()
plt.savefig('tempo_insercao.png')
plt.show()

#####  Tempo total de busca (barras)  #####
plt.figure(figsize=(8, 5))
plt.bar(x - width, bst_filtered['TempoTotalBusca'], width=width, label='BST', color="#1E555C")
plt.bar(x,        avl_filtered['TempoTotalBusca'], width=width, label='AVL', color="#CBDFBD")
plt.bar(x + width, rbt_filtered['TempoTotalBusca'], width=width, label='RBT', color="#F15152")

plt.title('Tempo Total de Busca por Estrutura')
plt.xlabel('Número de Documentos')
plt.ylabel('Tempo Total de Busca (s)')
plt.xticks(x)
plt.legend()
plt.tight_layout()
plt.savefig('tempo_busca.png')
plt.show()