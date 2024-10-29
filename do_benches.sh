#!/bin/bash

# set -xeuo pipefail

rm -rf build-*

BUILDS=("static-final" "static" "shared-final" "shared")


for build in "${BUILDS[@]}"; do
    mkdir build-$build
    cd build-$build

    SHARED=$([[ $build =~ "shared" ]] && echo "ON" || echo "OFF")
    FINAL=$([[ $build =~ "final" ]] && echo "ON" || echo "OFF")
    CXX=clang++-18 CC=clang-18 cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=$SHARED -DDERIVE_FINAL=$FINAL -G Ninja .. 1>/dev/null
    ninja -v 1>/dev/null
    echo "Running bench for $build"
    ./expose_bench
    cd ..
done
