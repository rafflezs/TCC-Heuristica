#include "../src/cpp/engine/heuristica.hpp"

int main(int argc, char **argv)
{
    srand(time(0));

    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]), std::stof(argv[3]), std::stof(argv[4]));
    h.inicializar();

    return 0;
}


/*

POS-PROCESSAMENTO ALEATORIO EM CIMA DE UMA SOLUCAO RODANDO MAIS DE UMA VEZ
    - BUSCA_LOCAL nao esta gerando pegando a solucao correta (ex: TAM 2 a busca local da solucao 1 na verdade está sendo aplicada na 2)
    - Implementar FIX-AND-OPTIMIZE (TRAVA UMA TURMA N E MODIFICA AS OUTRAS)

*/