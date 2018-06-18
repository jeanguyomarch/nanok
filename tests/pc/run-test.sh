#! /usr/bin/env sh
#
# This script executes the program passed as its first argument, and compare
# its output to a reference file passed as its second argument
#

set -e
set -u

# Getopt
if [ $# -ne 2 ]; then
   echo "*** Usage: $0 <prog> <ref>" 1>&2
   exit 1
fi
PROG="$1"
TXT_REF="$2"

# Create the path to the file that will contain the program output
OUT="$(dirname "$PROG")/.$(basename "$PROG").out"
set +e # Disable errors... we will handle them ourselves

# Run the program. It must succeed.
"$PROG" > "$OUT"
if [ $? -ne 0 ]; then
   echo "*** Execution of '$PROG' FAILED!" 1>&2
   exit 1
fi

# Diff the program output with the reference (print in stdout if diff)
diff "$OUT" "$TXT_REF"
if [ $? -ne 0 ]; then
   echo "*** Output of '$PROG' ($OUT) does not match the expected reference ($TXT_REF)!" 1>&2
   exit 1
fi

# Clean-up (on success)
set -e # Fail if errors occurs
rm "$OUT"
