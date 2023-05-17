if [ -f "data/output/solucao-analise.csv" ]
then
    rm -f data/output/prof.tex
    rm -f data/output/turma.tex
    rm -f data/output/solucao-analise.csv
fi

g++ -g ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm

gdb --args ./test/exe "Teste"  1 1 1