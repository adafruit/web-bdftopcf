#!/bin/sh
[ -d output ] || mkdir output

emcc -O -Wall -Werror -s TOTAL_MEMORY=67108864 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s ASSERTIONS=2 -s FORCE_FILESYSTEM=1 -s EXPORTED_RUNTIME_METHODS="['ccall']" -DPACKAGE_STRING=\"bdftopcf\" -I . *.c -o output/index.html --shell-file shell.html
