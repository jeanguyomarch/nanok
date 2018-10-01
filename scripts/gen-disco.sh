#! /usr/bin/env sh

set -e
set -u
set -x

./nanokbs/nanokbs.py -a ./tests/target/disco.hjson -t ./tests/target/build.ninja-disco.j2 -o build.ninja
rm -rf build
