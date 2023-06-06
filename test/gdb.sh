if [ -f "data/output/solucao-analise.csv" ]
then
    rm -f data/output/*
fi

g++ -g ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm

NOME_INSTANCA="Instancia-Facil-Comp"
TAM_POPULACAO=1
QTD_TURMAS_HEURISTICA=5 # 0 para mandar 1 > 2 > 3 ... max_turmas_curso; max_turmas ou mais para mandar todas as turmas do curso de uma vez
QTD_REPT_HEURISTICA=1   # 1 para linear, 2+ para rept
PESO_JANELA=1
PESO_SEXTO=1

echo "instancia: $NOME_INSTANCA"
echo "tam populacao: $TAM_POPULACAO"
echo "qtd turmas heuristica: $QTD_TURMAS_HEURISTICA"
echo "qtd repet heuristica: $QTD_REPT_HEURISTICA"
echo "peso janela: $PESO_JANELA"
echo "peso sexto: $PESO_SEXTO"

gdb --args ./test/exe $NOME_INSTANCA $TAM_POPULACAO $QTD_TURMAS_HEURISTICA $QTD_REPT_HEURISTICA $PESO_JANELA $PESO_SEXTO