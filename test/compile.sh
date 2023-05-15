#!/bin/bash

if [ -f "/test/exe" ]
then
    rm -f test/exe
fi

g++ ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm