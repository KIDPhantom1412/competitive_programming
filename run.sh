#!/bin/bash

set -e

if [ -f .env ]; then
    set -a
    source .env
    set +a
fi

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++23 -O2 -Wall -Wextra}

INPUT=${1:-input.txt}
OUTPUT=${2:-output.txt}

BUILD_DIR=tmp
EXE=$BUILD_DIR/main

mkdir -p "$BUILD_DIR"

echo "[$CXX] $CXXFLAGS -o $EXE main.cpp"
"$CXX" $CXXFLAGS -o "$EXE" main.cpp

echo "$EXE < $INPUT > $OUTPUT"
"$EXE" < "$INPUT" > "$OUTPUT"
