#!/bin/bash

## Implementar chamada src/automation/file-converter.py
## para gerar instancia a partir do xlsx

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

./test/exe "Instancia-Facil-Comp" 1 1 1 >> data/output/debug-out.txt

rm -f test/exe

## Implementar chamada src/automation/latex-to-pdf.py
## para gerar pdf de saida