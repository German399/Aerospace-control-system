 git clone https://github.com/snagles/docker-registry-manager.git && cd docker-registry-manager
 nano registries.yml # add your registry
 nano docker-compose.yml # Edit application settings e.g log level, port
 docker-compose up -d
 firefox localhost:8080