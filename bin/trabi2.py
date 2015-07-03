#Import the necessary methods from tweepy library
from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
import json
import sys

cnt = 0
    
def proc (data):
    filt = json.loads(data)
    data = {}            

    if 'user' in filt:
        if 'lang' in filt['user']:
            lang = filt['user']['lang']
            if lang == 'en':
                if 'coordinates' in filt:
                    coord = filt['coordinates']

                    if coord != None:
                        if 'location' in filt['user']:
                            loc = filt['user']['location']
                            if len(loc) > 0:
                                global cnt
                                cnt = cnt + 1
                                print loc                            
                                print filt['text']
                                print coord
                                if 'entities' in filt:
                                    if 'hashtags' in filt['entities']:
                                        shared_tags = []
                                        for hashtag in filt['entities']['hashtags']:
                                            shared_tags.append(hashtag['text'])
                                        print shared_tags

if __name__ == '__main__':
    f = open('tmp', 'r')
    for line in f:
        if len(line) > 1:
            proc(line)
    print cnt
