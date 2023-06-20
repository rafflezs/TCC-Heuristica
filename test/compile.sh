#!/bin/bash

if [ -f "/test/exe" ]
then
    rm -f test/exe
fi

if [ -f "data/output/debug-out.txt" ]
then
    rm -f data/output/debug-out.txt
    rm -f data/output/prof.tex
    rm -f data/output/turma.tex
    rm -f data/output/solucao-analise.csv
fi

g++ -O3 ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm
