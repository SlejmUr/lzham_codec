#!/bin/bash

dir=$(dirname $0)

mkdir -p $dir/x32 $dir/x64

cmake . -B $dir/x32 -DBUILD_X64=OFF
cmake . -B $dir/x64