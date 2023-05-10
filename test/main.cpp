#include "../src/cpp/engine/heuristica.hpp"
#include "../src/cpp/helpers/gravar-arquivo.hpp"

int main(int argc, char **argv)
{
    srand(time(0));

    Heuristica h = Heuristica(argv[1], std::stoi(argv[2]));
    h.heuristica_construtiva();
    h.avaliar_solucoes(std::stof(argv[3]), std::stof(argv[4]));
    printf("\n\nSOLUCOES ENCONTRADAS\n\n");
    h.exibir_solucoes();

    printf("\n\nSOLUCOES ENCONTRADAS (POS)\n\n");
    h.pos_processamento();
    h.avaliar_solucoes(std::stof(argv[3]), std::stof(argv[4]));
    printf("\n\nSOLUCOES ENCONTRADAS (POS PROCESSAMENTO)\n\n");
    h.exibir_solucoes();


    GravarArquivo ga = GravarArquivo();
    ga.salvar_solucao_prof("data/output/test.tex", h.get_solucao(1));

    return 0;
}


/*
TESTAR POPULACAO TAM 1
    - RESOLVER O PRPBLEMA EM QUE POP TAM 1 O PROGRAMA RETORNA SEGFAULT NO POS_PROCESSAMENTO em GET_INSTANCIA()

POS-PROCESSAMENTO ALEATORIO EM CIMA DE UMA SOLUCAO RODANDO MAIS DE UMA VEZ
    - BUSCA_LOCAL nao esta gerando pegando a solucao correta (ex: TAM 2 a busca local da solucao 1 na verdade está sendo aplicada na 2)
    - Implementar FIX-AND-OPTIMIZE (TRAVA UMA TURMA N E MODIFICA AS OUTRAS)

IMPLEMENTAR OUTPUT EM .CSV DAS SOLUCOES
    - Basta gravar o valor da solucao no template: sol_id, sol_val, [params]

*/