#include "../src/cpp/engine/heuristica.hpp"

int main(int argc, char** argv)
{
    std::cout << argv[1] << std::endl;
    // Instancia inst = Instancia(argv[1]);
    // inst.print_instancia();

    // Solucao sol = Solucao(argv[1], {});
    // sol.exibir_solucao();


    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]));
    h.heuristica_construtiva();
    return 0;
}
