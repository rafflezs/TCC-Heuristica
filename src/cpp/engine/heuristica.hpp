#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"
#include <set>
#include <ctime>

class Heuristica
{

private:
    std::vector<Solucao *> m_solucoes{};

public:
    Heuristica(std::string t_instancia_pipe, int tam_populacao);

    std::vector<Disciplina *> ordernar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void heuristica_construtiva();
    // void mutar(Solucao *solucao, int taxa_mutacao);
    // void cruzar(Solucao *solucao1, Solucao *solucao2);
    void pos_processamento();
    void metodo_destrutivo(int t_qtd_turmas, Solucao *solucao);

    void exibir_solucoes();
    void debug_heuristica();

    // Função Objetivo
    void avaliar_solucoes(const float &peso_janela, const float &peso_sexto_horario);

    float avaliar_solucao(Solucao *t_solucao, const float &peso_janela, const float &peso_sexto_horario);
    float calcular_janela_professor(Solucao *t_solucao);
    float calcular_sexto_horario_turma(Solucao *t_solucao);

    Solucao *get_solucao(int index);
};

#endif //!_HEURISTICA_HPP