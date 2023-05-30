#!/bin/bash

## Implementar chamada src/automation/file-converter.py
## para gerar instancia a partir do xlsx

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

rm -f data/output/*

time ./test/exe "TCC-Instancia-2019-1" 10 2.8 1.5 >> data/output/debug-out.txt

rm -f test/exe

# Inserir aqui arquivo Python para formatar LaTeX
# pdflatex -halt-on-error -output-directory data/output/ data/output/professor.tex 
# pdflatex -halt-on-error -output-directory data/output/ data/output/turma.tex 