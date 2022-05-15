#!/bin/sh
cd /home/mskbo && wget http://downloads.sourceforge.net/project/boost/boost/1.75.0/boost_1_75_0.tar.gz \
  && tar xfz boost_1_75_0.tar.gz \
  && rm boost_1_75_0.tar.gz \
  && cd boost_1_75_0 
  && sudo ./bootstrap.sh --prefix=/usr/local 
  #--with-libraries=program_options 
  #&& sudo ./b2 install \
  #chrono - timer, rest asio requirements
  && sudo ./b2 --with-chrono --with-system --with-thread --with-date_time --with-regex --with-serialization stage install \
  #&& cd /home/mskbo \
  #&& sudo rm -rf boost_1_75_0
  #add_library(asio INTERFACE)
