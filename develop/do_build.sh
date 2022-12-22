#!/bin/bash

if [ -d build ]; then
    echo "remove build folder"
    rm -rf build
fi

mkdir build
cp -rp html/* build
cd build

cmake ..
make
