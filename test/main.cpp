#include "../src/cpp/engine/heuristica.hpp"
#include "../src/cpp/helpers/gravar-arquivo.hpp"

int main(int argc, char** argv)
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

    GravarArquivo ga = GravarArquivo();
    ga.salvar_solucao_prof("data/output/test.latex", h.get_solucao(1));
    return 0;
}
