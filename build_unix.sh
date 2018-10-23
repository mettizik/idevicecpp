#!/bin/bash
echo This script is not tested on any UNIX system, but should be working
rm -rdf build
mkdir -p build
pushd build
    conan install OpenSSL/1.1.0i@conan/stable -g cmake 
    cmake -G "Unix Makefiles" ..
    cmake --build . --target idevicecpp
popd 
