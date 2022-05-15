#!/bin/sh
#git clone https://github.com/debian-tex/texlive-bin
#wget http://mirror.ctan.org/systems/texlive/tlnet/install-tl-unx.tar.gz
#tar xvzf install-tl-unx.tar.gz
#команда ниже зависит от даты билда текса, омг
#cd install-tl-20210413
#./install-tl
#
#cd texlive-bin
#sudo apt install libpng-dev
#apt install libpixman-1-dev
#apt install libfreetype6-dev
#cairo-dock
#libfreetype6-dev perl
#run ./Build
#make
#make install
#sudo apt-get install texlive-latex-base
#sudo apt-get install texlive-fonts-recommended
#sudo apt-get install texlive-fonts-extra
#sudo apt install texstudio
git clone https://github.com/arialwhite/docker-doxygen-to-pdf.git
cd docker-doxygen-to-pdf
docker build . -t doxy
#// for example ./doxygen-demo is a directory that contains Doxyfile
docker run -it -v "$PWD/doxygen-demo:/usr/src/project" --rm doxy /bin/bash

#doxy> cd /usr/src/project
#doxy> doxygen // generate doc.tex for example
#doxy> cd latex
#doxy> pdflatex doc.tex
