#ifndef _HEURISTICA_HPP
#define _HEURISTICA_HPP

#include "solucao.hpp"
#include <set>
#include <ctime>

class Heuristica
{

private:
    std::vector<Solucao *> m_solucoes{};
    std::string m_instancia{"NULL"};
    int m_tamanho_populacao{0};


public:
    Heuristica(std::string t_instancia_pipe, int tam_populacao);

    std::vector<Disciplina *> ordernar_disciplinas(const int &rand_metodo, Solucao *solucao);
    void ordernar_disciplinas(const int &rand_metodo, std::vector<Disciplina*> t_disciplinas);

    void heuristica_construtiva();
    bool busca_local(std::set<int> t_turmas_selecionadas);
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

    Solucao* busca_local(std::set<int> t_turmas_selecionadas, Solucao* t_solucao);
    std::set<int> encontrar_disciplinas_turma(Turma *t_turma);
    std::vector<Professor> encontrar_professores_turma(std::set<int> disciplinas_turma, Instancia *temp_instancia, Solucao* t_solucao);
};

#endif //!_HEURISTICA_HPP