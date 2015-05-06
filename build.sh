#!/bin/bash
#
#	BUILD SCRIPT FOR JETDIALOG
#	Copyright (C) 2015 Marius Messerschmidt
#

if [ "$1" == "--clean" ]
then
rm src/*.o
rm jdialog
exit
fi

echo "Starting build..."
for F in src/*.c; do \
echo "Using $F" && \
gcc "$F" -std=c11 -c -Wall  `pkg-config --libs --cflags gtk+-3.0` -o "${F%.c}.o"; \
done
echo "Building binary..."
VAR=""
for O in src/*.o; do \
VAR="$VAR $O"
done
echo "Building from $VAR"
gcc -Wall $VAR -o jdialog `pkg-config --cflags --libs gtk+-3.0`
