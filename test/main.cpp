#include "../src/cpp/engine/heuristica.hpp"

int main(int argc, char **argv)
{

    std::chrono::time_point<std::chrono::steady_clock> tempo_inicial = std::chrono::steady_clock::now();

    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stof(argv[3]), std::stof(argv[4]), &tempo_inicial);
    h.inicializar();

    auto tempo_gasto = std::chrono::steady_clock::now() - tempo_inicial;
    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << tempo_gasto.count() 
              << std::endl;

    return 0;
}

/*
    Implementar Fix-and-Optimize
    Ver heuristica.cpp para mais informacoes
*/