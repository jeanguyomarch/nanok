#! /usr/bin/env sh

set -e
set -u
set -x

./nanokbs/nanokbs.py -a ./tests/target/disco.hjson -t ./tests/targets/build.ninja.j2 -o build.ninja
