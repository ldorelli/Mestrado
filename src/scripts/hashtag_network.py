# This files just generates a network from a bunch of tweets and writes it in RAW format

# import matplotlib.pyplot as plt
import json
import sys
import os
import math
from progressbar import ProgressBar
import networkx as nx
import matplotlib.pyplot as pyplot
import numpy as np

root_dir = '/media/lfdorelli/Data/Mestrado/Twitter/'

# Generates a network from twitter hashtags and prints in RAW format
# @param file The filename to read tweets from
# @param perc Percentage of the file to be processed. 100 processes the whole file. 
def gen_network(file, perc=100):
	
	sz = os.path.getsize(file)
	c_sz = 0
	count = 0
	f = open(file)
	hashtags = dict()
	user_tags = dict()
	hashtag_idx = dict()

	progress = ProgressBar(sz, 0.01)

	for line in f:
		progress.step(len(line))
		
		try:
			if line != "\n":
				tweet = json.loads(line.decode('utf-8'))

				if 'entities' in tweet:
					shared_tags = []
					for hashtag in tweet['entities']['hashtags']:
						shared_tags.append(hashtag['text'])

					if 'user' in tweet:
						name = tweet['user']['screen_name']
						if name not in user_tags:
							user_tags[name] = []

						if len(shared_tags):
							user_tags[name].append(shared_tags)

					for hashtag in shared_tags:
						if hashtag not in hashtags:
							hashtags[hashtag] = dict()

					for hashtag in shared_tags:
						for neigh in shared_tags:
							if neigh != hashtag:
								if neigh not in hashtags[hashtag]:
									hashtags[hashtag][neigh] = 1
								else:
									hashtags[hashtag][neigh] += 1
			
			progress.show_bar("Current progress: ", "/" + str(perc) + "%")
			
			if progress.get_progress() > perc:
				break
		except:
			continue

	print "Looking at hashtags"
	# Send the result back as a networkx graph
	G = nx.Graph()
	idx = 0
	for hashtag in hashtags.keys():
		G.add_node(hashtag)
 		# G.add_vertex()
 		hashtag_idx[hashtag] = idx
 		idx += 1

 	print "Generating edges"
 	# Generate the edges
	for hashtag in hashtags:
		for neigh in hashtags[hashtag]:
			G.add_edge(hashtag, neigh, weight=float(1.0/hashtags[hashtag][neigh]))
	
	return G, user_tags, hashtag_idx


def print_table (G):
	n = len(G)
	md = 0
	cd = 0
	for nd in G.nodes():
		md += G.degree(nd)
		cd += 1
	md = md/cd
	# print n, ' & ', md, ' & ',  nx.number_connected_components(G), ' \\\\ '
	print nx.betweenness_centrality(G)

if __name__ == '__main__':
	G, h, f = gen_network(root_dir + 'resources/tweets', 100)
	# print 'Generating rangom graph ', str(len(G))
	# GR = nx.fast_gnp_random_graph(len(G), 0.00008)
	# print 'Generating BA ', str(len(G))
	# GBA = nx.barabasi_albert_graph(len(G), min(len(G), 2))
	# # nx.write_gexf(G, root_dir + 'graphs/gexf/hashtag_net.gexf')
	# print_table(G)
	# print_table(GR)
	# print_table(GBA

	hp = {}
	for user in h:w
		for hashlist in h[user]:
			x = len(hashlist)
			if x in hp:
				hp[x] += 1
			else:
				hp[x] = 1

	bins = []
	v = []
	for x in hp:
		bins.append(x)
		v.append(hp[x])

	pyplot.loglog(bins, v, color='green')
	pyplot.xlabel(r'Hashtags/Post', fontsize='xx-large')
	pyplot.ylabel(r'Frequencia', fontsize='xx-large')
	# pyplot.axis([0, 100, 0, 300000])
	pyplot.grid(True)
	pyplot.show()
