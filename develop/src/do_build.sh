#!/bin/bash

APPS_NAME="serverApp"

if [ -d build ]; then
    echo "remove build folder"
    rm -rf build
fi

mkdir build
cd build
cmake ..
make
cd -

if [ -e "build/$APPS_NAME" ]; then
    echo "make execution file"
    cp -p build/$APPS_NAME ../
fi
