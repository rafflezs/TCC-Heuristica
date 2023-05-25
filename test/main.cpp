#include "../src/cpp/engine/heuristica.hpp"

void debuga_tudo_nessa_desgraca(Solucao *t_solucao);

int main(int argc, char **argv)
{
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    auto tempo_inicial = std::chrono::steady_clock::now();
    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), &tempo_inicial);
    // h.inicializar();

    auto sol1 = h.get_solucao(0);
    auto sol2 = sol1->copia_profunda();

    debuga_tudo_nessa_desgraca(sol1);
    debuga_tudo_nessa_desgraca(sol2);

    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << since(tempo_inicial).count() << " microsegundos" << std::endl;

    return 0;
}

void debuga_tudo_nessa_desgraca(Solucao *t_solucao)
{
    std::cout << "Solucao address: " << t_solucao << std::endl;
    std::cout << "Instancia address: " << t_solucao->get_instancia() << std::endl
              << std::endl;

    for (auto prof : t_solucao->get_instancia()->get_lista_professores())
    {
        std::cout << "Professor address: " << prof << std::endl;
    }

    for (auto turma : t_solucao->get_instancia()->get_lista_turmas())
    {
        std::cout << "Turma address: " << turma << std::endl;
    }
}