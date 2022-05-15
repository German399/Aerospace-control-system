#CONFIG SET PROTECTED MODE NO / CONFOG REWRITE
import redis

#r = redis.Redis(host='192.168.1.99', port=6379, db=0)
r = redis.Redis(host='127.0.0.1', port=6379, db=0)
r.set('FPZstruct', '{"initReady":1,"timerReady":1}')
r.set('KSUstruct', '{"initReady":1,"timerReady":1}')
r.set('LAstruct', '{"initReady":1,"timerReady":1}')
r.set('OUstruct', '{"initReady":1,"timerReady":1}')
r.set('INSstruct', '{"initReady":1,"timerReady":1}')
r.set('IUPstruct', '{"initReady":1,"timerReady":1}')