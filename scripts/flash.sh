#! /usr/bin/env sh

set -e
set -u

if [ $# -ne 1 ]; then
   echo "ERROR: Usage: $0 <prog.bin>" 1>&2
   exit 1
fi

LOADADDR=0x08000000 # FIXME

set -x

st-flash --reset write "$1" "$LOADADDR"
