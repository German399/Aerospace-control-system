FROM debian:stable
LABEL version="0.2" maintainer="Shevadronov Alexander <ale5000@yandex.ru>"
USER root
RUN apt-get update -y&&apt-get upgrade -y&&apt-get install -y wget \
pkg-config \
tcl \
g++ \
cmake
RUN cd ~ && wget http://downloads.sourceforge.net/project/boost/boost/1.74.0/boost_1_74_0.tar.gz \
  && tar xfz boost_1_74_0.tar.gz \
  && rm boost_1_74_0.tar.gz \
  && cd boost_1_74_0 \
  && ./bootstrap.sh --prefix=/usr/local 
RUN cd /root/boost_1_74_0 && ./b2 --with-chrono --with-system --with-thread --with-date_time --with-regex --with-serialization stage install
RUN apt-get install -y git && git clone https://github.com/redis/hiredis.git \
&&cd hiredis \
&& make \
&& make install 
COPY . ./wago_adapter
