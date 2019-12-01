#!/bin/bash

bin_name="app"

clean () {
    rm -rf $bin_name build "bin/${bin_name}"
}

build () {
    mkdir build
    cd build
    cmake .. && cmake --build -j4 . && cd ..
}

re () {
    clean
    build
}

usage () {
    echo "USAGE:" $0 "[option]"
    echo "OPTION:"
    echo "  usage|-u  print this message"
    echo "  build     generate the binary"
    echo "  clean     remove the build folder and the binaries"
    echo "  re        clean then build"
}

case $1 in
    build)
    build
    shift
    ;;
    clean)
    clean
    shift
    ;;
    re)
    re
    shift
    ;;
    -u|usage)
    usage
    shift
    ;;
    *)
    re
    ;;
esac
