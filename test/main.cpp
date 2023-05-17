#include "../src/cpp/engine/heuristica.hpp"

int main(int argc, char **argv)
{
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };

    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stof(argv[3]), std::stof(argv[4]));
    h.inicializar();

    return 0;
}


/*
    Implementar Fix-and-Optimize
    Ver heuristica.cpp para mais informacoes
*/