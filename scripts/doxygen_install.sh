git clone https://github.com/doxygen/doxygen.git
cd doxygen
cmake -G "Unix Makefiles" ..
#if not installed
sudo update
sudo apt install flex
sudo apt install bison
sudo apt install graphviz
sudo apt install libreoffice 
make
make install
