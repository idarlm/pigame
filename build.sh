#!/bin/bash

# Using a bash script because i hate c/c++ build systems
# FYOUCAT CMake FYOUCAT MAKE
#
# This WILL age well (lies)

SOURCE_DIR="/home/pi/pigame/src"
BUILD_DIR="/home/pi/pigame/out"
EXECUTABLE_NAME="game"

# Verify that BUILD_DIR exists
ls "$BUILD_DIR" &> /dev/null
BUILD_DIR_EXISTS=$?

if [[ $BUILD_DIR_EXISTS -ne 0 ]]
then
    echo "Creating build dir: $BUILD_DIR"
    mkdir "$BUILD_DIR"
fi

# Build project
echo "Starting build..."
gcc -o "$BUILD_DIR/$EXECUTABLE_NAME" "$SOURCE_DIR/main.c"
BUILD_STATUS=$?

if [ $BUILD_STATUS -eq 0 ]
then
    echo "Output files added to $BUILD_DIR"
    echo "Build succeded."
else
    echo "Build failed with exit code $BUILD_STATUS."
fi
