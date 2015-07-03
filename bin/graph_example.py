#!/usr/bin/env python
"""
Draw a graph with matplotlib, color by degree.

You must have matplotlib for this to work.
"""
__author__ = """Aric Hagberg (hagberg@lanl.gov)"""
import matplotlib.pyplot as plt

import networkx as nx

G = nx.Graph()
G.add_edge(1, 2)
G.add_edge(2, 3)
G.add_edge(3, 4)
G.add_edge(4, 5)
G.add_edge(5, 6)
pos = nx.spring_layout(G) # positions for all nodes

# nodes
nx.draw_networkx_nodes(G,pos, node_size=300, node_color='white')

# edges
nx.draw_networkx_edges(G, pos, width=1.0)

plt.axis('off')
plt.savefig("ex2.pdf") # save as png
plt.show() # display

