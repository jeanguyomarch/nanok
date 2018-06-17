#! /usr/bin/env sh

set -e
set -u

if [ $# -ne 2 ]; then
   echo "ERROR: Usage: $0 <prog.bin> <loadaddr>" 1>&2
   exit 1
fi

BIN="$1"
LOADADDR="$2"

set -x
st-flash --reset write "$BIN" "$LOADADDR"
