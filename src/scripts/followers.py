#Import the necessary methods from tweepy library
from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
import tweepy 
import time
import json
from pymongo import MongoClient

#Variables that contains the user credentials to access Twitter API 
access_token = "132399683-R2FgZoNS8kgdUR8RAD9oVw3rT1dX32hlo10TLFgi"
access_token_secret = "uF4nRCaXkjnrAoMce85Xv0V3uXuFRM0HkFD0quWALjm19"
consumer_key = "KU24cYenLid8xP7h1hoZ7kFPc"
consumer_secret = "c1I5Ixn2fWfxeLzk1zTipkvFI1fJv8N0eDe7t9gMR63VvVCu76"

#  Cliente PyMongo
client = MongoClient()
db = client.twitter_follower_network

# Get followers of a user and some extra data
def getFollowerData(screen_name):
    global api
    while True:
        try:
            posts = db.posts
            if posts.find_one({'__id' : screen_name }) == None:
                user = api.get_user(screen_name)
            
                print 'Searching for ', screen_name
                d = { 
                    '__id' : screen_name,
                    'name' : user.name,
                    'id' : user.id,
                    'friends_count': user.friends_count,
                    'followers_count': user.followers_count,
                    'followers_ids' : user.followers_ids()
                }
                post_id = posts.insert(d)
            
            return

        except tweepy.TweepError, error:
            print type(error)
            print str(error)

            if error.message[0]['message'] == 'Not authorized.':
                print 'Cant access user data'
                return

            if error.message[0]['message'] == 'User has been suspended.':
                print 'User has been suspended'
                return

            if error.message[0]['message'] ==  'Rate limit exceeded':
                print 'Rate limit. Sleeping for 15 minutes.'
                time.sleep(5 * 60 + 15)
                continue



#This is a basic listener that just prints received tweets to stdout.
class StdOutListener(StreamListener):

    def __init__(self):
        self.count = 0;
    
    def on_data(self, data):
        global api
        data = json.loads(data.decode('utf-8'))

        print data

        if 'user' in data:
            if 'screen_name' in data['user']:
                getFollowerData(data['user']['screen_name'])
        return True

    def on_error(self, status):
    	print(status)


if __name__ == '__main__':
    global api
    #This handles Twitter authetification and the connection to Twitter Streaming API
    l = StdOutListener()
    auth = OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    api = tweepy.API(auth)
    stream = Stream(auth, l)
    stream.sample()