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
    std::vector<Solucao *> m_solucoes{};
    std::string m_instancia_nome{"NULL"};
    int m_tamanho_populacao{0};
    float m_peso_janela{0};
    float m_peso_sexto{0};

    std::vector<Disciplina *> ordenar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void ordenar_disciplinas(const int &rand_metodo, std::vector<Disciplina *> *t_disciplina);

    void heuristica_construtiva();
    void pos_processamento();

    void exibir_solucoes();
    void debug_heuristica();

    // Função Objetivo
    void avaliar_solucoes(const float &peso_janela, const float &peso_sexto_horario);

    float avaliar_solucao(Solucao *t_solucao, const float &peso_janela, const float &peso_sexto_horario);
    float calcular_janela_professor(Solucao *t_solucao);
    float calcular_sexto_horario_turma(Solucao *t_solucao);

    Solucao *get_solucao(int index);

    Heuristica *shallow_copy() const;

    Solucao *busca_local(std::set<int> t_turmas_selecionadas, Solucao t_solucao);
    std::set<int> encontrar_disciplinas_turma(Turma *t_turma);
    std::vector<Professor> encontrar_professores_turma(std::set<int> disciplinas_turma, Instancia *temp_instancia, Solucao *t_solucao);

    Solucao* get_melhor_solucao();

public:
    Heuristica(const std::string &t_instancia_nome, const int &t_tam_pop, const float &t_peso_janela, const int &t_peso_sexto);
    void inicializar();
};

#endif //!_HEURISTICA_HPP