#!/bin/bash -x

TOP=$(realpath $(dirname "$0"))
BUILD=$TOP/build
rm -rf $BUILD \
&& mkdir $BUILD \
&& cd $BUILD \
&& cmake $TOP \
&& make -j$(nproc)

