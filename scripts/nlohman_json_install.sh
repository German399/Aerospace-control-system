#!/bin/sh
git clone https://github.com/nlohmann/json.git
cd json
make
sudo make install