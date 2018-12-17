apt-get install cmake asterisk-dev


mkdir build
cd build
cmake ..
make
make install


asterisk -rx "module load res_dummy.so"


[dummy]
exten => 100,1,Dummy(arguments)
same => n,Set(DUMMY(some)=other)
same => n,NoOp(${DUMMY(some)})

console dial 100@dummy