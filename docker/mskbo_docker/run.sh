 #build image
 sudo docker build -t mskbo_build .
 sudo docker run --network=gitlab_gitlab -it --name mskbo_build_instance -d mskbo_build

#to connect to debug
#sudo docker exec -it mskbo_build_instance bash 
#cd home/testjson && ./install



 
