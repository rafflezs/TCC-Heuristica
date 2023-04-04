#include "../src/cpp/engine/heuristica.hpp"
#include "../src/cpp/helpers/gravar-arquivo.hpp"

int main(int argc, char **argv)
{
    srand(time(0));
    // Instancia inst = Instancia(argv[1]);
    // inst.print_instancia();

    // Solucao sol = Solucao(argv[1], {});
    // sol.exibir_solucao();

    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]));
    h.heuristica_construtiva();
    printf("\n\n\n\n\n\nSOLUCOES ENCONTRADAS\n\n");
    h.exibir_solucoes();

    // if (argv[3] == nullptr) argv[3] = "1";
    // if (argv[4] == nullptr) argv[4] = "1";

    h.avaliar_solucoes(std::stof(argv[3]), std::stof(argv[4]));
    
    GravarArquivo ga = GravarArquivo();
    ga.salvar_solucao_prof("data/output/test.tex", h.get_solucao(1));
    return 0;
}
