#include "../src/cpp/engine/heuristica.hpp"

void debuga_tudo_nessa_desgraca(Solucao *t_solucao);

int main(int argc, char **argv)
{
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    //                           INSTANCIA,         QTD_TURMAS,           QTD_REPT,           PESO JAN,          PESO SEX)
    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stof(argv[4]), std::stof(argv[5]));
    auto tempo_inicial = std::chrono::steady_clock::now();
    h.inicializar(&tempo_inicial);

    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << since(tempo_inicial).count() << " microsegundos" << std::endl;

    return 0;
}
