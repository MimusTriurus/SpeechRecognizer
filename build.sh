#!/bin/bash

rm -R build
mkdir build
cd build


cmake ..

cmake --build . --config Release

read -p "Press enter to continue"
