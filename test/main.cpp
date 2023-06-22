#include "../src/cpp/engine/heuristica.hpp"

void debuga_tudo_nessa_desgraca(Solucao *t_solucao);

int main(int argc, char **argv)
{
    std::cout << "Iniciando programa em C++" << std::endl;
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stof(argv[5]), std::stof(argv[6]));
    auto tempo_inicial = std::chrono::steady_clock::now();
    h.inicializar(&tempo_inicial);

    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << since(tempo_inicial).count() << " microsegundos" << std::endl;

    return 0;
}

void debuga_tudo_nessa_desgraca(Solucao *t_solucao)
{
    std::cout << "\n--------DEBUG---------" << "\n";
    std::cout << "Solucao address: " << t_solucao << "\n";
    std::cout << "Instancia address: " << t_solucao->get_instancia() << "\n\n";

    for (auto prof : t_solucao->get_instancia()->get_lista_professores())
    {
        std::cout << "PROFESSOR | address: " << prof << " | " << prof->get_nome() << "\n";
    }

    for (auto turma : t_solucao->get_instancia()->get_lista_turmas())
    {
        std::cout << "TURMA | address: " << turma << " | " << turma->get_nome() << "\n";
        for (auto disciplina : turma->get_disciplinas())
        {
            std::cout << "Disciplina | address: " << disciplina << " | " << disciplina->get_id() << "\n";
        }
    }

    std::cout << "\n" << std::endl;
}