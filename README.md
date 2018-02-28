# QCirS

## Overview
QCirS is a quantum circuit simulator.

## Requirements
To build QCirS, followings are required:
- C++ compiler with C++14 capabilities
    - g++ 6.4 is recomended.
- Boost C++ Libraries
    - to construct parser using boost::spirit::qi
- CMake 2.8 or greater

## Building
```
$ git clone git@github.com:sndtkrh/qcirs.git
$ cd qcirs
$ mkdir build
$ cd ./build
$ cmake ..
$ make
```
