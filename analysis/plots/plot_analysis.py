# Codigo Python para ler os CSVs e gerar graficos
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt

bst = pd.read_csv('../results/bst_results.csv')
avl = pd.read_csv('../results/avl_results.csv')
rbt = pd.read_csv('../results/bst_results.csv')

# Filtra os documentos de 1000 em 1000
bst_filtered = bst[bst['Documentos'] % 1000 == 0]
avl_filtered = avl[avl['Documentos'] % 1000 == 0]
rbt_filtered = rbt[rbt['Documentos'] % 1000 == 0]

x = np.array(bst_filtered['Documentos'])

# Cores
bst = '#5BC0EB'
avl = '#FF7F11'
rbt = '#9BC53D'

#####  Tempo de inserção  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['TempoTotalInsercao'], marker='o', label='BST', color=bst)
ax0.plot(x, avl_filtered['TempoTotalInsercao'], marker='o', label='AVL', color=avl)
ax0.plot(x, rbt_filtered['TempoTotalInsercao'], marker='o', label='RBT', color=rbt)
ax0.set_title('Tempo Total de Inserção')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Tempo Total de Inserção (s)')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['TempoMedioInsercao'], marker='o' , label='BST', color=bst)
ax1.plot(x, avl_filtered['TempoMedioInsercao'], marker='o' , label='AVL', color=avl)
ax1.plot(x, rbt_filtered['TempoMedioInsercao'], marker='o' , label='RBT', color=rbt)
ax1.set_title('Tempo Médio de Inserção por Palavra')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Tempo Médio de Inserção (s)')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Tempo de Inserção', fontsize=15)
plt.savefig('tempo_insercao.png')


#####  Tempo de busca  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['TempoTotalBusca'], marker='o', label='BST', color=bst)
ax0.plot(x, avl_filtered['TempoTotalBusca'], marker='o', label='AVL', color=avl)
ax0.plot(x, rbt_filtered['TempoTotalBusca'], marker='o', label='RBT', color=rbt)
ax0.set_title('Tempo Total de Busca')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Tempo Total de Busca (s)')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['TempoMedioBusca'], marker='o' , label='BST', color=bst)
ax1.plot(x, avl_filtered['TempoMedioBusca'], marker='o' , label='AVL', color=avl)
ax1.plot(x, rbt_filtered['TempoMedioBusca'], marker='o' , label='RBT', color=rbt)
ax1.set_title('Tempo Médio de Busca por Palavras')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Tempo Médio de Busca (s)')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Tempo de Busca', fontsize=15)
plt.savefig('tempo_busca.png')


#####  Número de Comparações  #####
plt.style.use('seaborn-v0_8')
fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(14, 5))
plt.style.use('default')
#####  Total  #####
ax0.plot(x, bst_filtered['ComparacoesInsercao'], marker='o', label='BST', color=bst)
ax0.plot(x, avl_filtered['ComparacoesInsercao'], marker='o', label='AVL', color=avl)
ax0.plot(x, rbt_filtered['ComparacoesInsercao'], marker='o', label='RBT', color=rbt)
ax0.set_title('Número de Comparações na Inserção')
ax0.set_xlabel('Número de Documentos')
ax0.set_ylabel('Número de Comparações')
ax0.set_xticks(x)
ax0.legend()
ax0.grid(alpha=0.5)
#####  Médio  #####
ax1.plot(x, bst_filtered['ComparacoesBusca'], marker='o' , label='BST', color=bst)
ax1.plot(x, avl_filtered['ComparacoesBusca'], marker='o' , label='AVL', color=avl)
ax1.plot(x, rbt_filtered['ComparacoesBusca'], marker='o' , label='RBT', color=rbt)
ax1.set_title('Número de Comparações na Busca')
ax1.set_xlabel('Número de Documentos')
ax1.set_ylabel('Número de Comparações')
ax1.set_xticks(x)
ax1.legend()
ax1.grid(alpha=0.5)

plt.subplots_adjust(top=0.85)
fig.suptitle('Número de Comparações', fontsize=15)
plt.savefig('num_comparacoes.png')


#####  Altura  #####
plt.style.use('seaborn-v0_8')
plt.figure(figsize=(10, 5))
plt.bar(x-250, bst_filtered['Altura'], width=250, label='BST', color=bst)
plt.bar(x    , avl_filtered['Altura'], width=250, label='AVL', color=avl)
plt.bar(x+250, rbt_filtered['Altura'], width=250, label='RBT', color=rbt)
plt.xlabel('Número de Documentos')
plt.ylabel('Altura')
plt.xticks(x)
plt.style.use('default')
plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.20), ncol=3)
plt.grid(False)

plt.tight_layout()
plt.subplots_adjust(top=0.88)
plt.title('Altura das Árvores\n', fontsize=15)
plt.savefig('altura.png')


#####  Tamanho dos galhos  #####
plt.style.use('seaborn-v0_8')
plt.figure(figsize=(10, 5))
plt.bar(x-250, bst_filtered['MaiorGalho'], width=250, label='BST - maior galho', color="#D5F0FC", edgecolor=bst, hatch='//', linewidth=0.8)
plt.bar(x-250, bst_filtered['MenorGalho'], width=250, label='BST - menor galho', color=bst, edgecolor='#148EC2')
plt.bar(x    , avl_filtered['MaiorGalho'], width=250, label='AVL - maior galho', color="#FCE1CA", edgecolor=avl, hatch='//', linewidth=0.8)
plt.bar(x    , avl_filtered['MenorGalho'], width=250, label='AVL - menor galho', color=avl, edgecolor="#C75F03")
plt.bar(x+250, rbt_filtered['MaiorGalho'], width=250, label='RBT - maior galho', color="#E3E9D8", edgecolor=rbt, hatch='//', linewidth=0.8)
plt.bar(x+250, rbt_filtered['MenorGalho'], width=250, label='RBT - menor galho', color=rbt, edgecolor="#6D9616")
plt.xlabel('Número de Documentos')
plt.ylabel('Tamanho do Galho')
plt.xticks(x)
plt.style.use('default')
plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.20), ncol=3)
plt.grid(False)

plt.tight_layout()
plt.subplots_adjust(top=0.88)
plt.title('Tamanho do Maior e do Menor Galho\n', fontsize=15)
plt.savefig('tamanho_galho.png')


plt.show()

