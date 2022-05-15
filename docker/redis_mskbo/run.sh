 sudo docker build -t redis_mskbo_debian .
 sudo docker run --restart=always --name redis_mskbo -d redis_mskbo_debian\
    -v /opt/redis/data:/data \
    -p 127.0.0.1:6379:6379 
 #   redis_server /usr/local/etc/redis/redis.conf
# /usr/local/etc/redis/redis.conf
 #  -v /opt/redis/etc/redis.conf:/usr/local/etc/redis/redis.conf \


 
