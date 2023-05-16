#include "../src/cpp/engine/heuristica.hpp"

int main(int argc, char **argv)
{
    srand(time(0));

    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]), std::stof(argv[3]), std::stof(argv[4]));
    h.inicializar();

    return 0;
}


/*
    - Implementar FIX-AND-OPTIMIZE (TRAVA UMA TURMA N E MODIFICA AS OUTRAS)
*/