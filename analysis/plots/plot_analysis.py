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

x = np.array(bst_filtered['Documentos'])

#####  Tempo de inserção  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['TempoTotalInsercao'], marker='o', label='BST', color="#1E555C")
ax0.plot(x, avl_filtered['TempoTotalInsercao'], marker='o', label='AVL', color="#F15152")
ax0.plot(x, rbt_filtered['TempoTotalInsercao'], marker='o', label='RBT', color="#D39236")
ax0.set_title('Tempo Total de Inserção')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Tempo Total de Inserção (s)')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['TempoMedioInsercao'], marker='o' , label='BST', color="#1E555C")
ax1.plot(x, avl_filtered['TempoMedioInsercao'], marker='o' , label='AVL', color="#F15152")
ax1.plot(x, rbt_filtered['TempoMedioInsercao'], marker='o' , label='RBT', color="#D39236")
ax1.set_title('Tempo Médio de Inserção por Palavra')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Tempo Médio de Inserção (s)')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Tempo de Inserção', fontsize=15)
plt.savefig('tempo_insercao.png')
plt.show()


#####  Tempo de busca  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['TempoTotalBusca'], marker='o', label='BST', color="#1E555C")
ax0.plot(x, avl_filtered['TempoTotalBusca'], marker='o', label='AVL', color="#F15152")
ax0.plot(x, rbt_filtered['TempoTotalBusca'], marker='o', label='RBT', color="#D39236")
ax0.set_title('Tempo Total de Busca')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Tempo Total de Busca (s)')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['TempoMedioBusca'], marker='o' , label='BST', color="#1E555C")
ax1.plot(x, avl_filtered['TempoMedioBusca'], marker='o' , label='AVL', color="#F15152")
ax1.plot(x, rbt_filtered['TempoMedioBusca'], marker='o' , label='RBT', color="#D39236")
ax1.set_title('Tempo Médio de Busca por Palavras')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Tempo Médio de Busca (s)')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Tempo de Busca', fontsize=15)
plt.savefig('tempo_busca.png')
plt.show()


#####  Número de Comparações  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['ComparacoesInsercao'], marker='o', label='BST', color="#1E555C")
ax0.plot(x, avl_filtered['ComparacoesInsercao'], marker='o', label='AVL', color="#F15152")
ax0.plot(x, rbt_filtered['ComparacoesInsercao'], marker='o', label='RBT', color="#D39236")
ax0.set_title('Número de Comparações na Inserção')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Número de Comparações')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['ComparacoesBusca'], marker='o' , label='BST', color="#1E555C")
ax1.plot(x, avl_filtered['ComparacoesBusca'], marker='o' , label='AVL', color="#F15152")
ax1.plot(x, rbt_filtered['ComparacoesBusca'], marker='o' , label='RBT', color="#D39236")
ax1.set_title('Número de Comparações na Busca')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Número de Comparações')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Número de Comparações', fontsize=15)
plt.savefig('num_comparacoes.png')
plt.show()



