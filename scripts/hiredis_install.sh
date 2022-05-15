#!/bin/sh
git clone https://github.com/redis/hiredis.git
cd hiredis
make
sudo make install
make test
