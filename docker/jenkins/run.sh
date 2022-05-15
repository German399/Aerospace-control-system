docker build -t jenkins-blueocean:latest .
docker run --name dev-jenkins-blueocean --detach --network jenkins --env DOCKER_HOST=tcp://docker:2376 --env DOCKER_CERT_PATH=/certs/client --env DOCKER_TLS_VERIFY=1 --publish 10100:8080 --publish 50000:50000 --volume jenkins-data:/var/jenkins_home --volume jenkins-docker-certs:/certs/client:ro jenkins-blueocean:latest
echo "login localhost:11000,secret for web-login:"
docker exec -it dev-jenkins-blueocean cat /var/jenkins_home/secrets/initialAdminPassword
#for work, need additional plugins such as gitea, pipeline
#manual for autobuild https://plugins.jenkins.io/gitea/