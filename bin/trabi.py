#Import the necessary methods from tweepy library
from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
import json
import sys

#Variables that contains the user credentials to access Twitter API 
access_token = "132399683-R2FgZoNS8kgdUR8RAD9oVw3rT1dX32hlo10TLFgi"
access_token_secret = "uF4nRCaXkjnrAoMce85Xv0V3uXuFRM0HkFD0quWALjm19"
consumer_key = "KU24cYenLid8xP7h1hoZ7kFPc"
consumer_secret = "c1I5Ixn2fWfxeLzk1zTipkvFI1fJv8N0eDe7t9gMR63VvVCu76"


#This is a basic listener that just prints received tweets to stdout.
class StdOutListener(StreamListener):

    def __init__(self):
        self.count = 0;
    
    def on_data(self, data):
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
                                    print loc                            
                                    print filt['text']
                                    print coord
                                    if 'entities' in filt:
                                        if 'hashtags' in filt['entities']:
                                            shared_tags = []
                                            for hashtag in filt['entities']['hashtags']:
                                                shared_tags.append(hashtag['text'])
                                            print shared_tags


                    # print filt['text']
                    # if 'followers_count' in filt['user']:
                        # print filt['user']['followers_count']


        return True

    def on_error(self, status):
        print(status)


if __name__ == '__main__':

    while True:
        try:
            #This handles Twitter authetification and the connection to Twitter Streaming API
            l = StdOutListener()
            auth = OAuthHandler(consumer_key, consumer_secret)
            auth.set_access_token(access_token, access_token_secret)
            stream = Stream(auth, l)
            stream.sample()
        except KeyboardInterrupt:
            break
        except:
            continue

try:
    sys.stdout.close()
except:
    pass
try:
    sys.stderr.close()
except:
    pass
