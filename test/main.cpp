#include "../src/cpp/engine/heuristica.hpp"

void debuga_tudo_nessa_desgraca(Solucao *t_solucao);

int main(int argc, char **argv)
{
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};

    auto tempo_inicial = std::chrono::steady_clock::now();
    Heuristica h = Heuristica(rng, argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), &tempo_inicial);
    h.inicializar();

    // auto sol1 = h.get_solucao(0);
    // debuga_tudo_nessa_desgraca(sol1);

    // auto sol2 = new Solucao(*sol1);
    // debuga_tudo_nessa_desgraca(sol2);

    // //!!!!!!!
    // !!!!!!!!!!!!!
    // !!!!!!!!
    // ERRO PROPOSITAL:
    // A BUSCA_LOCAL NAO ESTA FUNCIONANDO CORRETAMENTE COMO COMBINADO COM O BELO
    // POR EXEMPLO, ESTA SELECIONANDO 11 TURMAS DE UMA VEZ, SEM QUALQUER RELACAO DE Curso
    // O CORRETO SERIA
    // TESTA de 1 em 1, LINEARMENTE
    // DEPOIS 2 em 2, LINEARMENTE, SEMPRE DO MESMO CURSO
    // O COUNT DEVERIA SER O PARAMETRO DE PARADA PARA INCREMENTAR A QUANTIDADE DE TURMAS
    // OU SEJA, 1 em 1 TURMA, COUNT EXCEDEU A PARADA, PASSA PRA 2, DENTRO DA MESMA SOLUCAO
    // ALEM DISSO, NAO ESTA TENDO SHUFFLE DE DISCIPLINAS NA BUSCA_LOCAL
    // APAGAR O MAX_TURMAS_POR_CURSO

    // TESTAR 1 TURMA SEMPRE, DEPOIS 2 TURMAS SEMPRE, DEPOIS 3 TURMAS SEMPRE ...
    // IMPLEMENTAR REPETIR A BUSCA LOCAL PRA MESMA TURMA MAIS DE UMA VEZ

    std::cout << "Fim da execução. O programa completou com sucesso.\nTempo gasto total: " << since(tempo_inicial).count() << " microsegundos" << std::endl;

    return 0;
}

void debuga_tudo_nessa_desgraca(Solucao *t_solucao)
{
    std::cout << "\n--------DEBUG---------"
              << "\n";
    std::cout << "Solucao address: " << t_solucao << "\n";
    std::cout << "Instancia address: " << t_solucao->get_instancia() << "\n"
              << "\n";

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

    std::cout << "\n"
              << std::endl;
}