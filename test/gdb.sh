if [ -f "data/output/solucao-analise.csv" ]
then
    rm -f data/output/*
fi

g++ -g ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm

gdb --args ./test/exe "Teste"  1 1 1