# QCirS

## Overview
QCirS is a quantum circuit simulator.

## Requirements
To build QCirS, followings are required:
- C++ compiler with C++14 capabilities
    - g++ 6.4 is recomended.
- Boost C++ Libraries version 1.66 or greater
    - to construct parser using boost::spirit::qi
- CMake 2.8 or greater

## Building and Installing
```
$ git clone git@github.com:sndtkrh/qcirs.git
$ cd qcirs
$ mkdir build
$ cd ./build
$ cmake ..
$ make && make install
```

## Example

To use quantum circuit library, you include `qc/qcore.hpp` in your `.cpp` files.
For example, see `example/dj.cpp`.
To compile this file, execute following commands:

```bash
$ cd ./example
$ g++ -std=c++14 dj.cpp -lqc -odj
```

This command generate executable file `dj`, and you can run it by:

```bash
$ ./dj
```

and you will get the result:

```
The probability of results of measurement is [ 1 0 0 0 ]
Result of appling Deutsch-Jozsa algorithm to a constant function:
(-0.707107,0)
(0,0)
(0,0)
(0,0)
(0.707107,0)
(0,0)
(0,0)
(0,0)
This function is constant.

The probability of results of measurement is [ 0 0 1 0 ]
Result of appling Deutsch-Jozsa algorithm to a balanced function:
(0,0)
(0,0)
(-0.707107,0)
(0,0)
(0,0)
(0,0)
(0.707107,0)
(0,0)
This function is balanced.

```
