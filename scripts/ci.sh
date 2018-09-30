#! /usr/bin/env sh

set -e
set -u
set -x

./scripts/gen-unit-tests.sh
ninja check
