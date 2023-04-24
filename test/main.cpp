#include "../src/cpp/engine/heuristica.hpp"
#include "../src/cpp/helpers/gravar-arquivo.hpp"

int main(int argc, char **argv)
{
    srand(time(0));

    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]));
    h.heuristica_construtiva();
    printf("\n\nSOLUCOES ENCONTRADAS\n\n");
    h.avaliar_solucoes(std::stof(argv[3]), std::stof(argv[4]));
    h.exibir_solucoes();

    GravarArquivo ga = GravarArquivo();
    ga.salvar_solucao_prof("data/output/test.tex", h.get_solucao(1));

    return 0;
}
