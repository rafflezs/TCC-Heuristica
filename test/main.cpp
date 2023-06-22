#include "../src/cpp/engine/heuristica.hpp"

void debuga_tudo_nessa_desgraca(Solucao *t_solucao);

int main(int argc, char **argv)
{
    std::cout << "Iniciando programa em C++" << std::endl;
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    std::cout << "count: " << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "]=" << argv[i] << std::endl;
    }
    std::cout << "Entrando na heuristica em C++" << std::endl;
    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stof(argv[5]), std::stof(argv[6]));
    std::cout << "Terminou a heuristica em C++" << std::endl;
    auto tempo_inicial = std::chrono::steady_clock::now();
    h.inicializar(&tempo_inicial);

    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << since(tempo_inicial).count() << " microsegundos" << std::endl;

    return 0;
}
