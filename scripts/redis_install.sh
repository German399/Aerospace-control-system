cd ~ 
wget http://download.redis.io/redis-stable.tar.gz
tar xvzf redis-stable.tar.gz
rm redis-stable.tar.gz
cd redis-stable
make
make test
sudo make install
#after install reboot
#to start server - redis-server
#to start cli - redis-cli
#commands set key 
#get key
#monitor
#exit