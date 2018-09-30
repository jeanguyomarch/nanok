#! /usr/bin/env sh

set -e
set -u
set -x

./nanokbs/nanokbs.py -a ./tests/pc/unit.hjson -t ./tests/pc/build-unit-tests.ninja.j2 -o build.ninja
