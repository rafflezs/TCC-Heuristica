#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"
#include <ctime>

class Heuristica
{

private:
    std::vector<Solucao *> m_solucoes{};
    std::vector<float> m_avaliacao_solucao{};

public:
    Heuristica(std::string t_instancia_pipe, int tam_populacao);

    std::vector<Disciplina *> ordernar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void heuristica_construtiva();
    // void mutar(Solucao *solucao, int taxa_mutacao);
    // void cruzar(Solucao *solucao1, Solucao *solucao2);
    
    void exibir_solucoes();
    void debug_heuristica();

    float avaliar_solucao(Solucao* t_solucao);

    Solucao* get_solucao(int index);
};

#endif //!_HEURISTICA_HPP