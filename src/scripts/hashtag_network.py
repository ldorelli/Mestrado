# This files just generates a network from a bunch of tweets and writes it in RAW format

# import matplotlib.pyplot as plt
import json
import sys
import os
import math
from progressbar import ProgressBar
from graph_tool.all import *



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

	# Send the result back as a networkx graph
	G = Graph()
	idx = 0
	for hashtag in hashtags.keys():
		# G.add_node(hashtag)
 		G.add_vertex()
 		hashtag_idx[hashtag] = idx
 		idx += 1

 	e_prop = G.new_edge_property("double")
 	# Generate the edges
	for hashtag in hashtags:
		for neigh in hashtags[hashtag]:
			# G.add_edge(hashtag, neigh, weight=float(1.0/hashtags[hashtag][neigh]))
			G.add_edge(G.vertex(hashtag_idx[hashtag]), G.vertex(hashtag_idx[neigh]))
			e_prop[G.edge(G.vertex(hashtag_idx[hashtag]), G.vertex(hashtag_idx[neigh]))] = float(1.0/hashtags[hashtag][neigh])
	return G, e_prop, user_tags, hashtag_idx


if __name__ == '__main__':
	gen_network(root_dir + 'resources/tweets', 3)