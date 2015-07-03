import json
import sys
import os
import math
import numpy as np
from matplotlib import pyplot as plt


def get_stats (file):
	count = 0
	sz = os.path.getsize(file)
	c_sz = 0
	f = open(file)

	# Dictionaries
	users = dict()
	

	for line in f:
		c_sz += sys.getsizeof(line)
		try:
			if line != "\n":
				tweet = json.loads(line)
				if 'user' in tweet:
					name = tweet['user']['id']
					if name in users:
						users[name] += 1
					else:
						users[name] = 1
			

			count += 1

			# Print progress
			if count%10000 == 0:
				print str(round(c_sz/float(sz)*100, 2)) + "%"
		except:
			print("Error on line: ")
			print(line)
			continue

	# Quantity of users that tweeted a certain number of tweets on a day
	tweet_count = dict()
	for user in users:
		if users[user] in tweet_count:
			tweet_count[users[user]] += 1
		else:
			tweet_count[users[user]] = 1 			

	print "Tweet Count"
	print tweet_count



def plot_tweet_frequency(freq_map):
	user_count = []
	tweet_count = []
	for key in freq_map:
		tweet_count.append(key)
		user_count.append(math.log(freq_map[key]) + 1)
	print tweet_count
	print user_count
	plt.bar(tweet_count, user_count, alpha=0.4, color='black')
	# plt.xticks(np.arange(0, 40))

	plt.xlabel('#tweets on day')
	plt.ylabel('#users (log)')
	plt.axis([0, 40, 0, max(user_count)])
	plt.savefig('tweet_freq.pdf', format='pdf')


if __name__ == '__main__':
	# This generates the stats
	# get_stats(file='tweets')
	tweet_map = {1: 2494487, 2: 413517, 3: 126848, 4: 52943, 5: 26886, 6: 15359, 7: 9445, 8: 6199, 9: 4394, 10: 3139, 11: 2301, 12: 1831, 13: 1444, 14: 1098, 15: 961, 16: 755, 17: 681, 18: 565, 19: 501, 20: 413, 21: 343, 22: 311, 23: 263, 24: 259, 25: 212, 26: 195, 27: 162, 28: 149, 29: 114, 30: 116, 31: 83, 32: 73, 33: 54, 34: 62, 35: 39, 36: 38, 37: 32, 38: 20, 39: 20, 40: 16, 41: 16, 42: 21, 43: 11, 44: 11, 45: 10, 46: 11, 47: 4, 48: 5, 49: 8, 50: 7, 51: 7, 52: 6, 53: 8, 54: 1, 55: 5, 57: 2, 59: 2, 60: 2, 61: 3, 65: 2, 72: 1, 73: 1}
	plot_tweet_frequency(tweet_map)