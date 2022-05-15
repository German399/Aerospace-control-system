#запускаем на 11110 порту, сохраняем файлы в папке work, b151ca2b02a5 имя образа может отличатся
docker build -t jupiter-lab-mskbo:latest .
docker run --rm -p 11110:8888 -e JUPYTER_ENABLE_LAB=yes -v "${PWD}"/work:/home/jovyan/work build -t jupiter-lab-mskbo:latest
