#!/bin/bash

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

if [ -f "data/output/debug-out.txt" ]
then
    rm -f data/output/debug-out.txt
    rm -f data/output/prof.tex
    rm -f data/output/turma.tex
    rm -f data/output/solucao-analise.csv
fi

rm -f test/out.txt

./test/exe "Instancia-Facil-Comp" 100 101.8 205.6 >> data/output/debug-out.txt

rm -f test/exe