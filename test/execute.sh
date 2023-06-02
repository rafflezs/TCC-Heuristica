#!/bin/bash

## Implementar chamada src/automation/file-converter.py
## para gerar instancia a partir do xlsx

if [ ! -f "/test/exe" ]
then
    test/compile.sh
fi

rm -f data/output/*

NOME_INSTANCA="TCC-Instancia-2019-1"
TAM_POPULACAO=5
QTD_TURMAS_HEURISTICA=0 # 0 para mandar 1 > 2 > 3 ... max_turmas_curso; max_turmas ou mais para mandar todas as turmas do curso de uma vez
QTD_REPT_HEURISTICA=1   # 1 para linear, 2+ para rept
PESO_JANELA=1
PESO_SEXTO=1

echo "instancia: $NOME_INSTANCA"
echo "tam populacao: $TAM_POPULACAO"
echo "qtd turmas heuristica: $QTD_TURMAS_HEURISTICA"
echo "qtd repet heuristica: $QTD_REPT_HEURISTICA"
echo "peso janela: $PESO_JANELA"
echo "peso sexto: $PESO_SEXTO"

time ./test/exe $NOME_INSTANCA $TAM_POPULACAO $QTD_TURMAS_HEURISTICA $QTD_REPT_HEURISTICA $PESO_JANELA $PESO_SEXTO >> data/output/debug-out.txt

rm -f test/exe

# Inserir aqui arquivo Python para formatar LaTeX
# pdflatex -halt-on-error -output-directory data/output/ data/output/professor.tex 
# pdflatex -halt-on-error -output-directory data/output/ data/output/turma.tex 