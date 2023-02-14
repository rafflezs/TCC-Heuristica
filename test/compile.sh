if [ -f "/test/exe" ]; then
    rm test/exe
fi
g++ -g test/main.cpp src/cpp/engine/*.cpp src/cpp/helpers/*.cpp -o test/exe -lm 