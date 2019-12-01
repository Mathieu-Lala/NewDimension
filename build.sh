#!/bin/bash

bin_name="app"

clean () {
    rm -rf $bin_name build "bin/${bin_name}"
}

release () {
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build -j4 . && cd ..
}

debug () {
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build -j4 . && cd ..
}

re () {
    clean
    debug
}

usage () {
    echo "USAGE:" $0 "[option]"
    echo "OPTION:"
    echo "  usage|-u    print this message"
    echo "  debug       generate a debug build"
    echo "  release     generate a release build"
    echo "  clean       remove the build folder and the binaries"
    echo "  re          clean then create a debug build"
}

case $1 in
    debug)
    debug
    shift
    ;;
    release)
    release
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
