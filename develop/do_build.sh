#!/bin/bash

APPS_NAME="service"

if [ -d build ]; then
    echo "remove build folder"
    rm -rf build
fi

mkdir build
cp -rp html/* build
cd build

cmake ..
make

if [ -e $APPS_NAME ]; then
    echo "make execution file"
    cp -p $APPS_NAME ../
fi
cd -
