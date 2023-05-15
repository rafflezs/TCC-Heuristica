g++ -g ./test/main.cpp ./src/cpp/engine/*.cpp ./src/cpp/helpers/*.cpp -o ./test/exe -lm

gdb --args ./test/exe "Instancia-Facil-Comp"  1 1 1