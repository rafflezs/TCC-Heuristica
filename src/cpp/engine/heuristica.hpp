#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"
#include "../helpers/gravar-arquivo.hpp"
#include <set>
#include <ctime>
#include <limits>
#include <chrono>

class Heuristica
{

private:
    std::default_random_engine m_rng;
    std::vector<Solucao *> m_solucoes{};
    std::string m_instancia_nome{"NULL"};
    int m_tamanho_populacao{0};
    float m_peso_janela{0};
    float m_peso_sexto{0};
    std::chrono::time_point<std::chrono::steady_clock> *m_tempo_inicial;
    
    std::vector<Disciplina *> ordenar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void ordenar_disciplinas(const int &rand_metodo, std::vector<Disciplina *> *t_disciplina);

    void heuristica_construtiva(int t_iteracao);
    void pos_processamento();

    void exibir_solucoes();
    void debug_heuristica();

    // Função Objetivo
    void ordenar_solucoes();

    void avaliar_solucao(Solucao *t_solucao, bool t_factibilidade);
    int calcular_janela_professor(Solucao *t_solucao);
    int calcular_sexto_horario_turma(Solucao *t_solucao);

    Solucao *get_solucao(int index);

    Heuristica *shallow_copy() const;

    void busca_local(std::vector<Turma*> t_turmas, Solucao* t_solucao);
    std::vector<Disciplina*> encontrar_disciplinas_turma(Turma *t_turma);
    std::vector<Professor> encontrar_professores_turma(std::vector<Disciplina*> disciplinas_turma, Solucao *t_solucao);

    Solucao *get_melhor_solucao();

public:
    Heuristica(std::default_random_engine &t_rng, const std::string &t_instancia_nome, const int &t_tam_pop, const float &t_peso_janela, const int &t_peso_sexto, std::chrono::time_point<std::chrono::steady_clock> *t_tempo_inicial);
    void inicializar();
};

#endif //!_HEURISTICA_HPP