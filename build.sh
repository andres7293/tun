#!/bin/bash

BUILD_DIR="$(pwd)/build"

if [ -d ${BUILD_DIR} ]; then
    mkdir -p ${BUILD_DIR}
fi

cd ${BUILD_DIR}
cmake ..
make
