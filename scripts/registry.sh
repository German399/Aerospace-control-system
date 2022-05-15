docker run -d \
  -p 5505:5000 \
  --restart=always \
  --name registry \
  registry:2
  #docker image tag mskbo_build:latest localhost:5505/mskbo_build:latest
  #docker push localhost:5505/mskbo_build:latest