#! /usr/bin/env sh

set -e
set -u

ST_UTIL_PID=

if [ $# -ne 1 ]; then
   echo "ERROR: Usage: $0 <prog.elf>" 1>&2
   exit 1
fi


clean() {
   if [ -n "$ST_UTIL_PID" ]; then
      kill "$ST_UTIL_PID"
   fi
}

trap clean EXIT

PORT=4242

st-util --port "$PORT" --no-reset > "st-util.log" & ST_UTIL_PID=$!
sleep 1
arm-none-eabi-gdb "$1" -ex "target extended-remote :$PORT"
