#!/bin/sh
# Script used to build the game using Docker image 'barichello/sfml' and GitLab CI

GAME_NAME="multicaster"

function linux() {
    echo "Building for LINUX."
    # Build
    mkdir include
    cp -r /lua/include .
    cp /sol.hpp ./include/
    scons -j 4
    # Package
    mkdir bin/lib
    cp /usr/lib/x86_64-linux-gnu/libsfml-*.so.* bin/lib
    cp /usr/lib/libtgui.so* bin/lib
    cp /usr/lib/x86_64-linux-gnu/liblua5.3.so bin/lib
    mv bin $GAME_NAME
}

function windows() {
    echo "Building for WINDOWS."
    # Pre-build: dependencies
    mkdir include && mkdir lib
    cp -r /SFML-2.5.1/include .
    cp -r /SFML-2.5.1/lib .
    cp -r /TGUI-0.8/include .
    cp -r /TGUI-0.8/lib .
    cp /sol.hpp ./include/
    cp -r /lua/include .
    cp -r /lua/*.a ./lib
    # Build
    scons --cross=1 -j 4
    # Package
    cp /SFML-2.5.1/bin/openal32.dll bin/
    cp /SFML-2.5.1/bin/sfml-*-2.dll bin/
    cp /TGUI-0.8/bin/tgui.dll bin/
    cp /lua/*.dll bin/
    mv bin $GAME_NAME
}

if [[ $1 == "linux" ]]; then
    linux
elif [[ $1 == "windows" ]]; then
    windows
else
    echo "Provide either 'linux' or 'windows' as a command line argument to build."
    exit -1
fi
