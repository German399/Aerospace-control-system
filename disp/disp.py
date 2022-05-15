import random
from threading import Thread
from multiprocessing import Process
from time import sleep
from util.connection import get_connection

KEY = 'numbers'
GROUP = 'primes'
MEMBERS = 3
def setup():
    ''' Initializes the Stream and the primes consumers group '''
    redis = get_connection()
    redis.delete(KEY)
    redis.xgroup_create(KEY, GROUP, mkstream=True)