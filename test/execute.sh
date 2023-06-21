#!/bin/bash

## Implementar chamada src/automation/file-converter.py
## para gerar instancia a partir do xlsx

if [ -f "/test/exe" ]; then
    echo "Compilando"
    test/compile.sh
fi

echo "Limpando pasta output/"
rm -r "data/output/"
mkdir "data/output"

NOME_INSTANCA="TCC-Instancia-2019-1"
TAM_POPULACAO=1
QTD_TURMAS_HEURISTICA=1 # 0 para mandar 1 > 2 > 3 ... max_turmas_curso; max_turmas ou mais para mandar todas as turmas do curso de uma vez
QTD_REPT_HEURISTICA=1   # 1 para linear, 2+ para rept
PESO_JANELA=1
PESO_SEXTO=1

echo "instancia: $NOME_INSTANCA"
echo "tam populacao: $TAM_POPULACAO"
echo "qtd turmas heuristica: $QTD_TURMAS_HEURISTICA"
echo "qtd repet heuristica: $QTD_REPT_HEURISTICA"
echo "peso janela: $PESO_JANELA"
echo "peso sexto: $PESO_SEXTO"

folder="data/output/$NOME_INSTANCA"
mkdir "$folder"

time ./test/exe $NOME_INSTANCA $TAM_POPULACAO $QTD_TURMAS_HEURISTICA $QTD_REPT_HEURISTICA $PESO_JANELA $PESO_SEXTO >> "$folder"/debug-out.txt

rm -f test/exe # Comentar essa linha caso nao altere o codigo

mv data/output/analise.csv "$folder"
mv data/output/pequena_trollagem.txt "$folder"
mv data/output/professor.tex "$folder"
mv data/output/turma.tex "$folder"


echo "Compilando PDFs"
# Inserir aqui arquivo Python para formatar LaTeX
for file in $(find "$folder" -name "*.tex"); do
    echo "$file"
    pdflatex -halt-on-error -interaction=batchmode -output-directory $folder $file > /dev/null
done

echo ""
echo "Limpando a pasta"
if ls "$folder"/*.log >/dev/null 2>&1; then
    rm -f "$folder"/*.log
fi
if ls "$folder"/*.aux >/dev/null 2>&1; then
    rm -f "$folder"/*.aux
fi

echo ""
echo "Execucao finalizada. Saidas salvas em $folder"
echo "-----------------------------------------------"