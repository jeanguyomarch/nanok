#! /usr/bin/env sh
#
# This shell script runs nanokbs with the appropriate template and unit test
# configuration files to produce a build.ninja file that is able to compile and
# run the unit tests.
#
# NOTE: This script shall be run from the top source directory

set -e
set -u
set -x

./nanokbs/nanokbs.py -a ./tests/pc/unit.hjson -t ./tests/pc/build-unit-tests.ninja.j2 -o build.ninja
rm -rf build
