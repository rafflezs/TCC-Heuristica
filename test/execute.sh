#!/bin/bash

## Implementar chamada src/automation/file-converter.py
## para gerar instancia a partir do xlsx

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

rm -f data/output/*

time ./test/exe "TCC-Instancia-2019-1" 100 1 1 >> data/output/debug-out.txt

rm -f test/exe

## Implementar chamada src/automation/latex-to-pdf.py
## para gerar pdf de saida