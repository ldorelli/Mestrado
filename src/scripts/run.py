#!/usr/bin/env python
import matplotlib.pyplot as plt

import networkx as nx

idx = 1
labels = {}
tw_labels = {}
tag_labels = {}

def insertKey(T, w, i, G, lab_dic=tag_labels):
  
  global idx

  if i == len(w):
    return

  if w[i] not in T['nodes']:
    T['nodes'][w[i]] = { 'nodes' : dict(), 'idx' : idx }
    G.add_node(idx, label = w[i]) 
    labels[idx] = w[i]
    lab_dic[idx] = w[i]
    idx += 1
    G.add_edge(T['idx'], T['nodes'][w[i]]['idx'])  
 
  insertKey(T['nodes'][w[i]], w, i + 1, G, lab_dic)

#  Main code  
if __name__ == '__main__':

  T = { 'idx' : 0, 'nodes' : dict() }
  G = nx.Graph() 
  insertKey(T, 'TEAMWORK', 0, G, tw_labels)
  insertKey(T, 'ICPC', 0, G, tw_labels)
  insertKey(T, 'TRAVEL', 0, G, tw_labels)
  insertKey(T, 'OPPORTUNITIES', 0, G, tw_labels)
  insertKey(T, 'CHALLENGE', 0, G, tw_labels)
  insertKey(T, 'COMPETITION', 0, G, tw_labels)
  insertKey(T, 'NETWORKING', 0, G, tw_labels)
  insertKey(T, 'CREATIVITY', 0, G, tw_labels)
  insertKey(T, 'INNOVATION', 0, G, tw_labels)

  insertKey(T, 'DP', 0, G)
  insertKey(T, 'BINARY SEARCH', 0, G)
  insertKey(T, 'DIJKSTRA', 0, G)
  insertKey(T, 'TEAMWORK', 0, G)
  insertKey(T, 'TWO POINTERS', 0, G)
  insertKey(T, 'TOPOSORT', 0, G)
  insertKey(T, 'GRUNDY NUMBER', 0, G)
  insertKey(T, 'LINE SWEEP', 0, G)
  insertKey(T, 'PROBABILITIES', 0, G)
  insertKey(T, 'IMPLEMENTATION', 0, G)
  insertKey(T, 'DIVIDE AND CONQUER', 0, G)
  insertKey(T, 'MATRIX', 0, G)
  insertKey(T, 'MATCHING', 0, G)
  insertKey(T, 'MAX FLOW', 0, G)
  insertKey(T, 'MATH', 0, G)
  insertKey(T, 'PARSING', 0, G)
  insertKey(T, 'GEOMETRY', 0, G)
  insertKey(T, 'GRAPH', 0, G)
  insertKey(T, 'GRAPH COLORING', 0, G)
  insertKey(T, 'SEGMENT TREE', 0, G)
  insertKey(T, 'UNION FIND', 0, G)
  insertKey(T, 'RANDOMIZED', 0, G)
  insertKey(T, 'TREE', 0, G)
  insertKey(T, 'MIN MAX', 0, G)
  insertKey(T, 'MAX FLOW', 0, G)
  insertKey(T, 'MIN COST FLOW ', 0, G)
  insertKey(T, 'PARSING', 0, G)
  insertKey(T, 'SPANNING TREE', 0, G)
  insertKey(T, '', 0, G)


  pos = nx.graphviz_layout(G=G, prog='dot', args='')
  for ele in pos:
    pos[ele] = (2.35 * pos[ele][0],  pos[ele][1]) 


  fig = plt.figure(figsize=(12, 15), dpi=100)
  plt.axis('off')
  # fig.set_facecolor("#000000")
   
  #  Draw nodes and edges
  nx.draw_networkx_labels(G, pos, tw_labels, font_size=12, font_color='black', font_weight='bold')
  nx.draw_networkx_labels(G, pos, tag_labels, font_size=12, font_color='black')
  nx.draw_networkx_edges(G, pos, width=0.2, alpha=1.0, edge_color='black', arrows=True)
  # nx.draw_networkx_nodes(G, pos, node_color='white', node_size=300, alpha=0.3, linewidths=0.1)
  
  plt.savefig("labels_and_colors.png") # save as png
  plt.show() # display)
  nx.write_dot(G, 'graph.dot')