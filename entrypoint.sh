#!/bin/sh
# Read in the file of environment settings
. root/bin/thisroot.sh
# Then run the CMD
exec "$@"