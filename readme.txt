apt-get install cmake asterisk-dev


mkdir build
cd build
cmake ..
make
make install


asterisk -rx "module load res_dummy"