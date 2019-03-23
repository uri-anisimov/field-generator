#!/bin/bash -x

TOP=$(realpath $(dirname "$0"))
BUILD=$TOP/build

rm -rf $BUILD \
&& mkdir $BUILD \
&& cd $BUILD \
&& cmake -DCMAKE_INSTALL_PREFIX=$BUILD/install -DCMAKE_BUILD_TYPE=Release $TOP \
&& make -j$(nproc) \
&& make -j$(nproc) install

