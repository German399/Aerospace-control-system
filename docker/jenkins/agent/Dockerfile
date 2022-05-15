FROM jenkins/ssh-agent:jdk11
LABEL version="0.2" maintainer="Shevadronov Alexander <ale5000@yandex.ru>"
USER root
RUN apt-get update -y&&apt-get upgrade -y&&apt-get install -y wget \
apt-utils \
pkg-config \
tcl \
g++ \
cmake \
git
#for generating docs
RUN apt-get install -y libreoffice
#for build doxygen
RUN apt-get install -y python3 flex bison graphviz 
#make boost
RUN cd ~ && wget http://downloads.sourceforge.net/project/boost/boost/1.75.0/boost_1_75_0.tar.gz \
  && tar xfz boost_1_75_0.tar.gz \
  && rm boost_1_75_0.tar.gz \
  && cd boost_1_75_0 \
  && ./bootstrap.sh --prefix=/usr/local 
RUN cd ~/boost_1_75_0 && ./b2 --with-chrono --with-system --with-thread --with-date_time --with-regex --with-serialization stage install
#redis C exchange lib
RUN cd ~ && git clone https://github.com/redis/hiredis.git \
&& cd ~/hiredis \
&& make \
&& make install 
RUN cd ~ && git clone https://github.com/sewenew/redis-plus-plus.git
#redis plus-plus for streams api
RUN cd ~/redis-plus-plus && mkdir build && cd build && cmake -DREDIS_PLUS_PLUS_CXX_STANDARD=17 .. \
&& make && make install
RUN cd ~ && git clone https://github.com/doxygen/doxygen.git
RUN cd ~/doxygen \
&& cmake -G "Unix Makefiles" . \
&& make \
&& make install

